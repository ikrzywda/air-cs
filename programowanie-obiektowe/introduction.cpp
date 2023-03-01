#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INITIAL_CAPACITY 100

struct Student {
  std::string name = "";
  std::string surname = "";
  int index_number = 0;
  int birth_day = 0;
  int birth_month = 0;
  int birth_year = 0;

  Student() {}

  Student(std::string name, std::string surname, int index_number,
          int birth_day, int birth_month, int birth_year) {
    this->name = name;
    this->surname = surname;
    this->index_number = index_number;
    this->birth_day = birth_day;
    this->birth_month = birth_month;
    this->birth_year = birth_year;
  }

  Student(Student *student) {
    this->name = student->name;
    this->surname = student->surname;
    this->index_number = student->index_number;
    this->birth_day = student->birth_day;
    this->birth_month = student->birth_month;
    this->birth_year = student->birth_year;
  }

  std::string serialize_to_txt() {
    std::string out;
    out += this->name + "\n";
    out += this->surname + "\n";
    out += std::to_string(this->index_number) + "\n";
    out += std::to_string(this->birth_day) + "\n";
    out += std::to_string(this->birth_month) + "\n";
    out += std::to_string(this->birth_year) + "\n";

    return out;
  }
};

void display_student(Student *student) {
  std::cout << "name: " << student->name << '\n';
  std::cout << "surname: " << student->surname << '\n';
  std::cout << "index: " << student->index_number << '\n';
  std::cout << "birth date: ";
  std::cout << student->birth_day << "-" << student->birth_month << "-"
            << student->birth_year << "\n\n";
}

void display_all_students(Student student_arr[], int length) {
  for (int i = 0; i < length; i++) {
    display_student(&student_arr[i]);
  }
}

Student *read_student_from_file_stream(Student *student,
                                       std::ifstream *stream) {
  *stream >> student->name;
  *stream >> student->surname;
  *stream >> student->index_number;
  *stream >> student->birth_day;
  *stream >> student->birth_month;
  *stream >> student->birth_year;
}

struct StudentBase {
  std::string faculty_name;
  std::vector<Student> students;

  StudentBase(std::string faculty_name) {
    this->faculty_name = faculty_name;
    students.reserve(INITIAL_CAPACITY);
  }

  int add_student(Student student) {
    this->students.push_back(student);
    return 1;
  }

  void display_all() {
    std::cout << "faculty name: " << this->faculty_name << '\n';
    for (auto student : this->students) {
      display_student(&student);
    }
  }
};

std::string rand_string(int length) {

  std::string out;
  for (int i = 0; i < length; i++) {
    out.push_back((rand() % ('Z' - 'A')) + 'A');
  }

  return out;
}

Student *mock_student() {
  return new Student(rand_string(10), rand_string(11), rand() % 100000,
                     rand() % 30, rand() % 12, rand() % 2000);
}

Student *read_student() {
  Student *student = new Student;
  std::cin >> student->name;
  std::cin >> student->surname;
  std::cin >> student->index_number;
  std::cin >> student->birth_day;
  std::cin >> student->birth_month;
  std::cin >> student->birth_year;

  return student;
}

int find_student(StudentBase *student_base, int index_number, int *found) {
  if (student_base == nullptr) {
    return 0;
  }

  *found = -1;

  for (int i = 0; i < student_base->students.size(); i++) {
    if (student_base->students[i].index_number == index_number) {
      *found = i;
      break;
    }
  }

  return *found < student_base->students.size() && *found > 0;
}

int remove_student(StudentBase *student_base, int index_number) {
  int found_index;
  if (find_student(student_base, index_number, &found_index)) {
    student_base->students.erase(student_base->students.begin() + found_index);
  }
}

int write_students_to_file(StudentBase *students, const char *file_name) {
  std::ofstream out(file_name);
  for (auto student : students->students) {
    out << student.serialize_to_txt();
  }
  out.close();
  return 1;
}

int read_students_from_file(StudentBase *students, const char *file_name) {
  std::ifstream in(file_name);
  Student student;

  // OP:
  // https://stackoverflow.com/questions/8046357/how-do-i-check-if-a-stringstream-variable-is-empty-null
  while (!in.eof()) {
    read_student_from_file_stream(&student, &in);

    students->students.push_back(Student(&student));
  }

  in.close();
}

int main() {
  Student student_1("Jacek", "Placek", 213900, 10, 11, 2002);
  Student student_2("Franek", "Bajederka", 312290, 11, 12, 2005);

  display_student(&student_1);
  display_student(&student_2);

  Student *student_3 = read_student();
  display_student(student_3);

  Student student_array_1[5] = {student_1, student_2, Student(mock_student()),
                                Student(mock_student()),
                                Student(mock_student())};

  Student student_array_2[2] = {Student(mock_student()),
                                Student(mock_student())};

  display_all_students(student_array_1, 5);
  display_all_students(student_array_2, 2);

  StudentBase student_base("PWR");

  for (int i = 0; i < 10; ++i) {
    student_base.add_student(Student(mock_student()));
  }
  student_base.add_student(student_1);

  student_base.display_all();

  int found_std_index;

  if (find_student(&student_base, student_1.index_number, &found_std_index)) {
    std::cout << "FOUND: \n";
    display_student(&student_base.students[found_std_index]);
  }

  write_students_to_file(&student_base, "test.txt");

  remove_student(&student_base, student_1.index_number);

  if (!find_student(&student_base, student_1.index_number, &found_std_index)) {
    std::cout << "NOT FOUND!\n";
  }

  StudentBase student_base_2("PWR_2");
  read_students_from_file(&student_base_2, "test.txt");
  student_base_2.display_all();

  return 0;
}
