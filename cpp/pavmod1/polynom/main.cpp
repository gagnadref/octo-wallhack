#include <iostream>
#include "Polynom.h"

int main(int argc, char* argv[]) {
  Polynom a(std::vector<double>(0.1, 3)),
          b(std::vector<double>(1, 4));
  a += b;
  std::cout << a.ToString() << std::endl;
  std::cout << a.GetDegree() << std::endl;
  std::cout << b.ToString() << std::endl;
  std::cout << b.GetDegree() << std::endl;
  return 0;
}
