#include "tamgiac.h"
#include <math.h>

float tinhChuViTamGiac(float a, float b, float c) { return a + b + c; }

float tinhDienTichTamGiac(float a, float b, float c) {
  float p = (a + b + c) / 2;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}
