#ifndef HOADON_H
#define HOADON_H

#include <stdio.h>

// Định nghĩa cấu trúc HoaDon
typedef struct {
    char soHD[10];         // Số hóa đơn (tối đa 9 ký tự + null terminator)
    char maKH[10];         // Mã khách hàng (tối đa 9 ký tự + null terminator)
    char maPhong[10];      // Mã phòng (tối đa 9 ký tự + null terminator)
    char ngayThue[11];     // Ngày thuê (định dạng "dd/mm/yyyy")
    char gioVao[6];        // Giờ vào (định dạng "hh:mm")
    char gioRa[6];         // Giờ ra (định dạng "hh:mm")
    double tongTien;       // Tổng tiền thanh toán
} HoaDon;

// Định nghĩa cấu trúc node cho cây nhị phân tìm kiếm hóa đơn
typedef struct BSTNodeHoaDon {
    HoaDon Info;           // Dữ liệu hóa đơn
    struct BSTNodeHoaDon* Left;  // Con trỏ trái
    struct BSTNodeHoaDon* Right; // Con trỏ phải
} BSTNodeHoaDon;

typedef BSTNodeHoaDon* TreeHoaDon; // Định nghĩa kiểu cho cây hóa đơn

// Các hàm thao tác với cây hóa đơn
BSTNodeHoaDon* taoNodeHoaDon(HoaDon hd);
void chenHoaDon(TreeHoaDon* root, HoaDon hd);
void duyetHoaDonLNR(TreeHoaDon root);
void hienThiHoaDon(HoaDon hd);
BSTNodeHoaDon* timHoaDon(TreeHoaDon root, const char* soHD);
TreeHoaDon xoaHoaDon(TreeHoaDon root, const char* soHD);
void ghiFileHoaDon(TreeHoaDon root, FILE* fp);
void docFileHoaDon(TreeHoaDon* root, const char* tenFile);
void giaiPhongHoaDon(TreeHoaDon root);

#endif
