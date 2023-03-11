#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>
/*
Rational InputRational(const std::string& str, Rational& rat)
{
	std::istringstream istrm(str);
	istrm >> rat;
	return rat;
}

TEST_CASE("Testing ctor") {
	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(10, 6) == Rational(5, 3));
	CHECK(Rational(-10, 6) == Rational(-5, 3));
	CHECK(Rational(-5) == Rational(-5, 1));
	CHECK(Rational(10, -6) == Rational(-5, 3));
	CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("Testing Math Operator +") {
  CHECK(Rational(2, 3)+Rational(1, 2) == Rational(7, 6));
  CHECK(Rational(4,3)+Rational(1,2) == Rational(11,6));
  CHECK(Rational(5, 2) + 2 == Rational(9, 2));
  CHECK(2 + Rational(5, 2) == Rational(9, 2));
}

TEST_CASE("Testing Math Operator -") {
	CHECK(Rational(2, 3) - Rational(1, 2) == Rational(1, 6));
	CHECK(Rational(4, 3) - Rational(1, 2) == Rational(5, 6));
	CHECK(Rational(5, 2) - 2 == Rational(1, 2));
	CHECK(2 - Rational(5, 2) == Rational(-1, 2));
}

TEST_CASE("Testing Math Operator *") {
	CHECK(Rational(2, 3) * Rational(1, 2) == Rational(1, 3));
	CHECK(Rational(4, 3) * Rational(1, 2) == Rational(2, 3));
	CHECK(Rational(5, 2) * 2 == Rational(5, 1));
	CHECK(-2 * Rational(5, 2) == Rational(-5, 1));
}

TEST_CASE("Testing Math Operator /") {
	CHECK(Rational(2, 3) / Rational(1, 2) == Rational(4, 3));
	CHECK(Rational(5, 2) / Rational(1, 2) == Rational(5, 1));
	CHECK(Rational(5, 2) / 2 == Rational(5, 4));
	CHECK(-2 / Rational(5, 2) == Rational(-4, 5));
}

TEST_CASE("Testing Math Operator (+,-,*,/)= and (++,--)") {
	Rational x = Rational(2, 3);
	x += 1;
	CHECK(x == Rational(5, 3));
	x -= 1;
	CHECK(x == Rational(2, 3));
	x /= 2;
	CHECK(x == Rational(1, 3));
	x *= 4;
	CHECK(x == Rational(4, 3));
	x++;
	CHECK(x == Rational(7, 3));
	x--;
	CHECK(x == Rational(4, 3));
	x += Rational(4, 3);
	CHECK(x == Rational(8, 3));
	x -= Rational(1, 2);
	CHECK(x == Rational(13, 6));
	x *= Rational(1, 2);
	CHECK(x == Rational(13, 12));
	x /= Rational(13, 2);
	CHECK(x == Rational(1, 6));
}

TEST_CASE("Testing Unary Operator -") {
	CHECK(-Rational(2, 3) == Rational(-2, 3));
}

TEST_CASE("Testing Logic Operator >") {
	CHECK(Rational(2, 3) > Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) > Rational(2, 3));
	CHECK(Rational(2, 3)*2 > 1);
}

TEST_CASE("Testing Logic Operator <") {
	CHECK_FALSE(Rational(2, 3) < Rational(1, 2));
	CHECK(Rational(1, 2) < Rational(2, 3));
	CHECK_FALSE(Rational(2, 3) * 2 < 1);
}

TEST_CASE("Testing Logic Operator >=") {
	CHECK(Rational(2, 3) >= Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) >= Rational(2, 3));
	CHECK(Rational(2, 3) >= Rational(2, 3));
	CHECK(Rational(3, 2) >= 1);
}

TEST_CASE("Testing Logic Operator <=") {
	CHECK_FALSE(Rational(2, 3) <= Rational(1, 2));
	CHECK(Rational(1, 2) <= Rational(2, 3));
	CHECK(Rational(2, 3) <= Rational(2, 3));
	CHECK_FALSE(Rational(3, 2) <= 1);
}

TEST_CASE("Testing Logic Operator !=") {
	CHECK(Rational(2, 3) != Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) != Rational(1, 2));
	CHECK(Rational(2, 3) != 2);
	CHECK_FALSE(Rational(2, 2) != 1);
}


TEST_CASE("Testing Logic Operator ==") {
	CHECK_FALSE(Rational(2, 3) == Rational(1, 2));
	CHECK(Rational(1, 2) == Rational(1, 2));
	CHECK_FALSE(Rational(2, 3) == 2);
	CHECK(Rational(2, 2) == 1);
}

TEST_CASE("Dividing by 0") {
	CHECK_THROWS(Rational(1, 0));
	CHECK_THROWS(Rational(1, 2)/0);
	CHECK_THROWS(Rational(1, 2) / Rational(0, 5));
	Rational x = Rational(2, 3);
	CHECK_THROWS(x /= 0);
	CHECK_THROWS(x /= Rational(0, 5));
}

TEST_CASE("Checking input system") {
	Rational x;
	InputRational("1/4 ", x);
	CHECK(Rational(1, 4) == x);
	InputRational(" 1/2 ", x);
	CHECK(Rational(1, 2) == x);
	InputRational("1/7k", x);
	CHECK(Rational(1, 7) == x);
	InputRational("6/8", x);
	CHECK(Rational(3, 4) == x);
	std::string str_for_3 = "3/4 5/6 7/8";
	std::istringstream istrm_for_3(str_for_3);
	Rational y;
	Rational z;
	istrm_for_3 >> x >> y >> z;
	CHECK(Rational(3, 4) == x);
	CHECK(Rational(5, 6) == y);
	CHECK(Rational(7, 8) == z);

	x = Rational(1, 3);
	InputRational("1 /4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("4/k", x);
	CHECK(Rational(1, 3) == x);
	InputRational("4-3", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k3/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("3/ 4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("3", x);
	CHECK(Rational(1, 3) == x);
}*/


TEST_CASE("1 - Rational construtor") {
	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(0) == Rational(0, 1));
	CHECK(Rational(0, 6) == Rational(0, 1));
	CHECK(Rational(5) == Rational(5, 1));
	CHECK(Rational(-7) == Rational(-7, 1));
	CHECK(Rational(28, 7) == Rational(4, 1));
	CHECK(Rational(-34, 12) == Rational(-17, 6));
	CHECK(Rational(13, -2) == Rational(-13, 2));
	CHECK(Rational(-8, -26) == Rational(4, 13));
	CHECK_THROWS(Rational(1, 0));
	CHECK_THROWS(Rational(-4, 0));
}

TEST_CASE("2 - comparsion operators") {
	CHECK(Rational(3, 5) == Rational(9, 15));
	CHECK(Rational(3, 1) == 3);
	CHECK(Rational(-3, 5) != Rational(9, 15));
	CHECK(Rational(-1, 3) != Rational(-10001, 30004));
	CHECK(Rational(3, 5) > Rational(8, 15));
	CHECK(Rational(3, 1) > -4);
	CHECK(Rational(2, 5) <= Rational(9, 15));
	CHECK(Rational(3, 5) <= Rational(9, 15));
	CHECK(Rational(2, 1) <= 3);
	CHECK(Rational(-3, 1) <= -3);
	CHECK(Rational(3, 5) < Rational(10, 15));
	CHECK(Rational(-3, 1) < 4);
	CHECK(Rational(4, 5) >= Rational(9, 15));
	CHECK(Rational(3, 5) >= Rational(9, 15));
	CHECK(Rational(4, 1) >= 3);
	CHECK(Rational(-3, 1) >= -3);
}

TEST_CASE("3 - unary operators") {
	Rational x = Rational(3, 5);
	Rational y = -x;
	CHECK(x == Rational(3, 5));
	CHECK(y == Rational(-3, 5));
	y = ++x;
	CHECK(x == Rational(8, 5));
	CHECK(y == Rational(8, 5));
	y = --x;
	CHECK(x == Rational(3, 5));
	CHECK(y == Rational(3, 5));
	y = x++;
	CHECK(x == Rational(8, 5));
	CHECK(y == Rational(3, 5));
	y = x--;
	CHECK(x == Rational(3, 5));
	CHECK(y == Rational(8, 5));
}

TEST_CASE("4 - assigning operators") {
	Rational x = Rational(3, 5);
	x += Rational(4, 5);
	CHECK(x == Rational(7, 5));
	x += 2;
	CHECK(x == Rational(17, 5));
	x -= Rational(6, 5);
	CHECK(x == Rational(11, 5));
	x -= 3;
	CHECK(x == Rational(-4, 5));
	x *= Rational(4, 5);
	CHECK(x == Rational(-16, 25));
	x *= 2;
	CHECK(x == Rational(-32, 25));
	x /= Rational(-8, 3);
	CHECK(x == Rational(12, 25));
	x /= 6;
	CHECK(x == Rational(2, 25));
	CHECK_THROWS(x /= Rational(0, 1));
	CHECK_THROWS(x /= 0);
	x /= x;
	CHECK(x == Rational(1, 1));
}

TEST_CASE("5 - binary operators") {
	CHECK(Rational(3, 5) + Rational(4, 5) == Rational(7, 5));
	CHECK(Rational(3, 5) + Rational(4, 7) == Rational(41, 35));
	CHECK(Rational(3, 5) + 2 == Rational(13, 5));
	CHECK(2 + Rational(3, 5) == Rational(13, 5));
	CHECK(Rational(3, 5) - Rational(4, 5) == Rational(-1, 5));
	CHECK(Rational(3, 5) - 2 == Rational(-7, 5));
	CHECK(2 - Rational(3, 5) == Rational(7, 5));
	CHECK(Rational(3, 5) * Rational(4, 5) == Rational(12, 25));
	CHECK(Rational(3, 5) * 2 == Rational(6, 5));
	CHECK(2 * Rational(3, 5) == Rational(6, 5));
	CHECK(Rational(3, 5) / Rational(4, 5) == Rational(3, 4));
	CHECK(Rational(3, 5) / 2 == Rational(3, 10));
	CHECK(2 / Rational(3, 5) == Rational(10, 3));
	CHECK_THROWS(Rational(3, 5) / Rational(0, 1));
	CHECK_THROWS(Rational(3, 5) / 0);
	CHECK_THROWS(5 / Rational(0, 1));
}

Rational RationalInput(Rational& x, const std::string& s) {
	std::istringstream istrm(s);
	istrm >> x;
	return x;
}

TEST_CASE("6 - input stream") {
	Rational x;
	x = RationalInput(x, "3/5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "-3/5^D");
	CHECK(x == Rational(-3, 5));
	x = RationalInput(x, "1/5n");
	CHECK(x == Rational(1, 5));
	x = RationalInput(x, "3/5 1/5^D");
	CHECK(x == Rational(3, 5));

	std::istringstream istrm_3("2/5 3/5	  4/5");
	Rational x1, x2, x3;
	istrm_3 >> x1 >> x2 >> x3;
	CHECK(x1 == Rational(2, 5));
	CHECK(x2 == Rational(3, 5));
	CHECK(x3 == Rational(4, 5));

	x = RationalInput(x, "2/-5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2//5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2/0^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "n/5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2-5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2.5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2/ 5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2 /5^D");
	CHECK(x == Rational(3, 5));
	x = RationalInput(x, "2 / 5^D");
	CHECK(x == Rational(3, 5));
}
