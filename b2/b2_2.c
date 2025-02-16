#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define FOLDER_PATH "/home/dnd/workspace/kernel-linux/"

void listFiles(const char *path) {
  struct dirent *entry;
  struct stat fileStat;
  char filePath[1024];
  DIR *dir = opendir(path);

  if (dir == NULL) {
    perror("Không thể mở thư mục");
    return;
  }

  printf("%-30s %-10s %-25s\n", "Tên File", "Size (bytes)", "Modify Time");
  printf("-------------------------------------------------------------\n");

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) { // Chỉ lấy file thường
      snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);

      if (stat(filePath, &fileStat) == 0) {
        printf("%-30s %-10ld %s", entry->d_name, fileStat.st_size,
               ctime(&fileStat.st_mtime));
      }
    }
  }
  closedir(dir);
}

int main() {
  printf("Thông tin file trong thư mục: %s\n\n", FOLDER_PATH);
  listFiles(FOLDER_PATH);
  return 0;
}
