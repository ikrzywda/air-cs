#include "StudentBase.hpp"

StudentBase::StudentBase(std::string faculty_name) {
  this->faculty_name = faculty_name;
  students.reserve(INITIAL_CAPACITY);
}

int StudentBase::add_student(Student student) {
  this->students.push_back(student);
  return 1;
}

void StudentBase::display_all() {
  std::cout << "faculty name: " << this->faculty_name << '\n';
  for (auto student : this->students) {
    display_student(&student);
  }
}

int find_student(StudentBase *student_base, int index_number,
                 unsigned long *found) {
  if (student_base == nullptr) {
    return 0;
  }

  *found = -1;

  for (unsigned long i = 0; i < student_base->students.size(); i++) {
    if (student_base->students[i].index_number == index_number) {
      *found = i;
      break;
    }
  }

  return *found < student_base->students.size() && *found > 0;
}

int remove_student(StudentBase *student_base, int index_number) {
  unsigned long found_index;
  if (find_student(student_base, index_number, &found_index)) {
    student_base->students.erase(student_base->students.begin() + found_index);
    return 1;
  }
  return 0;
}

int write_students_to_file(StudentBase *students, const char *file_name) {
  std::ofstream out(file_name);
  for (auto student : students->students) {
    out << student.serialize_to_csv() << "\n";
  }
  out.close();
  return 1;
}

int read_students_from_file(StudentBase *students, const char *file_name) {
  std::ifstream in(file_name);
  std::string line;
  Student student;

  if (!in.good()) {
    in.close();
    return 0;
  }

  // OP:
  // https://stackoverflow.com/questions/8046357/how-do-i-check-if-a-stringstream-variable-is-empty-null
  while (getline(in, line)) {
    std::cout << line << std::endl;
    students->students.push_back(Student(line));
  }

  in.close();
  return 1;
}
