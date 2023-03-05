#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>

TEST_CASE("Test number 1") {
	ArrayD arr;
	arr.resize(5);
	arr[2] = 5.25;
	arr[3] = 3.29;
	CHECK(arr[2] == 5.25);
	CHECK(arr[3] == 3.29);
}