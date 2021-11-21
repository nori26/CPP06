#include "utils.hpp"

#include <string>
namespace ft {

bool is_signed_number(const std::string &str) {
  std::string tmp;

  if (str[0] == '-' || str[0] == '+') {
    tmp = str.substr(1, str.size());
  } else {
    tmp = str;
  }
  return is_number(tmp);
}

bool is_number(const std::string &str) {
  return str.size() && str.find_first_not_of("0123456789") == std::string::npos;
}

}  // namespace ft
