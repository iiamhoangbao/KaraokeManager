#ifndef CTHOADON_H
#define CTHOADON_H

#include <stdio.h>

typedef struct {
    char soHD[10];
    char maHH[10];
    int soLuong;
    double thanhTien;
} CTHoaDon;

typedef struct BSTNodeCTHoaDon {
    CTHoaDon Info;
    struct BSTNodeCTHoaDon* Left;
    struct BSTNodeCTHoaDon* Right;
} BSTNodeCTHoaDon;

typedef BSTNodeCTHoaDon* TreeCTHoaDon;

BSTNodeCTHoaDon* taoNodeCTHoaDon(CTHoaDon ct);
void chenCTHoaDon(TreeCTHoaDon* root, CTHoaDon ct);
void duyetCTHoaDonLNR(TreeCTHoaDon root);
void hienThiCTHoaDon(CTHoaDon ct);
BSTNodeCTHoaDon* timCTHoaDon(TreeCTHoaDon root, const char* soHD, const char* maHH);
TreeCTHoaDon xoaCTHoaDon(TreeCTHoaDon root, const char* soHD, const char* maHH);
void ghiFileCTHoaDon(TreeCTHoaDon root, FILE* fp);
void docFileCTHoaDon(TreeCTHoaDon* root, const char* tenFile);
void giaiPhongCTHoaDon(TreeCTHoaDon root);
void hienThiCTHoaDonTheoSoHD(TreeCTHoaDon root, const char* soHD);

#endif
