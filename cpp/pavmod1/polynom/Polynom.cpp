#include "Polynom.h"
#include <sstream>
#include <iostream>

Polynom::Polynom(std::vector<double> inputCoeffs) : coeffs(inputCoeffs) {
  int i(this->coeffs.size());
  if (i == 0) {
    return;
  }
  while(i > 0 && this->coeffs[i-1] == 0) {
    i--;
  }
  this->coeffs.resize(i);
}

Polynom::~Polynom() {
}

int Polynom::GetDegree() const {
  return this->coeffs.size() - 1;
}

Polynom Polynom::operator+=(const Polynom& p) {
  if (p.coeffs.size() > this->coeffs.size()) {
    this->coeffs.resize(p.coeffs.size());
  }
  for(int i = 0; i < this->coeffs.size(); i++) {
    this->coeffs[i] = this->coeffs[i] + p.coeffs[i];
  }
  return *this;
}

std::string Polynom::ToString() const {
  std::ostringstream res;
  for(int i = 0; i < this->coeffs.size(); i++) {
    res << this->coeffs[i];
    if (i != 0) {
      res << "x^" << i; 
    }
    if (i < this->coeffs.size() - 1) {
      res << " + ";
    }
  }
  return res.str();
}
