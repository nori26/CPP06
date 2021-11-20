#include <iostream>

#include "Scalar.hpp"

void validate() {}

void parse() {}

void output() {}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "invalid argument" << std::endl;
    return 1;
  }
  Scalar types;
  types.run(argv[1]);
}
