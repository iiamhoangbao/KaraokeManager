#ifndef HANGHOA_H
#define HANGHOA_H

#include <stdio.h>

// Định nghĩa cấu trúc HangHoa
typedef struct {
    char maHH[10];        // Mã hàng hóa (tối đa 9 ký tự + null terminator)
    char tenHH[50];       // Tên hàng hóa (tối đa 49 ký tự + null terminator)
    double donGia;        // Đơn giá (kiểu double để lưu giá trị tiền)
} HangHoa;

// Định nghĩa cấu trúc node cho cây nhị phân tìm kiếm hàng hóa
typedef struct BSTNodeHangHoa {
    HangHoa Info;          // Dữ liệu hàng hóa
    struct BSTNodeHangHoa* Left;  // Con trỏ trái
    struct BSTNodeHangHoa* Right; // Con trỏ phải
} BSTNodeHangHoa;

typedef BSTNodeHangHoa* TreeHangHoa; // Định nghĩa kiểu cho cây hàng hóa

// Các hàm thao tác với cây hàng hóa
BSTNodeHangHoa* taoNodeHangHoa(HangHoa hh);
void chenHangHoa(TreeHangHoa* root, HangHoa hh);
void duyetHangHoaLNR(TreeHangHoa root);
void hienThiHangHoa(HangHoa hh);
BSTNodeHangHoa* timHangHoa(TreeHangHoa root, const char* maHH);
TreeHangHoa xoaHangHoa(TreeHangHoa root, const char* maHH);
void ghiFileHangHoa(TreeHangHoa root, FILE* fp);
void docFileHangHoa(TreeHangHoa* root, const char* tenFile);
void giaiPhongHangHoa(TreeHangHoa root);

#endif
