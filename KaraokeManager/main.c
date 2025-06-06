#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <wchar.h>

#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"
#include "thongke.h"
#include "taofile.h"
#include "menu_all.h"
#include "menu_utils.h"

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
