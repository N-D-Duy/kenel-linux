#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
  int id;
  char name[50];
  float gpa;
  char class[20];
};

struct StudentManagement {
  struct Student students[MAX_STUDENTS];
  int count;
};

void initializeSystem(struct StudentManagement *system) { system->count = 0; }

void addStudent(struct StudentManagement *system) {
  if (system->count >= MAX_STUDENTS) {
    printf("Danh sách đã đầy!\n");
    return;
  }

  struct Student newStudent;
  printf("\nNhập thông tin sinh viên mới:\n");
  printf("ID: ");
  scanf("%d", &newStudent.id);
  getchar(); // Xóa bộ nhớ đệm

  printf("Tên: ");
  fgets(newStudent.name, 50, stdin);
  newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Xóa ký tự newline

  printf("GPA: ");
  scanf("%f", &newStudent.gpa);
  getchar();

  printf("Lớp: ");
  fgets(newStudent.class, 20, stdin);
  newStudent.class[strcspn(newStudent.class, "\n")] = 0;

  system->students[system->count] = newStudent;
  system->count++;
  printf("Đã thêm sinh viên thành công!\n");
}

void displayStudents(struct StudentManagement *system) {
  if (system->count == 0) {
    printf("Danh sách sinh viên trống!\n");
    return;
  }

  printf("\nDanh sách sinh viên:\n");
  printf("ID\tTên\t\tGPA\tLớp\n");
  printf("----------------------------------------\n");

  for (int i = 0; i < system->count; i++) {
    printf("%d\t%-15s\t%.2f\t%s\n", system->students[i].id,
           system->students[i].name, system->students[i].gpa,
           system->students[i].class);
  }
}

void searchStudent(struct StudentManagement *system) {
  int searchId;
  printf("Nhập ID sinh viên cần tìm: ");
  scanf("%d", &searchId);

  for (int i = 0; i < system->count; i++) {
    if (system->students[i].id == searchId) {
      printf("\nTìm thấy sinh viên:\n");
      printf("ID: %d\n", system->students[i].id);
      printf("Tên: %s\n", system->students[i].name);
      printf("GPA: %.2f\n", system->students[i].gpa);
      printf("Lớp: %s\n", system->students[i].class);
      return;
    }
  }
  printf("Không tìm thấy sinh viên có ID: %d\n", searchId);
}

void deleteStudent(struct StudentManagement *system) {
  int deleteId;
  printf("Nhập ID sinh viên cần xóa: ");
  scanf("%d", &deleteId);

  for (int i = 0; i < system->count; i++) {
    if (system->students[i].id == deleteId) {
      // Di chuyển các phần tử sau lên một vị trí
      for (int j = i; j < system->count - 1; j++) {
        system->students[j] = system->students[j + 1];
      }
      system->count--;
      printf("Đã xóa sinh viên thành công!\n");
      return;
    }
  }
  printf("Không tìm thấy sinh viên có ID: %d\n", deleteId);
}

int main() {
  struct StudentManagement system;
  initializeSystem(&system);
  int choice;

  do {
    printf("\n=== QUẢN LÝ SINH VIÊN ===\n");
    printf("1. Thêm sinh viên\n");
    printf("2. Hiển thị danh sách sinh viên\n");
    printf("3. Tìm kiếm sinh viên\n");
    printf("4. Xóa sinh viên\n");
    printf("0. Thoát\n");
    printf("Nhập lựa chọn của bạn: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addStudent(&system);
      break;
    case 2:
      displayStudents(&system);
      break;
    case 3:
      searchStudent(&system);
      break;
    case 4:
      deleteStudent(&system);
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
