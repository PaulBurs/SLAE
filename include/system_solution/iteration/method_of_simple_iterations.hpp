#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/suport/vector_operations.hpp"

const double tau = 0.005;

template <typename T, class M>
std::vector<T> method_of_simple_iterations(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, size_t iter, T epsilon){
    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t i = 0; i < iter && i < MAX_ITER; ++i){
        std::vector<T> r = tau * (A * x - b);
        x = x - r;
        if (abs(r)< epsilon)
            break;

    }
    return x;
}


template <typename T, class M>
std::vector<T> method_of_simple_iterations_iter(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, size_t iter){

    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t i = 0; i < iter && i < MAX_ITER; ++i){
        std::vector<T> r = tau * (A * x - b);
        x = x - r;
    }
    return x;
}


template <typename T, class M>
std::vector<T> method_of_simple_iterations_epsilon(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, T epsilon, T tau1){

    size_t MAX_ITER = 1000000;
    std::vector<T> x = x_0;
    for (size_t i = 0; i < MAX_ITER; ++i){
        std::vector<T> r = tau1 * (A * x - b);
        x = x - r;
        if (abs(r) < epsilon)
            break;

    }
    return x;
}

