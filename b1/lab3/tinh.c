#include "hinhtron.h"
#include "hinhvuong.h"
#include "tamgiac.h"
#include <stdio.h>

int main() {
  int luaChon;
  float a, b, c, canh, banKinh;

  do {
    printf("\nMENU CHUC NANG:\n");
    printf("1. Tinh chu vi va dien tich tam giac\n");
    printf("2. Tinh chu vi va dien tich hinh vuong\n");
    printf("3. Tinh chu vi va dien tich hinh tron\n");
    printf("4. Ket thuc\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &luaChon);

    switch (luaChon) {
    case 1:
      printf("Nhap 3 canh tam giac (a b c): ");
      scanf("%f %f %f", &a, &b, &c);
      printf("Chu vi tam giac: %.2f\n", tinhChuViTamGiac(a, b, c));
      printf("Dien tich tam giac: %.2f\n", tinhDienTichTamGiac(a, b, c));
      break;

    case 2:
      printf("Nhap canh hinh vuong: ");
      scanf("%f", &canh);
      printf("Chu vi hinh vuong: %.2f\n", tinhChuViHinhVuong(canh));
      printf("Dien tich hinh vuong: %.2f\n", tinhDienTichHinhVuong(canh));
      break;

    case 3:
      printf("Nhap ban kinh hinh tron: ");
      scanf("%f", &banKinh);
      printf("Chu vi hinh tron: %.2f\n", tinhChuViHinhTron(banKinh));
      printf("Dien tich hinh tron: %.2f\n", tinhDienTichHinhTron(banKinh));
      break;

    case 4:
      printf("Tam biet!\n");
      break;

    default:
      printf("Lua chon khong hop le!\n");
    }
  } while (luaChon != 4);

  return 0;
}
