#include <cassert>
#include "rational.hpp"

Rational::Rational(int q, int r) : q_(q), r_(r)
{
    normalize();
}

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

void Rational::normalize()
{
    assert(r_ != 0);
    int g = gcd(abs(q_), abs(r_));
    q_ /= g;
    r_ /= g;
}

bool Rational::operator==(Rational const &num) const
{
    return (q_ == num.q_ && r_ == num.r_);
}

bool Rational::operator<(Rational const &num) const
{
        
}

void Rational::print(std::ostream &out) const
{
    out << q_ << "/" << r_;
}

std::ostream &operator<<(std::ostream &out, Rational const &num)
{
    num.print(out);
    return out;
}
