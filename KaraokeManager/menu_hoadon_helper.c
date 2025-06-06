#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cthoadon.h"
#include "hanghoa.h"
#include "hoadon.h"

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

