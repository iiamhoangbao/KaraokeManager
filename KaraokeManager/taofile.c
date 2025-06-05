#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "phong.h"
#include "hoadon.h"
#include "khachhang.h"
#include "hanghoa.h"
#include "cthoadon.h"
#include "taofile.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

int fileDaTonTai(const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

void taoNgayNgauNhien(char* buffer) {
    int ngay = rand() % 28 + 1;
    int thang = rand() % 12 + 1;
    int nam = 2023 + rand() % 2;
    sprintf(buffer, "%02d/%02d/%04d", ngay, thang, nam);
}

void taoFilePhongMau(const char* tenFile) {
    if (fileDaTonTai(tenFile)) return;

    FILE* fp = fopen(tenFile, "wb");
    if (!fp) return;

    Phong p;
    for (int i = 1; i <= 20; i++) {
        sprintf(p.maPhong, "P%03d", i);
        sprintf(p.tenPhong, "Phong Karaoke %02d", i);
        strcpy(p.loaiPhong, (i % 2 == 0) ? "VIP" : "THUONG");
        p.trangThai = rand() % 2;
        p.soLuotDat = rand() % 50;
        p.gioThue = (strcmp(p.loaiPhong, "VIP") == 0) ? 200.0f : 100.0f;
        taoNgayNgauNhien(p.ngayThue);
        fwrite(&p, sizeof(Phong), 1, fp);
    }
    fclose(fp);
}

void taoFileHoaDonMau(const char* tenFile) {
    if (fileDaTonTai(tenFile)) return;

    FILE* fp = fopen(tenFile, "wb");
    if (!fp) return;

    srand(time(NULL));
    HoaDon hd;
    for (int i = 1; i <= 20; i++) {
        sprintf(hd.soHD, "HD%03d", i);
        sprintf(hd.maKH, "KH%03d", rand() % 20 + 1);
        sprintf(hd.maPhong, "P%03d", rand() % 20 + 1);
        taoNgayNgauNhien(hd.ngayThue);
        sprintf(hd.gioVao, "10:00");
        sprintf(hd.gioRa, "12:00");
        hd.tongTien = (rand() % 100 + 1) * 1000;
        fwrite(&hd, sizeof(HoaDon), 1, fp);
    }

    fclose(fp);
}

void taoFileKhachHangMau(const char* tenFile) {
    if (fileDaTonTai(tenFile)) return;

    FILE* fp = fopen(tenFile, "wb");
    if (!fp) return;

    KhachHang kh;
    for (int i = 1; i <= 20; i++) {
        sprintf(kh.maKH, "KH%03d", i);
        sprintf(kh.tenKH, "Khach Hang %03d", i);
        sprintf(kh.sdt, "0123456789");
        fwrite(&kh, sizeof(KhachHang), 1, fp);
    }
    fclose(fp);
}

void taoFileHangHoaMau(const char* tenFile) {
    if (fileDaTonTai(tenFile)) return;

    FILE* fp = fopen(tenFile, "wb");
    if (!fp) return;

    HangHoa hh;
    for (int i = 1; i <= 20; i++) {
        sprintf(hh.maHH, "HH%03d", i);
        sprintf(hh.tenHH, "Hang Hoa %03d", i);
        hh.donGia = (rand() % 100 + 1) * 10; // Giả định đơn giá ngẫu nhiên
        fwrite(&hh, sizeof(HangHoa), 1, fp);
    }
    fclose(fp);
}

void taoFileCTHoaDonMau(const char* tenFile) {
    if (fileDaTonTai(tenFile)) return;

    FILE* fp = fopen(tenFile, "wb");
    if (!fp) return;

    CTHoaDon ct;
    for (int i = 1; i <= 20; i++) {
        sprintf(ct.soHD, "HD%03d", rand() % 20 + 1);
        sprintf(ct.maHH, "HH%03d", rand() % 20 + 1);
        ct.soLuong = rand() % 10 + 1; // Số lượng ngẫu nhiên
        ct.thanhTien = ct.soLuong * (rand() % 100 + 1) * 10; // Tính thành tiền
        fwrite(&ct, sizeof(CTHoaDon), 1, fp);
    }
    fclose(fp);
}

void taoTatCaFileMau() {
    srand((unsigned)time(NULL));
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0777);
#endif
    taoFilePhongMau("data/phong.txt");
    taoFileHoaDonMau("data/hoadon.txt");
    taoFileKhachHangMau("data/khachhang.txt");
    taoFileHangHoaMau("data/hanghoa.txt");
    taoFileCTHoaDonMau("data/cthoadon.txt");
}
