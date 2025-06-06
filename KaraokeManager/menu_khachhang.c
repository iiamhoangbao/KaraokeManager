#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "khachhang.h"
#include "menu_utils.h"

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

