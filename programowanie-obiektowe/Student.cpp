#include "Student.hpp"

int str_to_int(std::string token) {
  try {
    return std::stoi(token);
  } catch (std::invalid_argument &exception) {
    std::cerr << "invalid argument" << exception.what() << '\n';
    return -1;
  }
  return -1;
}

Student::Student(Student *student) { *this = *student; }

Student::Student(std::string name, std::string surname, int index_number,
                 int birth_day, int birth_month, int birth_year) {
  this->name = name;
  this->surname = surname;
  this->index_number = index_number;
  this->birth_day = birth_day;
  this->birth_month = birth_month;
  this->birth_year = birth_year;
}

Student::Student(std::string csv_row) {
  std::stringstream string_stream(csv_row);
  std::string current_token;

  if (std::getline(string_stream, current_token, ',')) {
    name = current_token;
  }

  if (std::getline(string_stream, current_token, ',')) {
    surname = current_token;
  }

  if (std::getline(string_stream, current_token, ',')) {
    index_number = str_to_int(current_token);
  }

  if (std::getline(string_stream, current_token, ',')) {
    birth_day = str_to_int(current_token);
  }

  if (std::getline(string_stream, current_token, ',')) {
    birth_month = str_to_int(current_token);
  }

  if (std::getline(string_stream, current_token, ',')) {
    birth_year = str_to_int(current_token);
  }
}

std::string Student::serialize_to_csv() {
  std::string out;
  out += this->name + ",";
  out += this->surname + ",";
  out += std::to_string(this->index_number) + ",";
  out += std::to_string(this->birth_day) + ",";
  out += std::to_string(this->birth_month) + ",";
  out += std::to_string(this->birth_year);

  return out;
}

void display_student(Student *student) {
  std::cout << "name: " << student->name << '\n';
  std::cout << "surname: " << student->surname << '\n';
  std::cout << "index: " << student->index_number << '\n';
  std::cout << "birth date: ";
  std::cout << student->birth_day << "-" << student->birth_month << "-"
            << student->birth_year << "\n\n";
}

int read_student(Student *student) {
  std::string itnermediate_string;

  std::cout << "Name: ";
  std::cin >> student->name;

  std::cout << "\nSurname: ";
  std::cin >> student->surname;

  std::cout << "\nIndex Number: ";
  std::cin >> itnermediate_string;
  student->index_number = str_to_int(itnermediate_string);

  std::cout << "\nBirth (Day): ";
  std::cin >> itnermediate_string;
  student->birth_day = str_to_int(itnermediate_string);

  std::cout << "\nBirth (Month): ";
  std::cin >> itnermediate_string;
  student->birth_month = str_to_int(itnermediate_string);

  std::cout << "\nBirth (Year): ";
  std::cin >> itnermediate_string;
  student->birth_year = str_to_int(itnermediate_string);

  return 1;
}
