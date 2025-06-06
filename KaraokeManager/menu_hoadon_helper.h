#ifndef MENU_HOADON_HELPER_H
#define MENU_HOADON_HELPER_H

#include "cthoadon.h"
#include "hanghoa.h"

void themHangHoaVaoHoaDon(TreeCTHoaDon* rootCTHoaDon, TreeHangHoa* rootHangHoa,
    const char* soHD, double* tongTien);
double tinhTongTienHangHoa(TreeCTHoaDon root, const char* soHD);
void xoaTatCaCTHoaDonTheoSoHD(TreeCTHoaDon* root, const char* soHD);

#endif

