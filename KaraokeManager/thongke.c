#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thongke.h"
#include "hoadon.h"
#include "phong.h"

// So sánh ngày trả về 1 nếu ngày1 <= ngày2, 0 nếu ngược lại
int soSanhNgay(const char* ngay1, const char* ngay2) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(ngay1, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(ngay2, "%d/%d/%d", &d2, &m2, &y2);

    if (y1 < y2) return 1;
    if (y1 > y2) return 0;
    if (m1 < m2) return 1;
    if (m1 > m2) return 0;
    return d1 <= d2;
}

// Hàm hỗ trợ đệ quy để thống kê theo ngày
void thongKeTheoNgayHelper(TreeHoaDon root, const char* ngay, KetQuaThongKe* ketQua) {
    if (root == NULL) return;

    thongKeTheoNgayHelper(root->Left, ngay, ketQua);

    if (strcmp(root->Info.ngayThue, ngay) == 0) {
        ketQua->tongTien += root->Info.tongTien;
        ketQua->soHoaDon++;
    }

    thongKeTheoNgayHelper(root->Right, ngay, ketQua);
}

// Thống kê doanh thu theo ngày
void thongKeDoanhThuTheoNgay(TreeHoaDon root, const char* ngay) {
    KetQuaThongKe ketQua = { 0, 0 };

    thongKeTheoNgayHelper(root, ngay, &ketQua);

    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| THONG KE DOANH THU NGAY %s    |\033[0m\n", ngay);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| So hoa don: \033[1;37m%3d\033[1;33m                       |\033[0m\n", ketQua.soHoaDon);
    printf("\033[1;33m| Tong doanh thu: \033[1;32m%12.2lf VND\033[1;33m   |\033[0m\n", ketQua.tongTien);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

// Hàm hỗ trợ đệ quy để thống kê theo tháng
void thongKeTheoThangHelper(TreeHoaDon root, const char* thang, KetQuaThongKe* ketQua) {
    if (root == NULL) return;

    thongKeTheoThangHelper(root->Left, thang, ketQua);

    char thangHD[3];
    int thangInt;
    sscanf(root->Info.ngayThue, "%*d/%d/%*d", &thangInt);
    sprintf(thangHD, "%02d", thangInt);

    if (strcmp(thangHD, thang) == 0) {
        ketQua->tongTien += root->Info.tongTien;
        ketQua->soHoaDon++;
    }

    thongKeTheoThangHelper(root->Right, thang, ketQua);
}

// Thống kê doanh thu theo tháng
void thongKeDoanhThuTheoThang(TreeHoaDon root, const char* thang) {
    KetQuaThongKe ketQua = { 0, 0 };

    thongKeTheoThangHelper(root, thang, &ketQua);

    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m|   THONG KE DOANH THU THANG %s         |\033[0m\n", thang);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| So hoa don: \033[1;37m%3d\033[1;33m                       |\033[0m\n", ketQua.soHoaDon);
    printf("\033[1;33m| Tong doanh thu: \033[1;32m%12.2lf VND\033[1;33m   |\033[0m\n", ketQua.tongTien);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

// Hàm hỗ trợ đệ quy để thống kê theo năm
void thongKeTheoNamHelper(TreeHoaDon root, const char* nam, KetQuaThongKe* ketQua) {
    if (root == NULL) return;

    thongKeTheoNamHelper(root->Left, nam, ketQua);

    char namHD[5];
    int namInt;
    sscanf(root->Info.ngayThue, "%*d/%*d/%d", &namInt);
    sprintf(namHD, "%04d", namInt);

    if (strcmp(namHD, nam) == 0) {
        ketQua->tongTien += root->Info.tongTien;
        ketQua->soHoaDon++;
    }

    thongKeTheoNamHelper(root->Right, nam, ketQua);
}

// Thống kê doanh thu theo năm
void thongKeDoanhThuTheoNam(TreeHoaDon root, const char* nam) {
    KetQuaThongKe ketQua = { 0, 0 };

    thongKeTheoNamHelper(root, nam, &ketQua);

    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m|    THONG KE DOANH THU NAM %s        |\033[0m\n", nam);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| So hoa don: \033[1;37m%3d\033[1;33m                       |\033[0m\n", ketQua.soHoaDon);
    printf("\033[1;33m| Tong doanh thu: \033[1;32m%12.2lf VND\033[1;33m   |\033[0m\n", ketQua.tongTien);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

// Hàm hỗ trợ đệ quy để thống kê theo khoảng
void thongKeTheoKhoangHelper(TreeHoaDon root, const char* ngayTu, const char* ngayDen, KetQuaThongKe* ketQua) {
    if (root == NULL) return;

    thongKeTheoKhoangHelper(root->Left, ngayTu, ngayDen, ketQua);

    if (soSanhNgay(ngayTu, root->Info.ngayThue) && soSanhNgay(root->Info.ngayThue, ngayDen)) {
        ketQua->tongTien += root->Info.tongTien;
        ketQua->soHoaDon++;
    }

    thongKeTheoKhoangHelper(root->Right, ngayTu, ngayDen, ketQua);
}

// Thống kê doanh thu theo khoảng thời gian
void thongKeDoanhThuTheoKhoang(TreeHoaDon root, const char* ngayTu, const char* ngayDen) {
    KetQuaThongKe ketQua = { 0, 0 };

    thongKeTheoKhoangHelper(root, ngayTu, ngayDen, &ketQua);

    printf("\033[1;36m+--------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| THONG KE TU %s DEN %s            |\033[0m\n", ngayTu, ngayDen);
    printf("\033[1;36m+--------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| So hoa don: \033[1;37m%3d\033[1;33m                                 |\033[0m\n", ketQua.soHoaDon);
    printf("\033[1;33m| Tong doanh thu: \033[1;32m%12.2lf VND\033[1;33m             |\033[0m\n", ketQua.tongTien);
    printf("\033[1;36m+--------------------------------------------------+\033[0m\n");
}

// Đếm số lần thuê phòng
void demSoLanThuePhong(TreeHoaDon root, ThongKePhong thongKePhong[], int* soPhong) {
    if (root == NULL) return;

    demSoLanThuePhong(root->Left, thongKePhong, soPhong);

    int i;
    for (i = 0; i < *soPhong; i++) {
        if (strcmp(thongKePhong[i].maPhong, root->Info.maPhong) == 0) {
            thongKePhong[i].soLanThue++;
            break;
        }
    }
    if (i == *soPhong) {
        strcpy(thongKePhong[*soPhong].maPhong, root->Info.maPhong);
        thongKePhong[*soPhong].soLanThue = 1;
        (*soPhong)++;
    }

    demSoLanThuePhong(root->Right, thongKePhong, soPhong);
}

// So sánh phòng để sắp xếp
int soSanhPhong(const void* a, const void* b) {
    const ThongKePhong* p1 = (const ThongKePhong*)a;
    const ThongKePhong* p2 = (const ThongKePhong*)b;
    return p2->soLanThue - p1->soLanThue;
}

// Top 3 phòng được thuê nhiều nhất
void top3PhongDuocThueNhieuNhat(TreeHoaDon root) {
    ThongKePhong thongKePhong[100];
    int soPhong = 0;

    demSoLanThuePhong(root, thongKePhong, &soPhong);

    if (soPhong == 0) {
        printf("\033[1;31m⚠️  Khong co du lieu phong!\033[0m\n");
        return;
    }

    qsort(thongKePhong, soPhong, sizeof(ThongKePhong), soSanhPhong);

    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m|    TOP 3 PHONG DUOC THUE NHIEU NHAT   |\033[0m\n");
    printf("\033[1;36m+----------------------------------------+\033[0m\n");

    for (int i = 0; i < soPhong && i < 3; i++) {
        printf("\033[1;33m| \033[1;31m%d.\033[1;33m Ma phong: \033[1;37m%-8s\033[1;33m So lan: \033[1;32m%3d\033[1;33m      |\033[0m\n",
            i + 1, thongKePhong[i].maPhong, thongKePhong[i].soLanThue);
    }
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

// Hiển thị hóa đơn theo mã khách hàng
void hienThiHoaDonTheoMaKH(TreeHoaDon root, const char* maKH) {
    if (root == NULL) return;

    hienThiHoaDonTheoMaKH(root->Left, maKH);

    if (strcmp(root->Info.maKH, maKH) == 0) {
        hienThiHoaDon(root->Info);
    }

    hienThiHoaDonTheoMaKH(root->Right, maKH);
}

// Hàm hỗ trợ đếm phòng theo loại
void demPhongTheoLoaiHelper(TreePhong root, int* soPhongVIP, int* soPhongThuong) {
    if (root == NULL) return;

    demPhongTheoLoaiHelper(root->Left, soPhongVIP, soPhongThuong);

    if (strcmp(root->Info.loaiPhong, "VIP") == 0) {
        (*soPhongVIP)++;
    }
    else {
        (*soPhongThuong)++;
    }

    demPhongTheoLoaiHelper(root->Right, soPhongVIP, soPhongThuong);
}

// Thống kê phòng theo loại
void thongKePhongTheoLoai(TreePhong root) {
    int soPhongVIP = 0;
    int soPhongThuong = 0;

    demPhongTheoLoaiHelper(root, &soPhongVIP, &soPhongThuong);

    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m|        THONG KE PHONG THEO LOAI        |\033[0m\n");
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| Phong VIP:     \033[1;37m%3d\033[1;33m phong              |\033[0m\n", soPhongVIP);
    printf("\033[1;33m| Phong Thuong:  \033[1;37m%3d\033[1;33m phong              |\033[0m\n", soPhongThuong);
    printf("\033[1;33m| Tong cong:     \033[1;32m%3d\033[1;33m phong              |\033[0m\n", soPhongVIP + soPhongThuong);
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

// Hàm hỗ trợ đếm hóa đơn
void demHoaDon(TreeHoaDon root, int* tongHoaDon, double* tongDoanhThu) {
    if (root == NULL) return;

    demHoaDon(root->Left, tongHoaDon, tongDoanhThu);
    (*tongHoaDon)++;
    *tongDoanhThu += root->Info.tongTien;
    demHoaDon(root->Right, tongHoaDon, tongDoanhThu);
}

// Hàm hỗ trợ đếm phòng
void demPhong(TreePhong root, int* tongPhong) {
    if (root == NULL) return;

    demPhong(root->Left, tongPhong);
    (*tongPhong)++;
    demPhong(root->Right, tongPhong);
}

// Báo cáo tổng quan
void baoCaoTongQuan(TreeHoaDon rootHoaDon, TreePhong rootPhong) {
    int tongHoaDon = 0;
    double tongDoanhThu = 0.0;
    int tongPhong = 0;

    // Đếm hóa đơn và doanh thu
    demHoaDon(rootHoaDon, &tongHoaDon, &tongDoanhThu);

    // Đếm phòng
    demPhong(rootPhong, &tongPhong);

    // Hiển thị báo cáo
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m|         BAO CAO TONG QUAN              |\033[0m\n");
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
    printf("\033[1;33m| Tong so phong:        \033[1;37m%3d\033[1;33m phong       |\033[0m\n", tongPhong);
    printf("\033[1;33m| Tong so hoa don:      \033[1;37m%3d\033[1;33m hoa don     |\033[0m\n", tongHoaDon);
    printf("\033[1;33m| Tong doanh thu:    \033[1;32m%10.2f VND\033[1;33m     |\033[0m\n", tongDoanhThu);

    if (tongHoaDon > 0) {
        printf("\033[1;33m| Doanh thu TB/HD:   \033[1;32m%10.2f VND\033[1;33m     |\033[0m\n", tongDoanhThu / tongHoaDon);
    }
    else {
        printf("\033[1;33m| Doanh thu TB/HD:   \033[1;32m      0.00 VND\033[1;33m     |\033[0m\n");
    }

    if (tongPhong > 0) {
        printf("\033[1;33m| Doanh thu TB/phong:\033[1;32m%10.2f VND\033[1;33m     |\033[0m\n", tongDoanhThu / tongPhong);
    }
    else {
        printf("\033[1;33m| Doanh thu TB/phong:\033[1;32m      0.00 VND\033[1;33m     |\033[0m\n");
    }
    printf("\033[1;36m+----------------------------------------+\033[0m\n");
}

