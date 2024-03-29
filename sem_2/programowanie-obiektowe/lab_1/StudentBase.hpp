#ifndef STUDENT_BASE_HPP
#define STUDENT_BASE_HPP

#include <iostream>
#include <vector>

#include "Student.hpp"

#define INITIAL_CAPACITY 100

struct StudentBase {
  std::string faculty_name;
  std::vector<Student> students;

  StudentBase(std::string faculty_name);

  int add_student(Student student);
  void display_all();
};

int find_student(StudentBase *student_base, int index_number,
                 unsigned long *found);
int remove_student(StudentBase *student_base, int index_number);
int save_students(StudentBase *students, const char *file_name);
int load_students(StudentBase *students, const char *file_name);

#endif
