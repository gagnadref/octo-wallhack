#include <iostream>

int64_t factorial_rec(int n);
int64_t factorial_iter(int n);

int main() {
    std::cout << "Factorial rec:" << std::endl;

    for(int i = 0; i < 20; i++) {
        std::cout << i << "! : " << factorial_rec(i) << std::endl;
    }

    std::cout << "Factorial iter:" << std::endl;
    for(int i = 0; i < 20; i++) {
        std::cout << i << "! : " << factorial_rec(i) << std::endl;
    }    
    factorial_rec(-1);
    return 0;
}

int64_t factorial_rec(int n) {
    if (n < 0) {
        throw "negative number";
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }
    return n * factorial_rec(n-1);
}

int64_t factorial_iter(int n) {
    if (n < 0) {
        throw "negative number";
    }
    unsigned int result = 1;
    for (unsigned int i = 1; i < n; i++) {
        result = result * i; 
    }
    return result;
}
