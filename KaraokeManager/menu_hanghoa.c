#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanghoa.h"
#include "menu_utils.h"

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

