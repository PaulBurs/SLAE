#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"
#include "../include/suport/lambda_estimation.hpp"
#include "../include/system_solution/iteration/Gauss_Seidel_iteration_method.hpp"

template<typename T, class M>
T SOR_omega(const M& A, const std::vector<T>& b){
    size_t n = A.get_size_x();
    dense_matrix<T> dense(n, n);

    for(size_t i = 0; i < n; ++i){
        T d = A(i,i);
        for(size_t j = 0; j < n; ++j){
            if (i != j)
                dense(i,j) = - A(i,j) / d;
        }
        dense(i,i) = 0;
    }
    csr_matrix<T> csr(dense);

    T mu = std::abs(estimation_lambda_max(csr, b));
    //std::cout << mu << std::endl;
    T omega = 1 + std::pow(mu / (1 + std::sqrt(std::abs(1 - mu * mu))), 2);
    return omega;
}

template<typename T, class M>
std::vector<T> SOR(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter){
    T omega = SOR_omega(A, b);
    return Gauss_Seidel_iteration_method_iter(A * omega, omega * b, x_0, iter);
}


template<typename T, class M>
std::vector<T> SOR_test(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter, T omega){
    return Gauss_Seidel_iteration_method_iter(A * omega, omega * b, x_0, iter);
}



