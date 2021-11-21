#ifndef DATA_HPP
#define DATA_HPP
#include <string>

class Data {
 private:
  int i;
  std::string s;

 public:
  Data();
  ~Data();
  Data(Data const &other);
  Data &operator=(Data const &other);
};

#endif
