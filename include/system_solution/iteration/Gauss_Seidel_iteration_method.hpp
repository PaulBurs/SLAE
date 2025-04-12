#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"


template <typename T, class M>
std::vector<T> Gauss_Seidel_iteration_method(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter, T epsilon){
    size_t MAX_ITER = 1000000;
    size_t n = x_0.size();
    std::vector<T> x = x_0;

    for(size_t i = 0; i < iter && i < MAX_ITER; ++i){
        std::vector<T> tmp = x;
        for(size_t k = 0; k < n; ++k){

            T sum_ux = T(0);
            for(size_t j = k; j < n; ++j){
                sum_ux += A(k,j) * x[j];
            }

            T sum_lx = T(0);
            for(size_t j = 0; j < k-1; ++j){
                sum_lx += A(k,j) * x[j];
            }

            x[k] = 1.0 / A(k,k) * (b[k] - sum_ux - sum_lx);
        }

        if (abs(x - tmp)< epsilon)
            break;

    }

    return x;
}


template <typename T, class M>
std::vector<T> Gauss_Seidel_iteration_method_iter(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter){
    size_t MAX_ITER = 1000000;
    size_t n = x_0.size();
    std::vector<T> x = x_0;

    for(size_t i = 0; i < iter && i < MAX_ITER; ++i){
        std::vector<T> tmp = x;
        for(size_t k = 0; k < n; ++k){

            T sum_ux = T(0);
            for(size_t j = k + 1; j < n; ++j){
                sum_ux += A(k,j) * x[j];
            }

            T sum_lx = T(0);
            for(size_t j = 0; j < k && j < n; ++j){
                sum_lx += A(k,j) * x[j];
            }

            x[k] = 1 / A(k,k) * (b[k] - sum_ux - sum_lx);
        }

    }

    return x;
}



template <typename T, class M>
std::vector<T> Gauss_Seidel_iteration_method_epsilon(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, T epsilon){
    size_t MAX_ITER = 1000000;
    size_t n = x_0.size();
    std::vector<T> x = x_0;

    for(size_t i = 0; i < MAX_ITER; ++i){
        std::vector<T> tmp = x;
        for(size_t k = 0; k < n; ++k){

            T sum_ux = T(0);
            for(size_t j = k + 1; j < n; ++j){
                sum_ux += A(k,j) * tmp[j];
            }

            T sum_lx = T(0);
            for(size_t j = 0; j < k-1 && j < n; ++j){
                sum_lx += A(k,j) * x[j];
            }

            x[k] = 1 / A(k,k) * (b[k] - sum_ux - sum_lx);
        }

        if (abs(x - tmp)< epsilon)
            break;

    }

    return x;
}
