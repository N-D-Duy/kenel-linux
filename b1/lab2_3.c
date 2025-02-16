#include <stdio.h>
#include <stdlib.h>

void displayFile(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "mycat: %s: No such file or directory\n", filename);
    return;
  }

  char buffer[4096];
  size_t bytesRead;

  while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    fwrite(buffer, 1, bytesRead, stdout);
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: mycat <filename>\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    displayFile(argv[i]);
  }

  return 0;
}
