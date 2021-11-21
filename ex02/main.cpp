#include <cstdlib>
#include <ctime>
#include <iostream>

#include "classes.hpp"
void identify(Base *p) {
  if (dynamic_cast<A *>(p)) {
    std::cout << "A" << std::endl;
  } else if (dynamic_cast<B *>(p)) {
    std::cout << "B" << std::endl;
  } else if (dynamic_cast<C *>(p)) {
    std::cout << "C" << std::endl;
  }
}
void identify(Base &p) {
  try {
    (void)dynamic_cast<A &>(p);
    std::cout << "A" << std::endl;
  } catch (std::exception &e) {
    try {
      (void)dynamic_cast<B &>(p);
      std::cout << "B" << std::endl;
    } catch (std::exception &e) {
      (void)dynamic_cast<C &>(p);
      std::cout << "C" << std::endl;
    }
  }
}

Base *generate(void) {
  std::time_t t = std::time(NULL);
  const tm *local = std::localtime(&t);

  std::srand(local->tm_sec);
  if (std::rand() % 3 == 0) {
    std::cout << "A" << std::endl;
    return new A();
  } else if (std::rand() % 3 == 1) {
    std::cout << "B" << std::endl;
    ;
    return new B();
  } else {
    std::cout << "C" << std::endl;
    return new C();
  }
}
int main() {
  Base *p = generate();
  identify(p);
  identify(*p);
  delete p;
}
