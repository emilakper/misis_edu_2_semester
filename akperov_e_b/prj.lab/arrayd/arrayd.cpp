#include <arrayd/arrayd.hpp>

ArrayD::ArrayD(const std::ptrdiff_t size) {
	if (size < 0) {
		throw out_of_range;
	}
	size_ = size;
	data_ = new double[size];
	for (ptrdiff_t i = 0; i < size; ++i) {
		data_[i] = 0.0;
	}
}

ArrayD::ArrayD(const ArrayD& arr) {
	size_ = arr.ssize();
	data_ = new double[size_];
	for (int i = 0; i < arr.size_; i++) {
		data_[i] = arr[i];
	}
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
	if (&rhs != this) {
		delete[] data_;
		size_ = rhs.ssize();
		data_ = new double[size_];
		ptrdiff_t i = 0;
		for (ptrdiff_t i = 0; i < size_; ++i) {
			data_[i] = rhs[i];
		}
	}
	return *this;
}

double& ArrayD::operator[](const std::ptrdiff_t i) {
	if (0 <= i && i < size_) {
		return data_[i];
	}
	else {
		throw out_of_range;
	}
}

const double& ArrayD::operator[](const std::ptrdiff_t i) const {
	if (0 <= i && i < size_) {
		return data_[i];
	}
	else {
		throw out_of_range;
	}
}

void ArrayD::resize(const std::ptrdiff_t size) {
	if (size < 0) {
		throw out_of_range;
	}
	else {
		double* temp = new double[size];
		for (ptrdiff_t i = 0; i < size; ++i) {
			temp[i] = 0.0;
		}
		for (ptrdiff_t i = 0; i < size_; i++) {
			temp[i] = data_[i];
		}
		data_ = temp;
		size_ = size;
	}
}