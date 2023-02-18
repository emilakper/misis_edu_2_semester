#include <sstream>

#pragma once
#ifndef RATIONAL_RATIONAL_HPP_20230218
#define RATIONAL_RATIONAL_HPP_20230218

const std::exception division_by_zero("Error: Division by zero");
const std::exception input_error("Error: Not correct format of input");

class Rational {
public:
    Rational() = default;
    Rational(const Rational&) = default;
    Rational(int32_t num, int32_t denum);
    ~Rational() = default;

    Rational& operator=(const Rational& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator+=(const int32_t rhs) { return operator+=(Rational(rhs, 1)); }
    Rational& operator-=(const Rational& rhs);
    Rational& operator-=(const int32_t rhs) { return operator-=(Rational(rhs, 1)); }
    Rational& operator*=(const Rational& rhs);
    Rational& operator*=(const int32_t rhs) { return operator*=(Rational(rhs, 1)); }
    Rational& operator/=(const Rational& rhs);
    Rational& operator/=(const int32_t rhs) { return operator/=(Rational(rhs, 1)); }
    Rational& operator++(int);
    Rational& operator--(int);

    bool operator==(const Rational& rhs) const {
        return (num_ == rhs.num_)
            && (denum_ == rhs.denum_);
    }
    bool operator==(const int32_t& rhs) const {
        return (num_ == rhs)
            && (denum_ == 1);
    }
    bool operator!=(const Rational& rhs) const { return !operator==(rhs); }
    bool operator!=(const int32_t& rhs) const { return !operator==(rhs); }
    bool operator>(const Rational& rhs) const {
        return
            num_ * rhs.denum_ - rhs.num_ * denum_ > 0;
    };
    bool operator>(const int32_t& rhs) const {
        return
            num_  - rhs * denum_ > 0;
    };
    bool operator<(const Rational& rhs) const {
        return
            num_ * rhs.denum_ - rhs.num_ * denum_ < 0;
    };
    bool operator<(const int32_t& rhs) const {
        return
            num_ - rhs * denum_ < 0;
    };
    bool operator<=(const Rational& rhs) const { return !operator>(rhs); }
    bool operator<=(const int32_t& rhs) const { return !operator>(rhs); }
    bool operator>=(const Rational& rhs) const { return !operator<(rhs); }
    bool operator>=(const int32_t& rhs) const { return !operator<(rhs); }

    int nod();
    Rational& reduce_rational();

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);
private:
    int32_t num_{ 0 };
    int32_t denum_{ 1 };
    static const char separator{ '/' };
};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational& lhs, const int32_t& rhs);
Rational operator+(const int32_t& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const int32_t& rhs);
Rational operator-(const int32_t& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const int32_t& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator*(const int32_t& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const int32_t& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator/(const int32_t& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}

#endif