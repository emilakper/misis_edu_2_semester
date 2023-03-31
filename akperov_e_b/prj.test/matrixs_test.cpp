#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>

TEST_CASE("Test number 1") {
	MatrixS mat({3,3});
	int k = 1;
	for (std::ptrdiff_t i = 0; i < 3; ++i) {
		for (std::ptrdiff_t j = 0; j < 3; ++j) {
			mat.at(i, j) = k;
			k++;
		}
	}
	k = 1;
	for (std::ptrdiff_t i = 0; i < 3; ++i) {
		for (std::ptrdiff_t j = 0; j < 3; ++j) {
			CHECK(mat.at(i, j) == k);
			k++;
			mat.at(i, j) = 1;
		}
	}
	mat.resize(4, 5);
	for (std::ptrdiff_t i = 0; i < mat.nRows(); ++i) {
		for (std::ptrdiff_t j = 0; j < mat.nCols(); ++j) {
			if (i < 3 && j < 3) {
				CHECK(mat.at(i, j) == 1);
			}
			else {
				CHECK(mat.at(i, j) == 0);
			}
		}
	}
	CHECK(mat.nRows() == 4);
	CHECK(mat.nCols() == 5);
	CHECK(mat.at(MatrixS::SizeType{ 2,2 }) == 1);
	CHECK(4 == std::get<0>(mat.ssize()));
	CHECK(5 == std::get<1>(mat.ssize()));
	MatrixS mat2 = mat;
	mat2.at(2, 2) = 5;
	CHECK(mat.at(2, 2) == 1);
	CHECK(mat2.at(2, 2) == 5);
}