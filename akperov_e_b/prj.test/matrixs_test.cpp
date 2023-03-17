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
	for (std::ptrdiff_t i = 0; i < 3; ++i) {
		for (std::ptrdiff_t j = 0; j < 3; ++j) {
			std::cout << mat.at(i, j) << " ";
		}
		std::cout << std::endl;
	}
	mat.Resize(4, 5);
	std::cout << std::endl;
	for (std::ptrdiff_t i = 0; i < mat.rowCount(); ++i) {
		for (std::ptrdiff_t j = 0; j < mat.colCount(); ++j) {
			std::cout << mat.at(i, j) << " ";
		}
		std::cout << std::endl;
	}
    //CHECK(mat.at(0, 0) == 0);
}