#include <stdio.h>

void sortMatrix(float matrix[][100], int rows, int cols) {
  int size = rows * cols;
  float temp[size];
  int k = 0;

  // Chuyển ma trận thành mảng 1D
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      temp[k++] = matrix[i][j];
    }
  }

  // Sắp xếp mảng 1D
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (temp[i] > temp[j]) {
        float swap = temp[i];
        temp[i] = temp[j];
        temp[j] = swap;
      }
    }
  }

  // Chuyển mảng 1D trở lại ma trận
  k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = temp[k++];
    }
  }
}

void printMatrix(float matrix[][100], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%.2f ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  float matrix[100][100] = {{3.2, 1.5, 4.8}, {9.1, 2.3, 5.6}, {7.4, 6.8, 0.9}};
  int rows = 3, cols = 3;

  printf("Ma tran ban dau:\n");
  printMatrix(matrix, rows, cols);

  sortMatrix(matrix, rows, cols);

  printf("\nMa tran sau khi sap xep:\n");
  printMatrix(matrix, rows, cols);

  return 0;
}
