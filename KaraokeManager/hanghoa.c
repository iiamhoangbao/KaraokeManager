#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanghoa.h"

// Tạo node mới cho cây hàng hóa
BSTNodeHangHoa* taoNodeHangHoa(HangHoa hh) {
    BSTNodeHangHoa* node = (BSTNodeHangHoa*)malloc(sizeof(BSTNodeHangHoa));
    if (!node) {
        printf("\033[1;31m[X] Khong du bo nho de tao node moi!\033[0m\n");
        return NULL;
    }
    node->Info = hh;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

// Chèn hàng hóa vào cây
void chenHangHoa(TreeHangHoa* root, HangHoa hh) {
    if (*root == NULL) {
        *root = taoNodeHangHoa(hh);
        return;
    }

    int cmp = strcmp(hh.maHH, (*root)->Info.maHH);
    if (cmp < 0) {
        chenHangHoa(&((*root)->Left), hh);
    }
    else if (cmp > 0) {
        chenHangHoa(&((*root)->Right), hh);
    }
    else {
        printf("\033[1;31m[X] Khong the them: Ma hang hoa %s da ton tai!\033[0m\n", hh.maHH);
    }
}

// Duyệt cây theo thứ tự LNR
void duyetHangHoaLNR(TreeHangHoa root) {
    if (root != NULL) {
        duyetHangHoaLNR(root->Left);
        hienThiHangHoa(root->Info);
        duyetHangHoaLNR(root->Right);
    }
}

// Hiển thị thông tin hàng hóa
void hienThiHangHoa(HangHoa hh) {
    printf("\033[1;36m+-----------------------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| Ma HH: \033[1;37m%-10s\033[1;33m | Ten hang hoa: \033[1;37m%-30s\033[1;33m|\033[0m\n",
        hh.maHH, hh.tenHH);
    printf("\033[1;33m| \033[1;32mDon gia: \033[1;37m%.3lf VND\033[1;33m                                            |\033[0m\n",
        hh.donGia);
    printf("\033[1;36m+-----------------------------------------------------------------+\033[0m\n");
}

// Tìm hàng hóa theo mã
BSTNodeHangHoa* timHangHoa(TreeHangHoa root, const char* maHH) {
    if (root == NULL) return NULL;

    int cmp = strcmp(maHH, root->Info.maHH);
    if (cmp == 0) return root;
    if (cmp < 0) return timHangHoa(root->Left, maHH);
    return timHangHoa(root->Right, maHH);
}

// Xóa hàng hóa khỏi cây
TreeHangHoa xoaHangHoa(TreeHangHoa root, const char* maHH) {
    if (root == NULL) return NULL;

    int cmp = strcmp(maHH, root->Info.maHH);
    if (cmp < 0) {
        root->Left = xoaHangHoa(root->Left, maHH);
    }
    else if (cmp > 0) {
        root->Right = xoaHangHoa(root->Right, maHH);
    }
    else {
        if (root->Left == NULL) {
            BSTNodeHangHoa* temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) {
            BSTNodeHangHoa* temp = root->Left;
            free(root);
            return temp;
        }

        BSTNodeHangHoa* temp = root->Right;
        while (temp && temp->Left != NULL) {
            temp = temp->Left;
        }

        root->Info = temp->Info;
        root->Right = xoaHangHoa(root->Right, temp->Info.maHH);
    }
    return root;
}

// Ghi cây vào file
void ghiFileHangHoa(TreeHangHoa root, FILE* fp) {
    if (root != NULL) {
        fwrite(&(root->Info), sizeof(HangHoa), 1, fp);
        ghiFileHangHoa(root->Left, fp);
        ghiFileHangHoa(root->Right, fp);
    }
}

// Đọc file vào cây
void docFileHangHoa(TreeHangHoa* root, const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (!fp) return;

    HangHoa hh;
    while (fread(&hh, sizeof(HangHoa), 1, fp)) {
        chenHangHoa(root, hh);
    }
    fclose(fp);
}

// Giải phóng bộ nhớ cho cây
void giaiPhongHangHoa(TreeHangHoa root) {
    if (root != NULL) {
        giaiPhongHangHoa(root->Left);
        giaiPhongHangHoa(root->Right);
        free(root);
    }
}
