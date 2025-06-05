#ifndef PHONG_H
#define PHONG_H

#include <stdio.h>

typedef struct {
    char maPhong[10];
    char tenPhong[30];
    char loaiPhong[10];
    int trangThai;
    int soLuotDat;
    float gioThue;
    char ngayThue[15];
} Phong;

typedef struct BSTNodePhong {
    Phong Info;
    struct BSTNodePhong* Left;
    struct BSTNodePhong* Right;
} BSTNodePhong;

typedef BSTNodePhong* TreePhong;

BSTNodePhong* taoNodePhong(Phong p);
void chenPhong(TreePhong* root, Phong p);
void duyetPhongLNR(TreePhong root);
void hienThiPhong(Phong p);
BSTNodePhong* timPhong(TreePhong root, const char* maPhong);
TreePhong xoaPhong(TreePhong root, const char* maPhong);
void ghiFilePhong(TreePhong root, FILE* fp);
void docFilePhong(TreePhong* root, const char* tenFile);
void giaiPhongPhong(TreePhong root);

#endif
