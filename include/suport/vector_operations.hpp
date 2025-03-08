#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "../include/matrix/csr_matrix.hpp"
#include "../include/matrix/dense_matrix.hpp"


template <typename T>
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

template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {
	if (a.size() != b.size())
	{
	    throw std::invalid_argument("You are invalid: the vectors must be the same size!");
	}

	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); i++)
	{
	    result.push_back(a[i] - b[i]);
	}

	return result;
};

template <typename T>
T scalar(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }

    T result = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
};

template <typename T, typename M>
std::vector<T> operator*(const std::vector<T>& a, const M& m) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] * m);
	}

	return result;
};

template <typename T, typename M>
std::vector<T> operator*(const M& m, const std::vector<T>& a) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] * m);
	}

	return result;
};

template <typename T, typename M>
std::vector<T> operator/(const std::vector<T>& a, const M& m) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] / m);
	}

	return result;
};

template <typename T, typename M>
std::vector<T> operator/(const M& m, const std::vector<T>& a) {
	std::vector<T> result;
	result.reserve(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
	    result.push_back(a[i] / m);
	}

	return result;
};


template <typename T>
T abs(const std::vector<T>& a){
    return std::sqrt(scalar(a,a));
};



