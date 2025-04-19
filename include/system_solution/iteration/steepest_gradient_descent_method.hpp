#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"

template <typename T, class M>
std::vector<T> SGD(const M& A, const std::vector<T>& b, const std::vector<T>& x_0, size_t iter, T epsilon){
    std::vector<T> r = x_0;
    std::vector<T> x = x_0;
    for(size_t i = 0; i < iter; ++i){
        T alpha = scalar(r, r) / scalar(r, A * r);
        std::vector<T> x_new = x - alpha * (A * x - b);
        r = x_new - x;
        x = x_new;
        if (abs(r) < epsilon)
            return x;
    }
    return x;
}
