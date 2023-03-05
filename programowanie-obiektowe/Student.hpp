#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int str_to_int(std::string token);

struct Student {
  std::string name = "";
  std::string surname = "";
  int index_number = 0;
  int birth_day = 0;
  int birth_month = 0;
  int birth_year = 0;

  Student() {}
  Student(Student *student);
  Student(std::string name, std::string surname, int index_number,
          int birth_day, int birth_month, int birth_year);
  Student(std::string csv_row);

  std::string serialize_to_csv();
};

void display_student(Student *student);

int read_student(Student *student);

#endif
