#include <iostream>
#include "Polynom.h"

int main(int argc, char* argv[]) {
  Polynom a(std::vector<double>({ 0, 0, 1 })),
          b(std::vector<double>({ 4.4, 0, 2 }));
  Polynom c = 3 * a;
  Polynom d = c - a;
  std::cout << a.ToString() << std::endl;
  std::cout << a.GetDegree() << std::endl;
  std::cout << c.ToString() << std::endl;
  std::cout << c.GetDegree() << std::endl;
  std::cout << d.ToString() << std::endl;
  std::cout << d.GetDegree() << std::endl;
  return 0;
}
