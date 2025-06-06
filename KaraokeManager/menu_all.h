#ifndef MENU_ALL_H
#define MENU_ALL_H

#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"

// Khai báo các hàm menu
void menuQuanLyPhong(TreePhong* rootPhong);
void menuQuanLyKhachHang(TreeKhachHang* rootKhachHang);
void menuQuanLyHangHoa(TreeHangHoa* rootHangHoa);
void menuQuanLyHoaDon(TreeHoaDon* rootHoaDon, TreeKhachHang* rootKhachHang,
    TreePhong* rootPhong, TreeCTHoaDon* rootCTHoaDon, TreeHangHoa* rootHangHoa);
void menuThongKe(TreeHoaDon rootHoaDon, TreePhong rootPhong);
void menuCaiDat(TreePhong* rootPhong, TreeHoaDon* rootHoaDon, TreeKhachHang* rootKhachHang,
    TreeHangHoa* rootHangHoa, TreeCTHoaDon* rootCTHoaDon);

#endif

