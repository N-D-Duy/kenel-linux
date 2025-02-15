#include <stdio.h>
#include <string.h>

void findSubstring(const char *str, const char *substr) {
  char *pos = strstr(str, substr);
  if (pos) {
    printf("Chuoi con tim thay tai vi tri: %ld\n", pos - str);
  } else {
    printf("Chuoi con khong ton tai trong chuoi chinh.\n");
  }
}

int main() {
  char str[100] = "Hello, this is a sample string.";
  char substr[20] = "sample";

  findSubstring(str, substr);

  return 0;
}
