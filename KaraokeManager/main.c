#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <wchar.h> // để dùng wprintf và wchar_t

#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"
#include "thongke.h"
#include "taofile.h"

// Hàm xóa màn hình
void xoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Hàm dừng màn hình
void dungManHinh() {
    printf("\n\033[1;36mNhan Enter de tiep tuc...\033[0m");
    while (getchar() != '\n');  // Làm sạch bộ đệm
    getchar();
}

// Hàm in tiêu đề chương trình
void inTieuDe() {
    printf("\033[1;36m");
    printf("\n+--------------------------------------+\n");
    printf("|        QUAN LY KARAOKE SYSTEM        |\n");
    printf("|              Version 2.0             |\n");
    printf("+--------------------------------------+\n");
    printf("\033[0m");
}

// Hàm in menu chức năng chính
void inMenu() {
    printf("\n\033[1;32m+=============== MENU ===============+\033[0m\n");
    printf("\033[1;33m");
    printf("|  1. Quan ly phong                  |\n");
    printf("|  2. Quan ly khach hang             |\n");
    printf("|  3. Quan ly hang hoa               |\n");
    printf("|  4. Quan ly hoa don                |\n");
    printf("|  5. Thong ke va bao cao            |\n");
    printf("|  6. Cai dat he thong               |\n");
    printf("|  0. Thoat chuong trinh             |\n");
    printf("\033[1;32m+====================================+\033[0m\n");
    printf("\033[0m");
}

// Hàm thêm hàng hóa vào hóa đơn
void themHangHoaVaoHoaDon(TreeCTHoaDon* rootCTHoaDon, TreeHangHoa* rootHangHoa,
    const char* soHD, double* tongTien) {
    char tiepTuc = 'y';
    while (tiepTuc == 'y' || tiepTuc == 'Y') {
        CTHoaDon ct;
        strcpy(ct.soHD, soHD);

        printf("\nNhap ma hang hoa: ");
        scanf("%s", ct.maHH);

        BSTNodeHangHoa* hh = timHangHoa(*rootHangHoa, ct.maHH);
        if (!hh) {
            printf("\033[1;31m❌ Ma hang hoa khong ton tai!\033[0m\n");
            continue;
        }

        printf("So luong: ");
        scanf("%d", &ct.soLuong);

        ct.thanhTien = ct.soLuong * hh->Info.donGia;
        *tongTien += ct.thanhTien;

        chenCTHoaDon(rootCTHoaDon, ct);

        FILE* fp = fopen("data/cthoadon.txt", "wb");
        if (fp) {
            ghiFileCTHoaDon(*rootCTHoaDon, fp);
            fclose(fp);
        }

        printf("\033[1;32m✅ Da them %s - So luong: %d - Thanh tien: %.2lf\033[0m\n",
            hh->Info.tenHH, ct.soLuong, ct.thanhTien);

        printf("Tiep tuc them hang hoa? (y/n): ");
        scanf(" %c", &tiepTuc);
    }
}

// Hàm tính tổng tiền hàng hóa của một hóa đơn
double tinhTongTienHangHoa(TreeCTHoaDon root, const char* soHD) {
    static double tongTien = 0;
    static int daReset = 0;

    if (!daReset) {
        tongTien = 0;
        daReset = 1;
    }

    if (root != NULL) {
        tinhTongTienHangHoa(root->Left, soHD);
        if (strcmp(root->Info.soHD, soHD) == 0) {
            tongTien += root->Info.thanhTien;
        }
        tinhTongTienHangHoa(root->Right, soHD);
    }

    if (daReset) {
        daReset = 0;
        return tongTien;
    }
    return 0;
}

// Hàm xóa tất cả chi tiết hóa đơn theo số HD
void xoaTatCaCTHoaDonTheoSoHD(TreeCTHoaDon* root, const char* soHD) {
    if (*root != NULL) {
        xoaTatCaCTHoaDonTheoSoHD(&((*root)->Left), soHD);
        xoaTatCaCTHoaDonTheoSoHD(&((*root)->Right), soHD);

        if (strcmp((*root)->Info.soHD, soHD) == 0) {
            *root = xoaCTHoaDon(*root, soHD, (*root)->Info.maHH);
        }
    }
}

// Menu quản lý phòng
void menuQuanLyPhong(TreePhong* rootPhong) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== QUAN LY PHONG ===========+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Them phong moi                  |\n");
        printf("|  2. Hien thi danh sach phong        |\n");
        printf("|  3. Tim phong theo ma               |\n");
        printf("|  4. Cap nhat thong tin phong        |\n");
        printf("|  5. Xoa phong                       |\n");
        printf("|  6. Thong ke phong theo loai        |\n");
        printf("|  0. Quay lai menu chinh             |\n");
        printf("\033[1;34m+=====================================+\033[0m\n");
        printf("\033[0m");

        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            printf("\n\033[1;32m=== THEM PHONG MOI ===\033[0m\n");
            Phong p;
            printf("Nhap ma phong: ");
            scanf("%s", p.maPhong);

            if (timPhong(*rootPhong, p.maPhong)) {
                printf("\033[1;31m❌ Ma phong da ton tai! Khong the them.\033[0m\n");
                dungManHinh();
                break;
            }

            printf("Nhap ten phong: ");
            getchar();
            fgets(p.tenPhong, sizeof(p.tenPhong), stdin);
            p.tenPhong[strcspn(p.tenPhong, "\n")] = '\0';

            printf("Loai phong (VIP/THUONG): ");
            scanf("%s", p.loaiPhong);
            p.trangThai = 0;
            p.soLuotDat = 0;
            printf("Gia theo gio: ");
            scanf("%f", &p.gioThue);

            // Tự động lấy ngày hiện tại
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(p.ngayThue, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

            chenPhong(rootPhong, p);

            FILE* fp = fopen("data/phong.txt", "wb");
            if (fp) {
                ghiFilePhong(*rootPhong, fp);
                fclose(fp);
                printf("\033[1;32m✅ Da them phong moi thanh cong!\033[0m\n");
            }
            else {
                printf("\033[1;31m❌ Loi ghi file!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 2:
            printf("\n\033[1;32m=== DANH SACH PHONG ===\033[0m\n");
            if (*rootPhong == NULL) {
                printf("\033[1;33m⚠️  Chua co phong nao trong he thong!\033[0m\n");
            }
            else {
                duyetPhongLNR(*rootPhong);
            }
            dungManHinh();
            break;
        case 3: {
            printf("\n\033[1;32m=== TIM PHONG ===\033[0m\n");
            char maPhong[10];
            printf("Nhap ma phong can tim: ");
            scanf("%s", maPhong);
            BSTNodePhong* p = timPhong(*rootPhong, maPhong);
            if (p) {
                printf("\033[1;32m✅ Tim thay phong:\033[0m\n");
                hienThiPhong(p->Info);
            }
            else {
                printf("\033[1;31m❌ Khong tim thay phong!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 4: {
            printf("\n\033[1;32m=== CAP NHAT PHONG ===\033[0m\n");
            char maPhong[10];
            printf("Nhap ma phong can cap nhat: ");
            scanf("%s", maPhong);
            BSTNodePhong* p = timPhong(*rootPhong, maPhong);
            if (p) {
                printf("Thong tin hien tai:\n");
                hienThiPhong(p->Info);
                printf("\nNhap thong tin moi:\n");
                printf("Ten phong moi: ");
                getchar();
                fgets(p->Info.tenPhong, sizeof(p->Info.tenPhong), stdin);
                p->Info.tenPhong[strcspn(p->Info.tenPhong, "\n")] = '\0';
                printf("Loai phong (VIP/THUONG): ");
                scanf("%s", p->Info.loaiPhong);
                printf("Gia theo gio: ");
                scanf("%f", &p->Info.gioThue);

                FILE* fp = fopen("data/phong.txt", "wb");
                if (fp) {
                    ghiFilePhong(*rootPhong, fp);
                    fclose(fp);
                    printf("\033[1;32m✅ Cap nhat thanh cong!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay phong!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 5: {
            printf("\n\033[1;32m=== XOA PHONG ===\033[0m\n");
            char maPhong[10];
            printf("Nhap ma phong can xoa: ");
            scanf("%s", maPhong);
            BSTNodePhong* p = timPhong(*rootPhong, maPhong);
            if (p) {
                printf("Thong tin phong se bi xoa:\n");
                hienThiPhong(p->Info);
                printf("\033[1;31mBan co chac chan muon xoa? (y/n): \033[0m");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    *rootPhong = xoaPhong(*rootPhong, maPhong);
                    FILE* fp = fopen("data/phong.txt", "wb");
                    if (fp) {
                        ghiFilePhong(*rootPhong, fp);
                        fclose(fp);
                        printf("\033[1;32m✅ Xoa phong thanh cong!\033[0m\n");
                    }
                }
                else {
                    printf("\033[1;33m⚠️  Da huy thao tac xoa!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay phong!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 6:
            printf("\n\033[1;32m=== THONG KE PHONG THEO LOAI ===\033[0m\n");
            thongKePhongTheoLoai(*rootPhong);
            dungManHinh();
            break;
        }
    } while (choice != 0);
}

// Menu quản lý khách hàng
void menuQuanLyKhachHang(TreeKhachHang* rootKhachHang) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== QUAN LY KHACH HANG ===========+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Them khach hang moi                  |\n");
        printf("|  2. Hien thi danh sach khach hang        |\n");
        printf("|  3. Tim khach hang theo ma               |\n");
        printf("|  4. Cap nhat thong tin khach hang        |\n");
        printf("|  5. Xoa khach hang                       |\n");
        printf("|  6. Thong ke khach hang theo loai        |\n"); 
        printf("|  0. Quay lai menu chinh                  |\n");
        printf("\033[1;34m+==========================================+\033[0m\n");
        printf("\033[0m");


        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            printf("\n\033[1;32m=== THEM KHACH HANG MOI ===\033[0m\n");
            KhachHang kh;
            printf("Nhap ma khach hang: ");
            scanf("%s", kh.maKH);

            if (timKhachHang(*rootKhachHang, kh.maKH)) {
                printf("\033[1;31m❌ Ma khach hang da ton tai!\033[0m\n");
                dungManHinh();
                break;
            }

            printf("Nhap ten khach hang: ");
            getchar();
            fgets(kh.tenKH, sizeof(kh.tenKH), stdin);
            kh.tenKH[strcspn(kh.tenKH, "\n")] = '\0';

            printf("Nhap so dien thoai: ");
            scanf("%s", kh.sdt);

            chenKhachHang(rootKhachHang, kh);

            FILE* fp = fopen("data/khachhang.txt", "wb");
            if (fp) {
                ghiFileKhachHang(*rootKhachHang, fp);
                fclose(fp);
                printf("\033[1;32m✅ Da them khach hang thanh cong!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 2:
            printf("\n\033[1;32m=== DANH SACH KHACH HANG ===\033[0m\n");
            if (*rootKhachHang == NULL) {
                printf("\033[1;33m⚠️  Chua co khach hang nao!\033[0m\n");
            }
            else {
                duyetKhachHangLNR(*rootKhachHang);
            }
            dungManHinh();
            break;
        case 3: {
            printf("\n\033[1;32m=== TIM KHACH HANG ===\033[0m\n");
            char maKH[10];
            printf("Nhap ma khach hang: ");
            scanf("%s", maKH);
            BSTNodeKhachHang* kh = timKhachHang(*rootKhachHang, maKH);
            if (kh) {
                printf("\033[1;32m✅ Tim thay khach hang:\033[0m\n");
                hienThiKhachHang(kh->Info);
            }
            else {
                printf("\033[1;31m❌ Khong tim thay khach hang!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 4: {
            printf("\n\033[1;32m=== CAP NHAT KHACH HANG ===\033[0m\n");
            char maKH[10];
            printf("Nhap ma khach hang: ");
            scanf("%s", maKH);
            BSTNodeKhachHang* kh = timKhachHang(*rootKhachHang, maKH);
            if (kh) {
                printf("Thong tin hien tai:\n");
                hienThiKhachHang(kh->Info);
                printf("\nNhap thong tin moi:\n");
                printf("Ten khach hang: ");
                getchar();
                fgets(kh->Info.tenKH, sizeof(kh->Info.tenKH), stdin);
                kh->Info.tenKH[strcspn(kh->Info.tenKH, "\n")] = '\0';
                printf("So dien thoai: ");
                scanf("%s", kh->Info.sdt);

                FILE* fp = fopen("data/khachhang.txt", "wb");
                if (fp) {
                    ghiFileKhachHang(*rootKhachHang, fp);
                    fclose(fp);
                    printf("\033[1;32m✅ Cap nhat thanh cong!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay khach hang!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 5: {
            printf("\n\033[1;32m=== XOA KHACH HANG ===\033[0m\n");
            char maKH[10];
            printf("Nhap ma khach hang can xoa: ");
            scanf("%s", maKH);
            BSTNodeKhachHang* kh = timKhachHang(*rootKhachHang, maKH);
            if (kh) {
                printf("Thong tin khach hang se bi xoa:\n");
                hienThiKhachHang(kh->Info);
                printf("\033[1;31mBan co chac chan muon xoa? (y/n): \033[0m");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    *rootKhachHang = xoaKhachHang(*rootKhachHang, maKH);
                    FILE* fp = fopen("data/khachhang.txt", "wb");
                    if (fp) {
                        ghiFileKhachHang(*rootKhachHang, fp);
                        fclose(fp);
                        printf("\033[1;32m✅ Xoa khach hang thanh cong!\033[0m\n");
                    }
                }
                else {
                    printf("\033[1;33m⚠️  Da huy thao tac xoa!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay khach hang!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        }
    } while (choice != 0);
}

// Menu quản lý hàng hóa
void menuQuanLyHangHoa(TreeHangHoa* rootHangHoa) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== QUAN LY HANG HOA ============+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Them hang hoa moi                   |\n");
        printf("|  2. Hien thi danh sach hang hoa         |\n");
        printf("|  3. Tim hang hoa theo ma                |\n");
        printf("|  4. Cap nhat thong tin hang hoa         |\n");
        printf("|  5. Xoa hang hoa                        |\n");
        printf("|  0. Quay lai menu chinh                 |\n");
        printf("\033[1;34m+=========================================+\033[0m\n");
        printf("\033[0m");

        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            printf("\n\033[1;32m=== THEM HANG HOA MOI ===\033[0m\n");
            HangHoa hh;
            printf("Nhap ma hang hoa: ");
            scanf("%s", hh.maHH);

            if (timHangHoa(*rootHangHoa, hh.maHH)) {
                printf("\033[1;31m❌ Ma hang hoa da ton tai!\033[0m\n");
                dungManHinh();
                break;
            }

            printf("Nhap ten hang hoa: ");
            getchar();
            fgets(hh.tenHH, sizeof(hh.tenHH), stdin);
            hh.tenHH[strcspn(hh.tenHH, "\n")] = '\0';

            printf("Nhap don gia: ");
            scanf("%lf", &hh.donGia);

            chenHangHoa(rootHangHoa, hh);

            FILE* fp = fopen("data/hanghoa.txt", "wb");
            if (fp) {
                ghiFileHangHoa(*rootHangHoa, fp);
                fclose(fp);
                printf("\033[1;32m✅ Da them hang hoa thanh cong!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 2:
            printf("\n\033[1;32m=== DANH SACH HANG HOA ===\033[0m\n");
            if (*rootHangHoa == NULL) {
                printf("\033[1;33m⚠️  Chua co hang hoa nao!\033[0m\n");
            }
            else {
                duyetHangHoaLNR(*rootHangHoa);
            }
            dungManHinh();
            break;
        case 3: {
            printf("\n\033[1;32m=== TIM HANG HOA ===\033[0m\n");
            char maHH[10];
            printf("Nhap ma hang hoa: ");
            scanf("%s", maHH);
            BSTNodeHangHoa* hh = timHangHoa(*rootHangHoa, maHH);
            if (hh) {
                printf("\033[1;32m✅ Tim thay hang hoa:\033[0m\n");
                hienThiHangHoa(hh->Info);
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hang hoa!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 4: {
            printf("\n\033[1;32m=== CAP NHAT HANG HOA ===\033[0m\n");
            char maHH[10];
            printf("Nhap ma hang hoa: ");
            scanf("%s", maHH);
            BSTNodeHangHoa* hh = timHangHoa(*rootHangHoa, maHH);
            if (hh) {
                printf("Thong tin hien tai:\n");
                hienThiHangHoa(hh->Info);
                printf("\nNhap thong tin moi:\n");
                printf("Ten hang hoa: ");
                getchar();
                fgets(hh->Info.tenHH, sizeof(hh->Info.tenHH), stdin);
                hh->Info.tenHH[strcspn(hh->Info.tenHH, "\n")] = '\0';
                printf("Don gia: ");
                scanf("%lf", &hh->Info.donGia);

                FILE* fp = fopen("data/hanghoa.txt", "wb");
                if (fp) {
                    ghiFileHangHoa(*rootHangHoa, fp);
                    fclose(fp);
                    printf("\033[1;32m✅ Cap nhat thanh cong!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hang hoa!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 5: {
            printf("\n\033[1;32m=== XOA HANG HOA ===\033[0m\n");
            char maHH[10];
            printf("Nhap ma hang hoa can xoa: ");
            scanf("%s", maHH);
            BSTNodeHangHoa* hh = timHangHoa(*rootHangHoa, maHH);
            if (hh) {
                printf("Thong tin hang hoa se bi xoa:\n");
                hienThiHangHoa(hh->Info);
                printf("\033[1;31mBan co chac chan muon xoa? (y/n): \033[0m");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    *rootHangHoa = xoaHangHoa(*rootHangHoa, maHH);
                    FILE* fp = fopen("data/hanghoa.txt", "wb");
                    if (fp) {
                        ghiFileHangHoa(*rootHangHoa, fp);
                        fclose(fp);
                        printf("\033[1;32m✅ Xoa hang hoa thanh cong!\033[0m\n");
                    }
                }
                else {
                    printf("\033[1;33m⚠️  Da huy thao tac xoa!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hang hoa!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        }
    } while (choice != 0);
}

// Menu quản lý hóa đơn
void menuQuanLyHoaDon(TreeHoaDon* rootHoaDon, TreeKhachHang* rootKhachHang,
    TreePhong* rootPhong, TreeCTHoaDon* rootCTHoaDon, TreeHangHoa* rootHangHoa) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== QUAN LY HOA DON ===========+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Tao hoa don moi                   |\n");
        printf("|  2. Hien thi danh sach hoa don        |\n");
        printf("|  3. Tim hoa don theo so               |\n");
        printf("|  4. Hien thi hoa don theo ma KH       |\n");
        printf("|  5. Cap nhat hoa don                  |\n");
        printf("|  6. Xoa hoa don                       |\n");
        printf("|  0. Quay lai menu chinh               |\n");
        printf("\033[1;34m+=======================================+\033[0m\n");
        printf("\033[0m");

        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            printf("\n\033[1;32m=== TAO HOA DON MOI ===\033[0m\n");
            HoaDon hd;
            printf("Nhap so hoa don: ");
            scanf("%s", hd.soHD);

            if (timHoaDon(*rootHoaDon, hd.soHD)) {
                printf("\033[1;31m❌ So hoa don da ton tai!\033[0m\n");
                dungManHinh();
                break;
            }

            printf("Nhap ma khach hang: ");
            scanf("%s", hd.maKH);
            if (!timKhachHang(*rootKhachHang, hd.maKH)) {
                printf("\033[1;31m❌ Ma khach hang khong ton tai!\033[0m\n");
                dungManHinh();
                break;
            }

            printf("Nhap ma phong: ");
            scanf("%s", hd.maPhong);
            BSTNodePhong* phong = timPhong(*rootPhong, hd.maPhong);
            if (!phong) {
                printf("\033[1;31m❌ Ma phong khong ton tai!\033[0m\n");
                dungManHinh();
                break;
            }

            // Tự động lấy ngày hiện tại
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(hd.ngayThue, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

            printf("Nhap gio vao (hh:mm): ");
            scanf("%s", hd.gioVao);
            printf("Nhap gio ra (hh:mm): ");
            scanf("%s", hd.gioRa);

            // Tính tiền phòng
            int gioVao, phutVao, gioRa, phutRa;
            sscanf(hd.gioVao, "%d:%d", &gioVao, &phutVao);
            sscanf(hd.gioRa, "%d:%d", &gioRa, &phutRa);

            int tongPhut = (gioRa * 60 + phutRa) - (gioVao * 60 + phutVao);
            if (tongPhut < 0) tongPhut += 24 * 60; // Qua ngày

            double soGio = (double)tongPhut / 60.0;
            hd.tongTien = soGio * phong->Info.gioThue;

            // Cập nhật số lượt đặt phòng
            phong->Info.soLuotDat++;

            chenHoaDon(rootHoaDon, hd);

            // Lưu file
            FILE* fpHD = fopen("data/hoadon.txt", "wb");
            FILE* fpPhong = fopen("data/phong.txt", "wb");
            if (fpHD && fpPhong) {
                ghiFileHoaDon(*rootHoaDon, fpHD);
                ghiFilePhong(*rootPhong, fpPhong);
                fclose(fpHD);
                fclose(fpPhong);
                printf("\033[1;32m✅ Tao hoa don thanh cong! Tong tien: %.2lf VND\033[0m\n", hd.tongTien);

                // Hỏi có muốn thêm hàng hóa không
                printf("\nBan co muon them hang hoa vao hoa don? (y/n): ");
                char addItems;
                scanf(" %c", &addItems);
                if (addItems == 'y' || addItems == 'Y') {
                    themHangHoaVaoHoaDon(rootCTHoaDon, rootHangHoa, hd.soHD, &hd.tongTien);
                    // Cập nhật lại tổng tiền trong hóa đơn
                    BSTNodeHoaDon* hdNode = timHoaDon(*rootHoaDon, hd.soHD);
                    if (hdNode) {
                        hdNode->Info.tongTien = hd.tongTien;
                        FILE* fp = fopen("data/hoadon.txt", "wb");
                        if (fp) {
                            ghiFileHoaDon(*rootHoaDon, fp);
                            fclose(fp);
                        }
                    }
                }
            }
            dungManHinh();
            break;
        }
        case 2:
            printf("\n\033[1;32m=== DANH SACH HOA DON ===\033[0m\n");
            if (*rootHoaDon == NULL) {
                printf("\033[1;33m⚠️  Chua co hoa don nao!\033[0m\n");
            }
            else {
                duyetHoaDonLNR(*rootHoaDon);
            }
            dungManHinh();
            break;
        case 3: {
            printf("\n\033[1;32m=== TIM HOA DON ===\033[0m\n");
            char soHD[10];
            printf("Nhap so hoa don: ");
            scanf("%s", soHD);
            BSTNodeHoaDon* p = timHoaDon(*rootHoaDon, soHD);
            if (p) {
                printf("\033[1;32m✅ Tim thay hoa don:\033[0m\n");
                hienThiHoaDon(p->Info);
                printf("\n--- Chi tiet hang hoa ---\n");
                hienThiCTHoaDonTheoSoHD(*rootCTHoaDon, soHD);
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hoa don!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 4: {
            printf("\n\033[1;32m=== HOA DON THEO KHACH HANG ===\033[0m\n");
            char maKH[10];
            printf("Nhap ma khach hang: ");
            scanf("%s", maKH);
            hienThiHoaDonTheoMaKH(*rootHoaDon, maKH);
            dungManHinh();
            break;
        }
        case 5: {
            printf("\n\033[1;32m=== CAP NHAT HOA DON ===\033[0m\n");
            char soHD[10];
            printf("Nhap so hoa don can cap nhat: ");
            scanf("%s", soHD);
            BSTNodeHoaDon* hd = timHoaDon(*rootHoaDon, soHD);
            if (hd) {
                printf("Thong tin hien tai:\n");
                hienThiHoaDon(hd->Info);
                printf("\nCap nhat gio ra moi (hh:mm): ");
                scanf("%s", hd->Info.gioRa);

                // Tính lại tiền
                BSTNodePhong* phong = timPhong(*rootPhong, hd->Info.maPhong);
                if (phong) {
                    int gioVao, phutVao, gioRa, phutRa;
                    sscanf(hd->Info.gioVao, "%d:%d", &gioVao, &phutVao);
                    sscanf(hd->Info.gioRa, "%d:%d", &gioRa, &phutRa);

                    int tongPhut = (gioRa * 60 + phutRa) - (gioVao * 60 + phutVao);
                    if (tongPhut < 0) tongPhut += 24 * 60;

                    double soGio = (double)tongPhut / 60.0;
                    double tienPhong = soGio * phong->Info.gioThue;

                    // Tính tổng tiền hàng hóa
                    double tienHangHoa = tinhTongTienHangHoa(*rootCTHoaDon, soHD);
                    hd->Info.tongTien = tienPhong + tienHangHoa;

                    FILE* fp = fopen("data/hoadon.txt", "wb");
                    if (fp) {
                        ghiFileHoaDon(*rootHoaDon, fp);
                        fclose(fp);
                        printf("\033[1;32m✅ Cap nhat thanh cong! Tong tien moi: %.2lf VND\033[0m\n", hd->Info.tongTien);
                    }
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hoa don!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        case 6: {
            printf("\n\033[1;32m=== XOA HOA DON ===\033[0m\n");
            char soHD[10];
            printf("Nhap so hoa don can xoa: ");
            scanf("%s", soHD);
            BSTNodeHoaDon* hd = timHoaDon(*rootHoaDon, soHD);
            if (hd) {
                printf("Thong tin hoa don se bi xoa:\n");
                hienThiHoaDon(hd->Info);
                printf("\033[1;31mBan co chac chan muon xoa? (y/n): \033[0m");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    // Xóa chi tiết hóa đơn trước
                    xoaTatCaCTHoaDonTheoSoHD(rootCTHoaDon, soHD);
                    // Xóa hóa đơn
                    *rootHoaDon = xoaHoaDon(*rootHoaDon, soHD);

                    FILE* fpHD = fopen("data/hoadon.txt", "wb");
                    FILE* fpCT = fopen("data/cthoadon.txt", "wb");
                    if (fpHD && fpCT) {
                        ghiFileHoaDon(*rootHoaDon, fpHD);
                        ghiFileCTHoaDon(*rootCTHoaDon, fpCT);
                        fclose(fpHD);
                        fclose(fpCT);
                        printf("\033[1;32m✅ Xoa hoa don thanh cong!\033[0m\n");
                    }
                }
                else {
                    printf("\033[1;33m⚠️  Da huy thao tac xoa!\033[0m\n");
                }
            }
            else {
                printf("\033[1;31m❌ Khong tim thay hoa don!\033[0m\n");
            }
            dungManHinh();
            break;
        }
        }
    } while (choice != 0);
}

// Menu thống kê
void menuThongKe(TreeHoaDon rootHoaDon, TreePhong rootPhong) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== THONG KE VA BAO CAO ===========+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Thong ke doanh thu theo ngay          |\n");
        printf("|  2. Thong ke doanh thu theo thang         |\n");
        printf("|  3. Thong ke doanh thu theo nam           |\n");
        printf("|  4. Thong ke doanh thu theo khoang        |\n");
        printf("|  5. Top 3 phong duoc thue nhieu nhat      |\n");
        printf("|  6. Thong ke phong theo loai              |\n");
        printf("|  7. Bao cao tong quan                     |\n");
        printf("|  0. Quay lai menu chinh                   |\n");
        printf("\033[1;34m+===========================================+\033[0m\n");
        printf("\033[0m");

        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            printf("\n\033[1;32m=== THONG KE THEO NGAY ===\033[0m\n");
            char ngay[11];
            printf("Nhap ngay (dd/mm/yyyy): ");
            scanf("%s", ngay);
            thongKeDoanhThuTheoNgay(rootHoaDon, ngay);
            dungManHinh();
            break;
        }
        case 2: {
            printf("\n\033[1;32m=== THONG KE THEO THANG ===\033[0m\n");
            char thang[3];
            printf("Nhap thang (mm): ");
            scanf("%s", thang);
            thongKeDoanhThuTheoThang(rootHoaDon, thang);
            dungManHinh();
            break;
        }
        case 3: {
            printf("\n\033[1;32m=== THONG KE THEO NAM ===\033[0m\n");
            char nam[5];
            printf("Nhap nam (yyyy): ");
            scanf("%s", nam);
            thongKeDoanhThuTheoNam(rootHoaDon, nam);
            dungManHinh();
            break;
        }
        case 4: {
            printf("\n\033[1;32m=== THONG KE THEO KHOANG ===\033[0m\n");
            char tu[11], den[11];
            printf("Nhap ngay bat dau (dd/mm/yyyy): ");
            scanf("%s", tu);
            printf("Nhap ngay ket thuc (dd/mm/yyyy): ");
            scanf("%s", den);
            thongKeDoanhThuTheoKhoang(rootHoaDon, tu, den);
            dungManHinh();
            break;
        }
        case 5:
            printf("\n\033[1;32m=== TOP 3 PHONG ===\033[0m\n");
            top3PhongDuocThueNhieuNhat(rootHoaDon);
            dungManHinh();
            break;
        case 6:
            printf("\n\033[1;32m=== THONG KE PHONG THEO LOAI ===\033[0m\n");
            thongKePhongTheoLoai(rootPhong);
            dungManHinh();
            break;
        case 7:
            printf("\n\033[1;32m=== BAO CAO TONG QUAN ===\033[0m\n");
            baoCaoTongQuan(rootHoaDon, rootPhong);
            dungManHinh();
            break;
        }
    } while (choice != 0);
}

// Hàm sao lưu dữ liệu
void saoluuDuLieu(TreePhong rootPhong, TreeHoaDon rootHoaDon, TreeKhachHang rootKhachHang,
    TreeHangHoa rootHangHoa, TreeCTHoaDon rootCTHoaDon) {
    FILE* fp;

    // Tạo thư mục backup nếu chưa có
#ifdef _WIN32
    system("mkdir backup 2>nul");
#else
    system("mkdir -p backup");
#endif

    // Backup phòng
    fp = fopen("backup/phong_backup.txt", "wb");
    if (fp) {
        ghiFilePhong(rootPhong, fp);
        fclose(fp);
    }

    // Backup hóa đơn
    fp = fopen("backup/hoadon_backup.txt", "wb");
    if (fp) {
        ghiFileHoaDon(rootHoaDon, fp);
        fclose(fp);
    }

    // Backup khách hàng
    fp = fopen("backup/khachhang_backup.txt", "wb");
    if (fp) {
        ghiFileKhachHang(rootKhachHang, fp);
        fclose(fp);
    }

    // Backup hàng hóa
    fp = fopen("backup/hanghoa_backup.txt", "wb");
    if (fp) {
        ghiFileHangHoa(rootHangHoa, fp);
        fclose(fp);
    }

    // Backup chi tiết hóa đơn
    fp = fopen("backup/cthoadon_backup.txt", "wb");
    if (fp) {
        ghiFileCTHoaDon(rootCTHoaDon, fp);
        fclose(fp);
    }

    printf("\033[1;32m✅ Sao luu du lieu thanh cong vao thu muc 'backup'!\033[0m\n");
}

// Hàm xóa toàn bộ dữ liệu
void xoaToanBoDuLieu(TreePhong* rootPhong, TreeHoaDon* rootHoaDon, TreeKhachHang* rootKhachHang,
    TreeHangHoa* rootHangHoa, TreeCTHoaDon* rootCTHoaDon) {
    giaiPhongPhong(*rootPhong); *rootPhong = NULL;
    giaiPhongHoaDon(*rootHoaDon); *rootHoaDon = NULL;
    giaiPhongKhachHang(*rootKhachHang); *rootKhachHang = NULL;
    giaiPhongHangHoa(*rootHangHoa); *rootHangHoa = NULL;
    giaiPhongCTHoaDon(*rootCTHoaDon); *rootCTHoaDon = NULL;

    remove("data/phong.txt");
    remove("data/hoadon.txt");
    remove("data/khachhang.txt");
    remove("data/hanghoa.txt");
    remove("data/cthoadon.txt");
}

// Menu cài đặt hệ thống
void menuCaiDat(TreePhong* rootPhong, TreeHoaDon* rootHoaDon, TreeKhachHang* rootKhachHang,
    TreeHangHoa* rootHangHoa, TreeCTHoaDon* rootCTHoaDon) {
    int choice;
    do {
        xoaManHinh();
        printf("\033[1;34m+=========== CAI DAT HE THONG ===========+\033[0m\n");
        printf("\033[1;33m");
        printf("|  1. Sao luu du lieu                    |\n");
        printf("|  2. Khoi tao du lieu mau               |\n");
        printf("|  3. Xoa toan bo du lieu                |\n");
        printf("|  4. Thong tin he thong                 |\n");
        printf("|  0. Quay lai menu chinh                |\n");
        printf("\033[1;34m+========================================+\033[0m\n");
        printf("\033[0m");


        printf("\033[1;36mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("\n\033[1;32m=== SAO LUU DU LIEU ===\033[0m\n");
            saoluuDuLieu(*rootPhong, *rootHoaDon, *rootKhachHang, *rootHangHoa, *rootCTHoaDon);
            dungManHinh();
            break;
        case 2:
            printf("\n\033[1;32m=== KHOI TAO DU LIEU MAU ===\033[0m\n");
            printf("\033[1;31mChu y: Thao tac nay se ghi de du lieu hien tai!\033[0m\n");
            printf("Ban co chac chan muon tiep tuc? (y/n): ");
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                taoTatCaFileMau();
                // Đọc lại dữ liệu
                giaiPhongPhong(*rootPhong); *rootPhong = NULL;
                giaiPhongHoaDon(*rootHoaDon); *rootHoaDon = NULL;
                giaiPhongKhachHang(*rootKhachHang); *rootKhachHang = NULL;
                giaiPhongHangHoa(*rootHangHoa); *rootHangHoa = NULL;
                giaiPhongCTHoaDon(*rootCTHoaDon); *rootCTHoaDon = NULL;

                docFilePhong(rootPhong, "data/phong.txt");
                docFileHoaDon(rootHoaDon, "data/hoadon.txt");
                docFileKhachHang(rootKhachHang, "data/khachhang.txt");
                docFileHangHoa(rootHangHoa, "data/hanghoa.txt");
                docFileCTHoaDon(rootCTHoaDon, "data/cthoadon.txt");

                printf("\033[1;32m✅ Khoi tao du lieu mau thanh cong!\033[0m\n");
            }
            else {
                printf("\033[1;33m⚠️  Da huy thao tac!\033[0m\n");
            }
            dungManHinh();
            break;
        case 3:
            printf("\n\033[1;32m=== XOA TOAN BO DU LIEU ===\033[0m\n");
            printf("\033[1;31mCHU Y: Thao tac nay se xoa toan bo du lieu!\033[0m\n");
            printf("Nhap 'DELETE' de xac nhan: ");
            char confirmDelete[10];
            scanf("%s", confirmDelete);
            if (strcmp(confirmDelete, "DELETE") == 0) {
                xoaToanBoDuLieu(rootPhong, rootHoaDon, rootKhachHang, rootHangHoa, rootCTHoaDon);
                printf("\033[1;32m✅ Da xoa toan bo du lieu thanh cong!\033[0m\n");
            }
            else {
                printf("\033[1;33m⚠️  Da huy thao tac xoa du lieu!\033[0m\n");
            }
            dungManHinh();
            break;
        case 4:
            printf("\n\033[1;32m=== THONG TIN HE THONG ===\033[0m\n");
            printf("+==================================+\n");
            printf("|  QUAN LY KARAOKE SYSTEM v2.0     |\n");
            printf("|  Ngon ngu: C                     |\n");
            printf("|  Cau truc du lieu: BST           |\n");
            printf("|  Luu tru: KaraokeManager         |\n");
            printf("+==================================+\n");
            dungManHinh();
            break;
        case 0:
            return;
        default:
            printf("\033[1;31mLua chon khong hop le!\033[0m\n");
            dungManHinh();
        }
    } while (1);
}

int main() {

    system("chcp 65001");


    // Khởi tạo
    TreePhong rootPhong = NULL;
    TreeHoaDon rootHoaDon = NULL;
    TreeKhachHang rootKhachHang = NULL;
    TreeHangHoa rootHangHoa = NULL;
    TreeCTHoaDon rootCTHoaDon = NULL;

    // Tạo file mẫu nếu chưa có
    taoTatCaFileMau();

    // Đọc dữ liệu từ file
    docFilePhong(&rootPhong, "data/phong.txt");
    docFileHoaDon(&rootHoaDon, "data/hoadon.txt");
    docFileKhachHang(&rootKhachHang, "data/khachhang.txt");
    docFileHangHoa(&rootHangHoa, "data/hanghoa.txt");
    docFileCTHoaDon(&rootCTHoaDon, "data/cthoadon.txt");

    int choice;
    do {
        xoaManHinh();
        inTieuDe();
        inMenu();
        printf("\033[1;34mChon chuc nang: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            menuQuanLyPhong(&rootPhong);
            break;
        case 2:
            menuQuanLyKhachHang(&rootKhachHang);
            break;
        case 3:
            menuQuanLyHangHoa(&rootHangHoa);
            break;
        case 4:
            menuQuanLyHoaDon(&rootHoaDon, &rootKhachHang, &rootPhong, &rootCTHoaDon, &rootHangHoa);
            break;
        case 5:
            menuThongKe(rootHoaDon, rootPhong);
            break;
        case 6:
            menuCaiDat(&rootPhong, &rootHoaDon, &rootKhachHang, &rootHangHoa, &rootCTHoaDon);
            break;
        case 0:
            printf("\033[1;35m\n+=======================================+\n");
            printf("|   Cam on ban da su dung chuong trinh! |\n");
            printf("|           Hen gap lai!                |\n");
            printf("+=======================================+\n\033[0m");
            break;
        default:
            printf("\033[1;31mLua chon khong hop le!\033[0m\n");
            dungManHinh();
        }
    } while (choice != 0);

    // Giải phóng bộ nhớ
    giaiPhongPhong(rootPhong);
    giaiPhongHoaDon(rootHoaDon);
    giaiPhongKhachHang(rootKhachHang);
    giaiPhongHangHoa(rootHangHoa);
    giaiPhongCTHoaDon(rootCTHoaDon);

    return 0;
}