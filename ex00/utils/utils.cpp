#include <string>

namespace ft {

bool is_number(const std::string &str) {
  return str.size() &&
         str.find_first_not_of("-0123456789") == std::string::npos;
}

}  // namespace ft
