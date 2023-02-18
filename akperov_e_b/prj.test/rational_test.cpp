#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("Testing Math Operators") {
  CHECK(Rational(10, 6) == Rational(5, 3));
}