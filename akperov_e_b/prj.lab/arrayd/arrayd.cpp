#include <arrayd/arrayd.hpp>

ArrayD::ArrayD(const std::ptrdiff_t size) {
	if (size < 0) {
		throw out_of_range;
	}
	else {
		size_ = size;
		capacity_ = size;
		data_ = new double[size];
		for (std::ptrdiff_t i = 0; i < size; ++i) {
			data_[i] = 0.0;
		}
	}
}

ArrayD::ArrayD(const ArrayD& arr) {
	capacity_ = arr.ssize();
	size_ = arr.ssize();
	data_ = new double[size_];
	for (std::ptrdiff_t i = 0; i < arr.size_; i++) {
		data_[i] = arr.data_[i];
	}
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
	if (&rhs != this) {
		delete[] data_;
		size_ = rhs.ssize();
		capacity_ = rhs.ssize();
		data_ = new double[size_];
		for (std::ptrdiff_t i = 0; i < size_; ++i) {
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
	if (size < 1) {
		throw out_of_range;
	}
	else if (capacity_ < size) {
		double* temp = new double[size];
		for (std::ptrdiff_t i = 0; i < size; i++) {
			temp[i] = 0.0;
		}
		for (std::ptrdiff_t i = 0; i < size_; i++) {
			temp[i] = data_[i];
		}
		size_ = size;
		capacity_ = size * 2;
		data_ = temp;
	}
	else {
		size_ = size;
		for (std::ptrdiff_t i = size; i < capacity_; i++) {
			data_[i] = 0.0;
		}
	}
}

void ArrayD::remove(std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		double* temp = new double[size_-1];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		for (std::ptrdiff_t i = index; i < size_-1; i++) {
			temp[i] = data_[i+1];
		}
		this->resize(size_ - 1);
		data_ = temp;
	}
}

void ArrayD::insert(double val, std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		double* temp = new double[size_ + 1];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		temp[index] = val;
		for (std::ptrdiff_t i = index+1; i < size_ + 1; i++) {
			temp[i] = data_[i - 1];
		}
		this->resize(size_ + 1);
		data_ = temp;
	}
}