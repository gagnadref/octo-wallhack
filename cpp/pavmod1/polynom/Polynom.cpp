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

Polynom Polynom::operator*=(const double factor) {
  for (auto it = this->coeffs.begin(); it != this->coeffs.end(); it++) {
    *it = *it * factor;
  } 
  return *this;
}

Polynom Polynom::operator-=(const Polynom& p) {
  return *this += (-1) * p;
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

Polynom operator+(const Polynom& a, const Polynom& b) {
  Polynom temp(a);
  return temp += b;
}

Polynom operator*(const double factor, const Polynom& p) {
  Polynom temp(p);
  return temp *= factor;
}

Polynom operator-(const Polynom& a, const Polynom& b) {
  Polynom temp(a);
  return temp -= b;
}
