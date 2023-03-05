#include "Student.hpp"
#include "StudentBase.hpp"

void display_all_students(Student student_arr[], int length) {
  for (int i = 0; i < length; i++) {
    display_student(&student_arr[i]);
  }
}

std::string rand_string(int length) {
  std::string out;
  for (int i = 0; i < length; i++) {
    out.push_back((rand() % ('Z' - 'A')) + 'A');
  }

  return out;
}

Student student_fixture() {
  return Student(rand_string(10), rand_string(11), rand() % 100000, rand() % 30,
                 rand() % 12, rand() % 2000);
}

int main() {
  Student student_1("Jacek", "Placek", 213900, 10, 11, 2002);
  Student student_2("Franek", "Bajederka", 312290, 11, 12, 2005);

  display_student(&student_1);
  display_student(&student_2);

  Student student_3;
  read_student(&student_3);
  display_student(&student_3);

  Student student_array_1[5] = {student_1, student_2, student_fixture(),
                                student_fixture(), student_fixture()};

  Student student_array_2[2] = {student_fixture(), student_fixture()};

  display_all_students(student_array_1, 5);
  display_all_students(student_array_2, 2);

  StudentBase student_base("PWR");

  for (int i = 0; i < 10; ++i) {
    student_base.add_student(Student(student_fixture()));
  }
  student_base.add_student(student_1);

  student_base.display_all();

  unsigned long found_std_index;

  if (find_student(&student_base, student_1.index_number, &found_std_index)) {
    std::cout << "FOUND: \n";
    display_student(&student_base.students[found_std_index]);
  }

  // write_students_to_file(&student_base, "test.txt");

  remove_student(&student_base, student_1.index_number);

  if (!find_student(&student_base, student_1.index_number, &found_std_index)) {
    std::cout << "NOT FOUND!\n";
  }

  StudentBase student_base_2("PWR_2");
  read_students_from_file(&student_base_2, "test.txt");
  student_base_2.display_all();
  // display_student(&student_base_2.students[2]);
  return 0;
}
