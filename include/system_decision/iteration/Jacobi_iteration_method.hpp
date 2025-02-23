#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/suport/vector_operations.hpp"


template <typename T>
std::vector<T> Jacobi_iteration_method(const dense_matrix<T>& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter, T epsilon){
    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t k = 0; k < iter && k < MAX_ITER; ++k){

        std::vector<T> tmp(b.size(), T(0));
        for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b.size(); ++j) {
            if (i != j)
                tmp[i] += A(i,j) * x[j];
        }
        tmp = b - tmp;
        for (size_t j = 0; j < b.size(); ++j) {
            tmp[j] = tmp[j] / A(j,j);
        }

        if (abs(x - tmp) < epsilon)
            break;
        x = tmp;

    }
    return x;
}


template <typename T>
std::vector<T> Jacobi_iteration_method_iter(const dense_matrix<T>& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter){
    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t k = 0; k < iter && k < MAX_ITER; ++k){

        std::vector<T> tmp(b.size(), T(0));
        for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b.size(); ++j) {
            if (i != j)
                tmp[i] += A(i,j) * x[j];
        }
        tmp = b - tmp;
        for (size_t j = 0; j < b.size(); ++j) {
            tmp[j] = tmp[j] / A(j,j);
        }

        x = tmp;

    }
    return x;
}


template <typename T>
std::vector<T> Jacobi_iteration_method_epsilon(const dense_matrix<T>& A, const std::vector<T>& b, const std::vector<T>& x_0, T epsilon){
    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t k = 0; k < MAX_ITER; ++k){

        std::vector<T> tmp(b.size(), T(0));
        for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b.size(); ++j) {
            if (i != j)
                tmp[i] += A(i,j) * x[j];
        }
        tmp = b - tmp;
        for (size_t j = 0; j < b.size(); ++j) {
            tmp[j] = tmp[j] / A(j,j);
        }

        if (abs(x - tmp) < epsilon)
            break;
        x = tmp;

    }
    return x;
}

