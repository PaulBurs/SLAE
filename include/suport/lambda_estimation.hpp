#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"

template<typename T, class M>
T estimation_lambda_max(const M& A, const std::vector<T>& start){
    size_t MAX_ITER = 1000000;
    double epsilon = 1e-4;
    std::vector<T> x_0 = (A * start) / abs(A * start);
    T mu_0 = scalar(x_0, A * x_0) / abs(x_0);

    for(size_t i = 0; i < MAX_ITER; ++i){
        std::vector<T> x = A * x_0 / abs(A * x_0);
        T mu = scalar(x, A * x) / abs(x);
        if (std::abs(mu - mu_0) <= epsilon)
            return mu;
        mu_0 = mu;
        x_0 = x;
    }
    return mu_0;
}

template<typename T, class M>
T estimation_lambda_max(const M& A){
    std::vector<T>& start(A.get_size_x(), 1);
    size_t MAX_ITER = 1000000;
    double epsilon = 1e-4;
    std::vector<T> x_0 = (A * start) / abs(A * start);
    T mu_0 = scalar(x_0, A * x_0) / abs(x_0);

    for(size_t i = 0; i < MAX_ITER; ++i){
        std::vector<T> x = A * x_0 / abs(A * x_0);
        T mu = scalar(x, A * x) / abs(x);
        if (std::abs(mu - mu_0) <= epsilon)
            return mu;
        mu_0 = mu;
        x_0 = x;
    }
    return mu_0;
}

template<typename T, class M>
T estimation_lambda_min(const M& A){
    T lambda = 2.0;
    for (size_t i = 0; i < std::min(A.get_size_x(), A.get_size_y()); ++i)
        if (A(i,i))
            lambda = (T)std::min(lambda, A(i,i));
    return lambda;
}
