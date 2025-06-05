#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cthoadon.h"

// Tạo khóa tổng hợp soHD_maHH để so sánh
void taoKhoaTongHop(const char* soHD, const char* maHH, char* khoa) {
    sprintf(khoa, "%s_%s", soHD, maHH);
}

BSTNodeCTHoaDon* taoNodeCTHoaDon(CTHoaDon ct) {
    BSTNodeCTHoaDon* node = (BSTNodeCTHoaDon*)malloc(sizeof(BSTNodeCTHoaDon));
    if (!node) {
        printf("Khong du bo nho de tao node moi!\n");
        return NULL;
    }
    node->Info = ct;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void chenCTHoaDon(TreeCTHoaDon* root, CTHoaDon ct) {
    if (*root == NULL) {
        *root = taoNodeCTHoaDon(ct);
        return;
    }
    char khoa1[25], khoa2[25];
    taoKhoaTongHop(ct.soHD, ct.maHH, khoa1);
    taoKhoaTongHop((*root)->Info.soHD, (*root)->Info.maHH, khoa2);
    int cmp = strcmp(khoa1, khoa2);
    if (cmp < 0) chenCTHoaDon(&((*root)->Left), ct);
    else if (cmp > 0) chenCTHoaDon(&((*root)->Right), ct);
    else printf("Chi tiet hoa don %s_%s da ton tai!\n", ct.soHD, ct.maHH);
}

void duyetCTHoaDonLNR(TreeCTHoaDon root) {
    if (root != NULL) {
        duyetCTHoaDonLNR(root->Left);
        hienThiCTHoaDon(root->Info);
        duyetCTHoaDonLNR(root->Right);
    }
}

void hienThiCTHoaDon(CTHoaDon ct) {
    printf("SoHD: %s | MaHH: %s | So luong: %d | Thanh tien: %.2lf\n",
        ct.soHD, ct.maHH, ct.soLuong, ct.thanhTien);
}

BSTNodeCTHoaDon* timCTHoaDon(TreeCTHoaDon root, const char* soHD, const char* maHH) {
    if (root == NULL) return NULL;
    char khoa1[25], khoa2[25];
    taoKhoaTongHop(soHD, maHH, khoa1);
    taoKhoaTongHop(root->Info.soHD, root->Info.maHH, khoa2);
    int cmp = strcmp(khoa1, khoa2);
    if (cmp == 0) return root;
    else if (cmp < 0) return timCTHoaDon(root->Left, soHD, maHH);
    else return timCTHoaDon(root->Right, soHD, maHH);
}

TreeCTHoaDon xoaCTHoaDon(TreeCTHoaDon root, const char* soHD, const char* maHH) {
    if (root == NULL) return NULL;
    char khoa1[25], khoa2[25];
    taoKhoaTongHop(soHD, maHH, khoa1);
    taoKhoaTongHop(root->Info.soHD, root->Info.maHH, khoa2);
    int cmp = strcmp(khoa1, khoa2);
    if (cmp < 0) root->Left = xoaCTHoaDon(root->Left, soHD, maHH);
    else if (cmp > 0) root->Right = xoaCTHoaDon(root->Right, soHD, maHH);
    else {
        if (root->Left == NULL) {
            BSTNodeCTHoaDon* temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) {
            BSTNodeCTHoaDon* temp = root->Left;
            free(root);
            return temp;
        }
        BSTNodeCTHoaDon* temp = root->Right;
        while (temp && temp->Left != NULL) temp = temp->Left;
        root->Info = temp->Info;
        root->Right = xoaCTHoaDon(root->Right, temp->Info.soHD, temp->Info.maHH);
    }
    return root;
}

void ghiFileCTHoaDon(TreeCTHoaDon root, FILE* fp) {
    if (root != NULL) {
        fwrite(&(root->Info), sizeof(CTHoaDon), 1, fp);
        ghiFileCTHoaDon(root->Left, fp);
        ghiFileCTHoaDon(root->Right, fp);
    }
}

void docFileCTHoaDon(TreeCTHoaDon* root, const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (!fp) return;
    CTHoaDon ct;
    while (fread(&ct, sizeof(CTHoaDon), 1, fp)) {
        chenCTHoaDon(root, ct);
    }
    fclose(fp);
}

void giaiPhongCTHoaDon(TreeCTHoaDon root) {
    if (root != NULL) {
        giaiPhongCTHoaDon(root->Left);
        giaiPhongCTHoaDon(root->Right);
        free(root);
    }
}

void hienThiCTHoaDonTheoSoHD(TreeCTHoaDon root, const char* soHD) {
    if (root != NULL) {
        hienThiCTHoaDonTheoSoHD(root->Left, soHD);
        if (strcmp(root->Info.soHD, soHD) == 0)
            hienThiCTHoaDon(root->Info);
        hienThiCTHoaDonTheoSoHD(root->Right, soHD);
    }
}
