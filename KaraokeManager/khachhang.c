#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "khachhang.h"

// Kiểm tra số điện thoại hợp lệ của Việt Nam
int kiemTraSDT(const char* sdt) {
    // Kiểm tra độ dài
    int len = strlen(sdt);
    if (len != 10) {
        return 0; // Số điện thoại phải có đúng 10 chữ số
    }

    // Kiểm tra tất cả là chữ số
    for (int i = 0; i < len; i++) {
        if (sdt[i] < '0' || sdt[i] > '9') {
            return 0; // Không phải chữ số
        }
    }

    // Kiểm tra bắt đầu bằng 0
    if (sdt[0] != '0') {
        return 0;
    }

    // Lấy 3 số đầu để kiểm tra
    char dauSo[4];
    strncpy(dauSo, sdt, 3);
    dauSo[3] = '\0';

    // Danh sách đầu số hợp lệ
    const char* dauSoHopLe[] = {
        // Viettel
        "032", "033", "034", "035", "036", "037", "038", "039",
        "086", "096", "097", "098",
        // Vinaphone
        "081", "082", "083", "084", "085", "088",
        "091", "094",
        // Mobifone
        "070", "076", "077", "078", "079",
        "089", "090", "093",
        // Vietnamobile
        "052", "056", "058", "092",
        // Gmobile
        "099", "059",
        // Một số đầu số cố định phổ biến
        "024", "028", "020", "021", "022", "023", "025", "026", "027", "029",
        NULL
    };

    // Kiểm tra đầu số có hợp lệ không
    for (int i = 0; dauSoHopLe[i] != NULL; i++) {
        if (strcmp(dauSo, dauSoHopLe[i]) == 0) {
            return 1; // Đầu số hợp lệ
        }
    }

    return 0; // Đầu số không hợp lệ
}

// Tạo node mới cho cây khách hàng
BSTNodeKhachHang* taoNodeKhachHang(KhachHang kh) {
    BSTNodeKhachHang* node = (BSTNodeKhachHang*)malloc(sizeof(BSTNodeKhachHang));
    if (!node) {
        printf("\033[1;31m[X] Khong du bo nho de tao node moi!\033[0m\n");
        return NULL;
    }
    node->Info = kh;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

// Chèn khách hàng vào cây
void chenKhachHang(TreeKhachHang* root, KhachHang kh) {
    if (*root == NULL) {
        *root = taoNodeKhachHang(kh);
        return;
    }

    int cmp = strcmp(kh.maKH, (*root)->Info.maKH);
    if (cmp < 0) {
        chenKhachHang(&((*root)->Left), kh);
    }
    else if (cmp > 0) {
        chenKhachHang(&((*root)->Right), kh);
    }
    else {
        printf("\033[1;31m[X] Khong the them: Ma khach hang %s da ton tai!\033[0m\n", kh.maKH);
    }
}

// Duyệt cây theo thứ tự LNR
void duyetKhachHangLNR(TreeKhachHang root) {
    if (root != NULL) {
        duyetKhachHangLNR(root->Left);
        hienThiKhachHang(root->Info);
        duyetKhachHangLNR(root->Right);
    }
}

// Hiển thị thông tin khách hàng
void hienThiKhachHang(KhachHang kh) {
    printf("\033[1;36m+-----------------------------------------------------------------------+\033[0m\n");
    printf("\033[1;33m| Ma KH: \033[1;37m%-10s\033[1;33m | Ten khach hang:\033[1;37m%-35s\033[1;33m|\033[0m\n",
        kh.maKH, kh.tenKH);
    printf("\033[1;33m| So dien thoai: \033[1;37m%-15s\033[1;33m                                        |\033[0m\n",
        kh.sdt);
    printf("\033[1;36m+-----------------------------------------------------------------------+\033[0m\n");
}

// Tìm khách hàng theo mã
BSTNodeKhachHang* timKhachHang(TreeKhachHang root, const char* maKH) {
    if (root == NULL) return NULL;

    int cmp = strcmp(maKH, root->Info.maKH);
    if (cmp == 0) return root;
    if (cmp < 0) return timKhachHang(root->Left, maKH);
    return timKhachHang(root->Right, maKH);
}

// Xóa khách hàng khỏi cây
TreeKhachHang xoaKhachHang(TreeKhachHang root, const char* maKH) {
    if (root == NULL) return NULL;

    int cmp = strcmp(maKH, root->Info.maKH);
    if (cmp < 0) {
        root->Left = xoaKhachHang(root->Left, maKH);
    }
    else if (cmp > 0) {
        root->Right = xoaKhachHang(root->Right, maKH);
    }
    else {
        if (root->Left == NULL) {
            BSTNodeKhachHang* temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) {
            BSTNodeKhachHang* temp = root->Left;
            free(root);
            return temp;
        }

        BSTNodeKhachHang* temp = root->Right;
        while (temp && temp->Left != NULL) {
            temp = temp->Left;
        }

        root->Info = temp->Info;
        root->Right = xoaKhachHang(root->Right, temp->Info.maKH);
    }
    return root;
}

// Ghi cây vào file
void ghiFileKhachHang(TreeKhachHang root, FILE* fp) {
    if (root != NULL) {
        fwrite(&(root->Info), sizeof(KhachHang), 1, fp);
        ghiFileKhachHang(root->Left, fp);
        ghiFileKhachHang(root->Right, fp);
    }
}

// Đọc file vào cây
void docFileKhachHang(TreeKhachHang* root, const char* tenFile) {
    FILE* fp = fopen(tenFile, "rb");
    if (!fp) return;

    KhachHang kh;
    while (fread(&kh, sizeof(KhachHang), 1, fp)) {
        chenKhachHang(root, kh);
    }
    fclose(fp);
}

// Giải phóng bộ nhớ cho cây
void giaiPhongKhachHang(TreeKhachHang root) {
    if (root != NULL) {
        giaiPhongKhachHang(root->Left);
        giaiPhongKhachHang(root->Right);
        free(root);
    }
}

