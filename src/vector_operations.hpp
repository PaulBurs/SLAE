#pragma once
#include "csr_matrix.hpp"
#include "dense_matrix.hpp"
#include <vector>

template <typename T>
template <typename M>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
	if (a.size() != b.size())
	{
	    throw std::invalid_argument("You are invalid: the vectors must be the same size!");
	}

	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); i++)
	{
	    result.push_back(a[i] + b[i]);
	}

	return result;
};

T scalar(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }

    T result = 0;
    for (int i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
};

std::vector<T> operator*(const std::vector<T>& a, const M& m) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] * m);
	}

	return result;
};

std::vector<T> operator*(const M& m, const std::vector<T>& a) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] * m);
	}

	return result;
};





