#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *file;
  long position;
  char content[] = "Đây là dòng 1.\nĐây là dòng 2.\nĐây là dòng 3.\nĐây là "
                   "dòng 4.\nĐây là dòng 5.";

  file = fopen("test.txt", "w");
  if (file == NULL) {
    printf("Không thể tạo file!\n");
    return 1;
  }

  fputs(content, file);
  fclose(file);
  printf("Đã tạo file test.txt với nội dung:\n%s\n\n", content);

  file = fopen("test.txt", "r");
  if (file == NULL) {
    printf("Không thể mở file!\n");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  printf("Kích thước file: %ld bytes\n", file_size);
  printf("Nhập vị trí muốn đọc (0-%ld): ", file_size - 1);
  scanf("%ld", &position);

  if (position < 0 || position >= file_size) {
    printf("Vị trí không hợp lệ!\n");
    fclose(file);
    return 1;
  }

  fseek(file, position, SEEK_SET);

  printf("\nNội dung từ vị trí %ld:\n", position);
  int c;
  while ((c = fgetc(file)) != EOF) {
    putchar(c);
  }
  printf("\n");

  fclose(file);
  return 0;
}
