#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>

TEST_CASE("Test number 1") {
    MatrixS mat(3,3);
	int k = 1;
	for (std::ptrdiff_t i = 0; i < 3; ++i) {
		for (std::ptrdiff_t j = 0; j < 3; ++j) {
			mat.at(i, j) = k;
			k++;
		}
	}
	MatrixS mat555(3, 3);
	for (std::ptrdiff_t i = 0; i < 3; ++i) {
		for (std::ptrdiff_t j = 0; j < 3; ++j) {
			std::cout << mat.at(i, j) << " ";
		}
		std::cout << std::endl;
	}
	mat.resize(4, 5);
	std::cout << std::endl;
	for (std::ptrdiff_t i = 0; i < mat.nRows(); ++i) {
		for (std::ptrdiff_t j = 0; j < mat.nCols(); ++j) {
			std::cout << mat.at(i, j) << " ";
		}
		std::cout << std::endl;
	}
}