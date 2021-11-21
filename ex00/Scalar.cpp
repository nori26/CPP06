#include "Scalar.hpp"

#include <stdlib.h>

#include "utils.hpp"
#define GREEN_BOLD_UNDERLINE "\x1b[32;1;4m"
#define RESET "\x1b[39;0m"

#include <cerrno>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
Scalar::Scalar(const int precision) : d_(), precision_(precision) {}

Scalar::~Scalar() {}

Scalar::Scalar(Scalar const &other) : precision_(other.precision_) {
  *this = other;
}

Scalar &Scalar::operator=(Scalar const &other) {
  if (this == &other) {
    return *this;
  }
  return *this;
}

void Scalar::run(const std::string &input) {
  input_ = input;
  type = detect_type();
  parse_to_value();
  to_str();
  output();
}

Scalar::e_type Scalar::detect_type() {
  if (ft::is_number(input_)) {
    return INT;
  }
  if (input_.size() == 3 && input_[0] == '\'' && input_[2] == '\'') {
    return CHAR;
  }
  if (input_ == "-inff" || input_ == "+inff" || input_ == "nanf") {
    return FLT;
  };
  if (input_ == "-inf" || input_ == "+inf" || input_ == "nan") {
    return DBL;
  }
  if (input_.find(".", 0) != std::string::npos) {
    if (input_.at(input_.size() - 1) == 'f') {
      return FLT;
    }
    return DBL;
  }
  return IMP;
}

void Scalar::parse_to_value() {
  if (type == FLT) {
    input_ = input_.substr(0, input_.size() - 1);
  }
  if (type != CHAR) {
    type = parse_to_double();
  };
  switch (type) {
    case IMP:
      return;
    case CHAR:
      to_char_val();
      return;
    case INT:
      to_int_val();
      return;
    case FLT:
      to_float_val();
      return;
    case DBL:
      to_double_val();
      return;
    default:
      return;
  }
}

Scalar::e_type Scalar::parse_to_double() {
  if (!input_.size()) {
    return IMP;
  }
  char last_char = input_.at(input_.size() - 1);
  char *error;

  d_.d = strtod(input_.c_str(), &error);
  if (*error || last_char == '.') {
    return IMP;
  }
  return type;
}

void Scalar::to_char_val() {
  ss_c_ << GREEN_BOLD_UNDERLINE;
  char c = input_[1];
  d_.d = c;
}

void Scalar::to_int_val() {
  ss_i_ << GREEN_BOLD_UNDERLINE;
  if (isOverlow<int>()) {
    type = IMP;
    return;
  };
  int i = static_cast<int>(d_.d);
  d_.d = i;
}

void Scalar::to_float_val() {
  ss_f_ << GREEN_BOLD_UNDERLINE;
  float f = static_cast<float>(d_.d);
  d_.d = f;
}

void Scalar::to_double_val() { ss_d_ << GREEN_BOLD_UNDERLINE; }

void Scalar::to_str() {
  switch (type) {
    case IMP:
      impossible();
      break;
    default:
      char_to_str();
      int_to_str();
      float_to_str();
      double_to_str();
  }
}

void Scalar::impossible() {
  ss_c_ << "impossible";
  ss_i_ << "impossible";
  ss_f_ << "impossible";
  ss_d_ << "impossible";
}

void Scalar::char_to_str() {
  if (d_.bit.exp == expmax || isOverlow<char>()) {
    ss_c_ << "impossible";
    return;
  }
  if (!isprint(static_cast<char>(d_.d))) {
    ss_c_ << "Non displayable";
    return;
  }
  ss_c_ << "'" << static_cast<char>(d_.d) << "'";
}

void Scalar::int_to_str() {
  if (d_.bit.exp == expmax || isOverlow<int>()) {
    ss_i_ << "impossible";
    return;
  }
  ss_i_ << static_cast<int>(d_.d);
}

void Scalar::float_to_str() {
  std::string s;
  f_to_str<float>(s);
  ss_f_ << s << "f";
}

void Scalar::double_to_str() {
  std::string s;
  f_to_str<double>(s);
  ss_d_ << s;
}

void Scalar::calcPrec(std::string &s) {
  size_t place = s.find_last_not_of("0");
  s = s.substr(0, place + 1);
  if (s[s.size() - 1] == '.') {
    s += "0";
  }
}

void Scalar::output() {
  std::cout << std::left << std::setw(8) << "char"
            << ": " << ss_c_.str() << RESET << std::endl;
  std::cout << std::left << std::setw(8) << "int"
            << ": " << ss_i_.str() << RESET << std::endl;
  std::cout << std::left << std::setw(8) << "float"
            << ": " << ss_f_.str() << RESET << std::endl;
  std::cout << std::left << std::setw(8) << "double"
            << ": " << ss_d_.str() << RESET << std::endl;
}
