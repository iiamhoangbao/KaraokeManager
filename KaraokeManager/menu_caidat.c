#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"
#include "taofile.h"
#include "menu_utils.h"

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

