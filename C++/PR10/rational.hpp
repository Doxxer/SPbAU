#include <iostream>

class Rational {
public:
    explicit Rational(int q = 0, int r = 1);
    void print(std::ostream &out) const;
    bool operator==(Rational const& num) const;
    bool operator<(Rational const& num) const;
    bool operator<=(Rational const& num) const;
    bool operator>(Rational const& num) const;
    bool operator>=(Rational const& num) const;

private:    
    int q_;
    int r_;
    
    void normalize();
};

std::ostream &operator<<(std::ostream &out, Rational const &num);
