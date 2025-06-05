#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hoadon.h"

// Tạo node mới cho cây hóa đơn
BSTNodeHoaDon* taoNodeHoaDon(HoaDon hd) {
    BSTNodeHoaDon* node = (BSTNodeHoaDon*)malloc(sizeof(BSTNodeHoaDon));
    if (!node) {
        printf("\033[1;31m[X] Khong du bo nho de tao node moi!\033[0m\n");
        return NULL;
    }
    node->Info = hd;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

// Chèn hóa đơn vào cây
void chenHoaDon(TreeHoaDon* root, HoaDon hd) {
    if (*root == NULL) {
        *root = taoNodeHoaDon(hd);
        return;
    }

    int cmp = strcmp(hd.soHD, (*root)->Info.soHD);
    if (cmp < 0) {
        chenHoaDon(&((*root)->Left), hd);
    }
    else if (cmp > 0) {
        chenHoaDon(&((*root)->Right), hd);
    }
    else {
        printf("\033[1;31m[X] Khong the them: So hoa don %s da ton tai!\033[0m\n", hd.soHD);
    }
}

// Duyệt cây theo thứ tự LNR
void duyetHoaDonLNR(TreeHoaDon root) {
    if (root != NULL) {
        duyetHoaDonLNR(root->Left);
        hienThiHoaDon(root->Info);
        duyetHoaDonLNR(root->Right);
    }
}

// Hiển thị thông tin hóa đơn
void hienThiHoaDon(HoaDon hd) {
    printf("\033[1;36m+------------------------------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| So HD: \033[1;37m%-10s\033[1;33m       | Ma KH: \033[1;37m%-10s\033[1;33m | Ma phong: \033[1;37m%-10s\033[1;33m     |\033[0m\n",
        hd.soHD, hd.maKH, hd.maPhong);
    printf("\033[1;33m| Ngay thue: \033[1;37m%-12s\033[1;33m | Gio vao: \033[1;37m%-8s\033[1;33m | Gio ra: \033[1;37m%-8s\033[1;33m         |\033[0m\n",
        hd.ngayThue, hd.gioVao, hd.gioRa);
    printf("\033[1;33m| \033[1;32mTong tien: \033[1;37m%.3lf VND\033[1;33m                                               |\033[0m\n",
        hd.tongTien);
    printf("\033[1;36m+------------------------------------------------------------------------+\033[0m\n");
}

// Tìm hóa đơn theo số
BSTNodeHoaDon* timHoaDon(TreeHoaDon root, const char* soHD) {
    if (root == NULL) return NULL;

    int cmp = strcmp(soHD, root->Info.soHD);
    if (cmp == 0) return root;
    if (cmp < 0) return timHoaDon(root->Left, soHD);
    return timHoaDon(root->Right, soHD);
}

// Xóa hóa đơn khỏi cây
TreeHoaDon xoaHoaDon(TreeHoaDon root, const char* soHD) {
    if (root == NULL) return NULL;

    int cmp = strcmp(soHD, root->Info.soHD);
    if (cmp < 0) {
        root->Left = xoaHoaDon(root->Left, soHD);
    }
    else if (cmp > 0) {
        root->Right = xoaHoaDon(root->Right, soHD);
    }
    else {
        if (root->Left == NULL) {
            BSTNodeHoaDon* temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) {
            BSTNodeHoaDon* temp = root->Left;
            free(root);
            return temp;
        }

        BSTNodeHoaDon* temp = root->Right;
        while (temp && temp->Left != NULL) {
            temp = temp->Left;
        }

        root->Info = temp->Info;
        root->Right = xoaHoaDon(root->Right, temp->Info.soHD);
    }
    return root;
}

// Ghi cây vào file
void ghiFileHoaDon(TreeHoaDon root, FILE* fp) {
    if (root != NULL) {
        fwrite(&(root->Info), sizeof(HoaDon), 1, fp);
        ghiFileHoaDon(root->Left, fp);
        ghiFileHoaDon(root->Right, fp);
    }
}

// Đọc file vào cây
void docFileHoaDon(TreeHoaDon* root, const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (!fp) return;

    HoaDon hd;
    while (fread(&hd, sizeof(HoaDon), 1, fp)) {
        chenHoaDon(root, hd);
    }
    fclose(fp);
}

// Giải phóng bộ nhớ cho cây
void giaiPhongHoaDon(TreeHoaDon root) {
    if (root != NULL) {
        giaiPhongHoaDon(root->Left);
        giaiPhongHoaDon(root->Right);
        free(root);
    }
}
