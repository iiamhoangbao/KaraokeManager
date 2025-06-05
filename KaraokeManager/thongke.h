#ifndef THONGKE_H
#define THONGKE_H

#include "hoadon.h"
#include "phong.h"

// Struct thống kê phòng
typedef struct {
    char maPhong[10];
    int soLanThue;
} ThongKePhong;

// Struct để lưu kết quả thống kê
typedef struct {
    double tongTien;
    int soHoaDon;
} KetQuaThongKe;

// Hàm so sánh ngày
int soSanhNgay(const char* ngay1, const char* ngay2);

// Hàm thống kê doanh thu theo ngày
void thongKeDoanhThuTheoNgay(TreeHoaDon root, const char* ngay);

// Hàm thống kê doanh thu theo tháng
void thongKeDoanhThuTheoThang(TreeHoaDon root, const char* thang);

// Hàm thống kê doanh thu theo năm
void thongKeDoanhThuTheoNam(TreeHoaDon root, const char* nam);

// Hàm thống kê doanh thu theo khoảng thời gian
void thongKeDoanhThuTheoKhoang(TreeHoaDon root, const char* ngayTu, const char* ngayDen);

// Hàm thống kê top 3 phòng được thuê nhiều nhất
void top3PhongDuocThueNhieuNhat(TreeHoaDon root);

// Hàm hiển thị hóa đơn theo mã khách hàng
void hienThiHoaDonTheoMaKH(TreeHoaDon root, const char* maKH);

// Hàm thống kê phòng theo loại
void thongKePhongTheoLoai(TreePhong root);

// Hàm báo cáo tổng quan
void baoCaoTongQuan(TreeHoaDon rootHoaDon, TreePhong rootPhong);

#endif
