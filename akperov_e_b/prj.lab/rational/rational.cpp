#include <rational/rational.hpp>

Rational& Rational::operator=(const Rational& rhs)
{
    num_ = rhs.num_;
    denum_ = rhs.denum_;
    return *this;
}

Rational& Rational::operator=(const int32_t& rhs)
{
    num_ = rhs;
    denum_ = 1;
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.reduce_rational();
    return sum;
}

Rational operator+(const Rational& lhs, const int32_t& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    return sum;
}

Rational operator+(const int32_t& lhs, const Rational& rhs)
{
    Rational sum(rhs);
    sum += lhs;
    return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum -= rhs;
    sum.reduce_rational();
    return sum;
}

Rational operator-(const Rational& lhs, const int32_t& rhs)
{
    Rational sum(lhs);
    sum -= rhs;
    return sum;
}

Rational operator-(const int32_t& lhs, const Rational& rhs)
{
    Rational sum(rhs);
    sum -= lhs;
    return -sum;
}

Rational operator*(const Rational& lhs, const int32_t& rhs)
{
    Rational mul(lhs);
    mul *= rhs;
    mul.reduce_rational();
    return mul;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational mul(lhs);
    mul *= rhs;
    mul.reduce_rational();
    return mul;
}

Rational operator*(const int32_t& lhs, const Rational& rhs)
{
    Rational mul(rhs);
    mul *= lhs;
    mul.reduce_rational();
    return mul;
}

Rational operator/(const Rational& lhs, const int32_t& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.reduce_rational();
    return div;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.reduce_rational();
    return div;
}

Rational operator/(const int32_t& lhs, const Rational& rhs)
{
    Rational div(lhs,1);
    div /= rhs;
    div.reduce_rational();
    return div;
}

Rational operator-(const Rational& lhs)
{
    return lhs * (-1);
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num_ = num_ * rhs.denum_ + rhs.num_ * denum_;
    denum_ = rhs.denum_ * denum_;
    reduce_rational();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    num_ = num_ * rhs.denum_ - rhs.num_ * denum_;
    denum_ = rhs.denum_ * denum_;
    reduce_rational();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num_ = num_ * rhs.num_;
    denum_ = denum_ * rhs.denum_;
    reduce_rational();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    if (rhs.num_ != 0) {
        if (rhs.num_ < 0)
            *this *= Rational(-rhs.denum_, -rhs.num_);
        else 
            *this *= Rational(rhs.denum_, rhs.num_);
        reduce_rational();
        return *this;
    }
    else {
        throw division_by_zero;
    }
}

int Rational::nod()
{
    int32_t num = std::abs(num_);
    int32_t denum = denum_;
    while (num > 0 && denum > 0) {
        if (num > denum)
            num %= denum;
        else
            denum %= num;
    };
    return num + denum;
}

Rational& Rational::operator++(int) {
    num_ = num_ + denum_;
    return *this;
}

Rational& Rational::operator--(int) {
    num_ = num_ - denum_;
    return *this;
}

Rational& Rational::reduce_rational() {
    int32_t reduce_coef = nod();
    if (reduce_coef != 1) {
        num_ /= reduce_coef;
        denum_ /= reduce_coef;
    };
    return *this;
}

Rational::Rational(int32_t num, int32_t denum)
    : num_(num)
    , denum_(denum)
{
    if (denum_ == 0)
        throw division_by_zero;
    if (denum_ < 0)
        throw input_error;
    reduce_rational();
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
    ostrm << num_ << separator << denum_;
    return ostrm;
}
std::istream& Rational::readFrom(std::istream& istrm)
{
    int32_t numerator(0);
    char comma(0);
    int32_t denumerator(-1);
    istrm >> numerator >> comma >> denumerator;
    if (!istrm.eof() || denumerator < 0
        || Rational::separator != comma) {
        throw input_error;
    }
    else {
        if (denumerator == 0) {
            throw division_by_zero;
        }
        else {
            num_ = numerator;
            denum_ = denumerator;
            reduce_rational();
        }
        return istrm;
    }
}