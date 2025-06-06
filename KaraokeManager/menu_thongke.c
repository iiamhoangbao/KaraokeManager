#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thongke.h"
#include "hoadon.h"
#include "phong.h"
#include "menu_utils.h"

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

