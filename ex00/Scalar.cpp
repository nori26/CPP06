#include "Scalar.hpp"

#include <stdlib.h>
#define GREEN_BOLD_UNDERLINE "\x1b[32;1;4m"
#define RESET "\x1b[39;0m"

#include <cerrno>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

Scalar::Scalar() : d_() {}

Scalar::~Scalar() {}

Scalar::Scalar(Scalar const &other) { *this = other; }

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
  cast_to_dbl();
  to_str();
  output();
}

Scalar::e_type Scalar::detect_type() {
  if (!input_.size()) {
    return IMP;
  }
  char last = input_.at(input_.size() - 1);

  if (input_.size() == 1 && !isdigit(last)) {
    return CHAR;
  }
  if (input_.find(".", 0) != std::string::npos) {
    if (last == 'f') {
      return FLT;
    }
    return DBL;
  }
  if (input_ == "-inff" || input_ == "+inff" || input_ == "nanf") {
    return FLT;
  };
  if (input_ == "-inf" || input_ == "+inf" || input_ == "nan") {
    return DBL;
  }
  return INT;
}

void Scalar::parse_to_value() {
  char *error;
  errno = 0;

  switch (type) {
    case IMP:
      return;
    case CHAR:
      d_.d = cast<double, char>(input_.at(input_.size() - 1));
      return;
    case FLT:
      input_ = input_.substr(0, input_.size() - 1);
    default:
      d_.d = strtod(input_.c_str(), &error);
  }
  char last_char = input_.at(input_.size() - 1);

  if (errno || *error || isImp(type) || last_char == '.' || input_ == "-nan" ||
      input_ == "inf") {
    type = IMP;
  }
}

bool Scalar::isImp(e_type typ) {
  switch (typ) {
    case CHAR:
      return d_.bit.exp == expmax || isOverlow<char>();
    case INT:
      return d_.bit.exp == expmax || isOverlow<int>();
    default:
      return false;
  }
}

void Scalar::cast_to_dbl() {
  switch (type) {
    case INT:
      d_.d = cast<int, double>(d_.d);
      break;
    case FLT:
      d_.d = cast<float, double>(d_.d);
      break;
    default:
      return;
  }
}

void Scalar::to_str() {
  switch (type) {
    case IMP:
      impossible();
      break;
    default:
      to_char();
      to_int();
      to_float();
      to_double();
  }
}

void Scalar::impossible() {
  ss_c_ << "impossible";
  ss_i_ << "impossible";
  ss_f_ << "impossible";
  ss_d_ << "impossible";
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

void Scalar::to_char() {
  if (type == CHAR) {
    ss_c_ << GREEN_BOLD_UNDERLINE;
  }
  if (isImp(CHAR)) {
    ss_c_ << "impossible";
    return;
  }
  if (!isprint(static_cast<char>(d_.d))) {
    ss_c_ << "Non displayable";
    return;
  }
  ss_c_ << static_cast<char>(d_.d);
}

void Scalar::to_int() {
  if (type == INT) {
    ss_i_ << GREEN_BOLD_UNDERLINE;
  }
  if (isImp(INT)) {
    ss_i_ << "impossible";
    return;
  }
  ss_i_ << static_cast<int>(d_.d);
}

void Scalar::to_float() {
  if (type == FLT) {
    ss_f_ << GREEN_BOLD_UNDERLINE;
  }
  ss_f_ << std::fixed << static_cast<float>(d_.d) << "f";
}

void Scalar::to_double() {
  if (type == DBL) {
    ss_d_ << GREEN_BOLD_UNDERLINE;
  }
  ss_d_ << std::fixed << d_.d;
}
