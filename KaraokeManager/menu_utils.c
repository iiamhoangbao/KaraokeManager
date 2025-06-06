#include <stdio.h>
#include <stdlib.h>

void xoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void dungManHinh() {
    printf("\n\033[1;36mNhan Enter de tiep tuc...\033[0m");
    while (getchar() != '\n');  // Làm sạch bộ đệm
    getchar();
}
