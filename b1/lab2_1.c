#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.dat"

struct Student {
  char id[10];
  char name[50];
  char class[20];
  float gpa;
};

// 1. Tạo danh sách sinh viên và lưu vào file
void createStudentList() {
  FILE *fp = fopen(FILENAME, "wb");
  if (fp == NULL) {
    printf("Không thể tạo file!\n");
    return;
  }

  struct Student sv;
  char continue_input;

  do {
    printf("\nNhập thông tin sinh viên:\n");
    printf("MSSV: ");
    scanf("%s", sv.id);
    getchar();

    printf("Tên: ");
    fgets(sv.name, sizeof(sv.name), stdin);
    sv.name[strcspn(sv.name, "\n")] = 0;

    printf("Lớp: ");
    scanf("%s", sv.class);

    printf("GPA: ");
    scanf("%f", &sv.gpa);

    fwrite(&sv, sizeof(struct Student), 1, fp);

    printf("Tiếp tục nhập? (y/n): ");
    scanf(" %c", &continue_input);
  } while (continue_input == 'y' || continue_input == 'Y');

  fclose(fp);
  printf("Đã lưu danh sách sinh viên vào file!\n");
}

// 2. Tìm kiếm sinh viên
void searchStudent() {
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  char search_id[10];
  printf("Nhập MSSV cần tìm: ");
  scanf("%s", search_id);

  struct Student sv;
  int found = 0;

  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    if (strcmp(sv.id, search_id) == 0) {
      printf("\nThông tin sinh viên:\n");
      printf("MSSV: %s\n", sv.id);
      printf("Tên: %s\n", sv.name);
      printf("Lớp: %s\n", sv.class);
      printf("GPA: %.2f\n", sv.gpa);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Không tìm thấy sinh viên!\n");
  }

  fclose(fp);
}

// 3. Hiển thị danh sách sinh viên theo lớp
void displayByClass() {
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  char class_name[20];
  printf("Nhập tên lớp cần hiển thị: ");
  scanf("%s", class_name);

  struct Student sv;
  int found = 0;

  printf("\nDanh sách sinh viên lớp %s:\n", class_name);
  printf("MSSV\tTên\t\tGPA\n");
  printf("--------------------------------\n");

  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    if (strcmp(sv.class, class_name) == 0) {
      printf("%s\t%-20s\t%.2f\n", sv.id, sv.name, sv.gpa);
      found = 1;
    }
  }

  if (!found) {
    printf("Không có sinh viên nào trong lớp này!\n");
  }

  fclose(fp);
}

// 4. Tách file theo lớp
void splitByClass() {
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  struct Student sv;
  char classes[MAX_STUDENTS][20];
  int class_count = 0;

  // Tìm danh sách các lớp độc nhất
  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    int exists = 0;
    for (int i = 0; i < class_count; i++) {
      if (strcmp(classes[i], sv.class) == 0) {
        exists = 1;
        break;
      }
    }
    if (!exists) {
      strcpy(classes[class_count], sv.class);
      class_count++;
    }
  }

  // Tạo file cho từng lớp
  rewind(fp);
  for (int i = 0; i < class_count; i++) {
    char filename[30];
    sprintf(filename, "%s.dat", classes[i]);
    FILE *class_fp = fopen(filename, "wb");

    rewind(fp);
    while (fread(&sv, sizeof(struct Student), 1, fp)) {
      if (strcmp(sv.class, classes[i]) == 0) {
        fwrite(&sv, sizeof(struct Student), 1, class_fp);
      }
    }

    fclose(class_fp);
    printf("Đã tạo file %s\n", filename);
  }

  fclose(fp);
}

// 5. Thêm sinh viên mới
void addStudent() {
  FILE *fp = fopen(FILENAME, "ab");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  struct Student sv;
  printf("\nNhập thông tin sinh viên mới:\n");
  printf("MSSV: ");
  scanf("%s", sv.id);
  getchar();

  printf("Tên: ");
  fgets(sv.name, sizeof(sv.name), stdin);
  sv.name[strcspn(sv.name, "\n")] = 0;

  printf("Lớp: ");
  scanf("%s", sv.class);

  printf("GPA: ");
  scanf("%f", &sv.gpa);

  fwrite(&sv, sizeof(struct Student), 1, fp);
  fclose(fp);

  printf("Đã thêm sinh viên mới!\n");
}

// 6. Sửa thông tin sinh viên
void editStudent() {
  FILE *fp = fopen(FILENAME, "rb+");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  char edit_id[10];
  printf("Nhập MSSV cần sửa: ");
  scanf("%s", edit_id);

  struct Student sv;
  int found = 0;
  long pos;

  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    if (strcmp(sv.id, edit_id) == 0) {
      printf("\nNhập thông tin mới:\n");
      getchar();

      printf("Tên (%s): ", sv.name);
      fgets(sv.name, sizeof(sv.name), stdin);
      sv.name[strcspn(sv.name, "\n")] = 0;

      printf("Lớp (%s): ", sv.class);
      scanf("%s", sv.class);

      printf("GPA (%.2f): ", sv.gpa);
      scanf("%f", &sv.gpa);

      pos = ftell(fp) - sizeof(struct Student);
      fseek(fp, pos, SEEK_SET);
      fwrite(&sv, sizeof(struct Student), 1, fp);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Không tìm thấy sinh viên!\n");
  } else {
    printf("Đã cập nhật thông tin sinh viên!\n");
  }

  fclose(fp);
}

// 7. Loại bỏ sinh viên
void removeStudent() {
  FILE *fp = fopen(FILENAME, "rb");
  FILE *temp = fopen("temp.dat", "wb");
  if (fp == NULL || temp == NULL) {
    printf("Lỗi file!\n");
    return;
  }

  char remove_id[10];
  printf("Nhập MSSV cần xóa: ");
  scanf("%s", remove_id);

  struct Student sv;
  int found = 0;

  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    if (strcmp(sv.id, remove_id) != 0) {
      fwrite(&sv, sizeof(struct Student), 1, temp);
    } else {
      found = 1;
    }
  }

  fclose(fp);
  fclose(temp);

  if (found) {
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    printf("Đã xóa sinh viên!\n");
  } else {
    remove("temp.dat");
    printf("Không tìm thấy sinh viên!\n");
  }
}

// 8. Sắp xếp danh sách sinh viên theo GPA
void sortStudents() {
  FILE *fp = fopen(FILENAME, "rb+");
  if (fp == NULL) {
    printf("Không thể mở file!\n");
    return;
  }

  struct Student *students = NULL;
  struct Student sv;
  int count = 0;

  // Đọc tất cả sinh viên vào mảng
  while (fread(&sv, sizeof(struct Student), 1, fp)) {
    count++;
    students = realloc(students, count * sizeof(struct Student));
    students[count - 1] = sv;
  }

  // Sắp xếp theo GPA (giảm dần)
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (students[j].gpa < students[j + 1].gpa) {
        struct Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }

  // Ghi lại vào file
  rewind(fp);
  for (int i = 0; i < count; i++) {
    fwrite(&students[i], sizeof(struct Student), 1, fp);
  }

  free(students);
  fclose(fp);

  printf("Đã sắp xếp danh sách theo GPA!\n");
}

int main() {
  int choice;
  do {
    printf("\n=== QUẢN LÝ SINH VIÊN ===\n");
    printf("1. Tạo danh sách sinh viên\n");
    printf("2. Tìm kiếm sinh viên\n");
    printf("3. Hiển thị danh sách theo lớp\n");
    printf("4. Tách file theo lớp\n");
    printf("5. Thêm sinh viên mới\n");
    printf("6. Sửa thông tin sinh viên\n");
    printf("7. Xóa sinh viên\n");
    printf("8. Sắp xếp danh sách\n");
    printf("0. Thoát\n");
    printf("Chọn chức năng: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      createStudentList();
      break;
    case 2:
      searchStudent();
      break;
    case 3:
      displayByClass();
      break;
    case 4:
      splitByClass();
      break;
    case 5:
      addStudent();
      break;
    case 6:
      editStudent();
      break;
    case 7:
      removeStudent();
      break;
    case 8:
      sortStudents();
      break;
    case 0:
      printf("Tạm biệt!\n");
      break;
    default:
      printf("Lựa chọn không hợp lệ!\n");
    }
  } while (choice != 0);

  return 0;
}
