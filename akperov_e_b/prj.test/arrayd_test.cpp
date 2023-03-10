#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>
/*
TEST_CASE("Test number 1") {
resize нельзя до 0
ar = br присваивание
A br(ar)
A ar(5)
resize()
[]
A ar


	ArrayD arr;
	arr.resize(5);
	arr[2] = 5.25;
	arr[3] = 3.29;
	CHECK(arr[2] == 5.25);
	CHECK(arr[3] == 3.29);
}*/

TEST_CASE("Test number 1") {
	ArrayD arr{ 10 };
	for (int i = 0; i < arr.ssize(); i++) {
		std::cout << arr[i] << "\t";
	}
	ArrayD arr1(arr);
	ArrayD arr2;
	arr2 = arr1;
	arr[2] = 5;
	arr[3] = arr[2];
	std::cout << arr[3] << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < arr2.ssize(); i++) {
		std::cout << arr2[i] << "\t";
	}
	std::cout << arr.ssize() << std::endl;
}