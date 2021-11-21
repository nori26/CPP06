#include <stdint.h>

#include <iomanip>
#include <iostream>

#include "Data.hpp"
Data* deserialize(uintptr_t raw) { return reinterpret_cast<Data*>(raw); }
uintptr_t serialize(Data* ptr) { return reinterpret_cast<uintptr_t>(ptr); }

int main() {
  Data d;
  Data* p;
  uintptr_t ptr;

  ptr = serialize(&d);
  std::cout << std::hex << "0x" << ptr << std::endl;
  p = deserialize(ptr);
  std::cout << std::hex << p << std::endl;
  std::cout << std::hex << &d << std::endl;
}
