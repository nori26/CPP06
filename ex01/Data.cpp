#include "Data.hpp"

#include <limits.h>
Data::Data() {
  s = "nop";
  i = INT_MAX;
}

Data::~Data() {}

Data::Data(Data const &other) { *this = other; }

Data &Data::operator=(Data const &other) {
  if (this == &other) {
    return *this;
  }
  s = other.s;
  i = other.i;
  return *this;
}
