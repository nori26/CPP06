#ifndef SCALAR_HPP
#define SCALAR_HPP
#include <iomanip>
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
  const int precision_;
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
  void impossible();
  Scalar::e_type parse_to_double();
  void to_char_val();
  void to_int_val();
  void to_float_val();
  void to_double_val();
  void to_str();
  void char_to_str();
  void int_to_str();
  void float_to_str();
  void double_to_str();
  void output();
  void calcPrec(std::string &s);

 public:
  Scalar(const int precision = 1500);
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
  template <typename T>
  void ft_to_str(std::string &s) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision_) << static_cast<T>(d_.d);
    ss >> s;
    calcPrec(s);
  }
};

#endif

// template <typename T>
// T add(T a, T b) {
//   return a + b;
// }

// add<int>(1, 2);
