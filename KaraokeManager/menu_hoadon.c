#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"
#include "thongke.h"

#include "menu_all.h"
#include "menu_utils.h"

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

