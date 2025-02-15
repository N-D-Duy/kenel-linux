#include <stdio.h>

void createAdjacentSumArray(int a[], int b[], int n) {
  for (int i = 0; i < n; i++) {
    b[i] = 0;
    if (i > 0) {
      b[i] += a[i - 1];
    }
    if (i < n - 1) {
      b[i] += a[i + 1];
    }
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5};
  int n = sizeof(a) / sizeof(a[0]);
  int b[n];
  printf("Mảng a: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
  }
  createAdjacentSumArray(a, b, n);

  printf("Mảng b: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
  }
  printf("\n");

  return 0;
}
