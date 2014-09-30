#include <vector>
#include <string>

class Polynom {
  private:
    std::vector<double> coeffs;

  public:
    Polynom(std::vector<double> inputCoeffs);
    ~Polynom();
    int GetDegree() const;
    Polynom operator+=(const Polynom& p);
    Polynom operator*=(double factor);
    Polynom operator-=(const Polynom& p);
    std::string ToString() const;
};

Polynom operator+(const Polynom& a, const Polynom& b);
Polynom operator*(const double factor, const Polynom& p);
Polynom operator-(const Polynom& a, const Polynom& b);
