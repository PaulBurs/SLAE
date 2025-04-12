#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"


template <typename T, class M>
std::vector<T> symmetry_Gauss_Seidel_iteration_method(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter){
    size_t MAX_ITER = 1000000;
    size_t n = x_0.size();
    std::vector<T> x = x_0;

    for(size_t i = 0; i < iter * 2 && i < MAX_ITER * 2; ++i){
        if (i % 2){
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
        else{
            for(size_t k = 0; k < n; ++k){

                T sum_ux = T(0);
                for(size_t j = k + 1; j < n; ++j){
                    sum_ux += A(j,k) * x[j];
                }

                T sum_lx = T(0);
                for(size_t j = 0; j < k && j < n; ++j){
                    sum_lx += A(j,k) * x[j];
                }

                x[k] = 1 / A(k,k) * (b[k] - sum_ux - sum_lx);
            }
        }


    }

    return x;
}
