
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "phong.h"
#include "thongke.h"
#include "menu_utils.h"

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

