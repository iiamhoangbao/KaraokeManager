#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"

BSTNodePhong* taoNodePhong(Phong p) {
    BSTNodePhong* node = (BSTNodePhong*)malloc(sizeof(BSTNodePhong));
    if (!node) {
        printf("\033[1;31m[X] Khong du bo nho de tao node moi!\033[0m\n");
        return NULL;
    }
    node->Info = p;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void chenPhong(TreePhong* root, Phong p) {
    if (*root == NULL) {
        *root = taoNodePhong(p);
        return;
    }
    int cmp = strcmp(p.maPhong, (*root)->Info.maPhong);
    if (cmp < 0)
        chenPhong(&((*root)->Left), p);
    else if (cmp > 0)
        chenPhong(&((*root)->Right), p);
    else
        printf("\033[1;31m[X] Khong the them: Ma phong %s da ton tai!\033[0m\n", p.maPhong);
}

void duyetPhongLNR(TreePhong root) {
    if (root != NULL) {
        duyetPhongLNR(root->Left);
        hienThiPhong(root->Info);
        duyetPhongLNR(root->Right);
    }
}

void hienThiPhong(Phong p) {
    printf("\033[1;36m+------------------------------------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| Ma phong: \033[1;37m%-10s\033[1;33m | Ten: \033[1;37m%-30s\033[1;33m | Loai: \033[1;37m%-7s\033[1;33m |\033[0m\n",
        p.maPhong, p.tenPhong, p.loaiPhong);
    printf("\033[1;33m| Trang thai: \033[1;37m%-8s\033[1;33m | Luot dat: \033[1;37m%-5d\033[1;33m | Gia/gio: \033[1;37m%8.3lf VND\033[1;33m         |\033[0m\n",
        p.trangThai == 0 ? "Trong" : "Dang su dung", p.soLuotDat, p.gioThue);
    printf("\033[1;33m| Ngay thue: \033[1;37m%-15s\033[1;33m                                                |\033[0m\n", p.ngayThue);
    printf("\033[1;36m+------------------------------------------------------------------------------+\033[0m\n");
}

BSTNodePhong* timPhong(TreePhong root, const char* maPhong) {
    if (root == NULL) return NULL;
    int cmp = strcmp(maPhong, root->Info.maPhong);
    if (cmp == 0) return root;
    if (cmp < 0) return timPhong(root->Left, maPhong);
    else return timPhong(root->Right, maPhong);
}

TreePhong xoaPhong(TreePhong root, const char* maPhong) {
    if (root == NULL) return NULL;
    int cmp = strcmp(maPhong, root->Info.maPhong);
    if (cmp < 0) root->Left = xoaPhong(root->Left, maPhong);
    else if (cmp > 0) root->Right = xoaPhong(root->Right, maPhong);
    else {
        if (root->Left == NULL) {
            BSTNodePhong* temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) {
            BSTNodePhong* temp = root->Left;
            free(root);
            return temp;
        }
        BSTNodePhong* temp = root->Right;
        while (temp->Left != NULL) temp = temp->Left;
        root->Info = temp->Info;
        root->Right = xoaPhong(root->Right, temp->Info.maPhong);
    }
    return root;
}

void ghiFilePhong(TreePhong root, FILE* fp) {
    if (root != NULL) {
        fwrite(&(root->Info), sizeof(Phong), 1, fp);
        ghiFilePhong(root->Left, fp);
        ghiFilePhong(root->Right, fp);
    }
}

void docFilePhong(TreePhong* root, const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (!fp) return;
    Phong p;
    while (fread(&p, sizeof(Phong), 1, fp) == 1) {
        chenPhong(root, p);
    }
    fclose(fp);
}

void giaiPhongPhong(TreePhong root) {
    if (root != NULL) {
        giaiPhongPhong(root->Left);
        giaiPhongPhong(root->Right);
        free(root);
    }
}

