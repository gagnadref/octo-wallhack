#include <iostream>
#include "Polynom.h"

int main(int argc, char* argv[]) {
  Polynom a(std::vector<double>({ 3.3, 4, 5.5 })),
          b(std::vector<double>({ 4.4, 0, 2 }));
  a += b;
  std::cout << a.ToString() << std::endl;
  std::cout << a.GetDegree() << std::endl;
  std::cout << b.ToString() << std::endl;
  std::cout << b.GetDegree() << std::endl;
  return 0;
}
