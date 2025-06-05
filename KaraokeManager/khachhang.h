#ifndef KHACHHANG_H
#define KHACHHANG_H

#include <stdio.h>

// Định nghĩa cấu trúc KhachHang
typedef struct {
    char maKH[10];        // Mã khách hàng (tối đa 9 ký tự + null terminator)
    char tenKH[50];       // Tên khách hàng (tối đa 49 ký tự + null terminator)
    char sdt[15];         // Số điện thoại (tối đa 14 ký tự + null terminator)
} KhachHang;

// Định nghĩa cấu trúc node cho cây nhị phân tìm kiếm khách hàng
typedef struct BSTNodeKhachHang {
    KhachHang Info;          // Dữ liệu khách hàng
    struct BSTNodeKhachHang* Left;  // Con trỏ trái
    struct BSTNodeKhachHang* Right; // Con trỏ phải
} BSTNodeKhachHang;

typedef BSTNodeKhachHang* TreeKhachHang; // Định nghĩa kiểu cho cây khách hàng

// Các hàm thao tác với cây khách hàng
BSTNodeKhachHang* taoNodeKhachHang(KhachHang kh);
void chenKhachHang(TreeKhachHang* root, KhachHang kh);
void duyetKhachHangLNR(TreeKhachHang root);
void hienThiKhachHang(KhachHang kh);
BSTNodeKhachHang* timKhachHang(TreeKhachHang root, const char* maKH);
TreeKhachHang xoaKhachHang(TreeKhachHang root, const char* maKH);
void ghiFileKhachHang(TreeKhachHang root, FILE* fp);
void docFileKhachHang(TreeKhachHang* root, const char* tenFile);
void giaiPhongKhachHang(TreeKhachHang root);

// Hàm kiểm tra số điện thoại hợp lệ
int kiemTraSDT(const char* sdt);

#endif
