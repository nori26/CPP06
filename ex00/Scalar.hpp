#ifndef SCALAR_HPP
#define SCALAR_HPP
#include <limits>
#include <sstream>
#include <string>
class Scalar {
 private:
  typedef enum e {
    CHAR,
    INT,
    FLT,
    DBL,
    IMP,
  } e_type;
  e_type type;
  typedef struct bits {
    unsigned int mantl : 32;
    unsigned int mantu : 20;
    unsigned int exp : 11;
    unsigned int sign : 1;
  } b;

  typedef union dble {
    double d;
    b bit;
  } dbl;

  dbl d_;
  std::stringstream ss_c_;
  std::stringstream ss_i_;
  std::stringstream ss_f_;
  std::stringstream ss_d_;
  std::string input_;
  const static unsigned long expmax = 0x7ff;
  Scalar(Scalar const &other);
  Scalar &operator=(Scalar const &other);
  void parse_to_value();
  Scalar::e_type detect_type();
  bool isImp(e_type typ);
  void cast_to_dbl();
  void impossible();
  void to_str();
  void to_char();
  void to_int();
  void to_float();
  void to_double();
  void output();
  void calcPrec(std::string &s);

 public:
  Scalar();
  ~Scalar();
  void run(const std::string &input);

  template <typename TO, typename FROM>
  TO cast(FROM a) {
    return static_cast<TO>(a);
  }
  template <typename T>
  bool isOverlow() {
    return d_.d > std::numeric_limits<T>::max() ||
           d_.d < std::numeric_limits<T>::min();
  }
};

#endif

// template <typename T>
// T add(T a, T b) {
//   return a + b;
// }

// add<int>(1, 2);
