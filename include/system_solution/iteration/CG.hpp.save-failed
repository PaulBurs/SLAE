#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <utility>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"

template <typename T, class M>
std::vector<T> CG(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, size_t iter, T epsilon){
    std::vector<T> x = x_0;
    std::vector<T> r = A * x_0 - b;
    std::vector<T> d = r;
    std::vector<T> r1 = r;

    for(size_t i = 0; i < iter; ++i){
        x = x - scalar(r, r) / scalar(d, (A * d)) * d;
        r1 = A * x - b;
        d = r1 + abs(r1) / abs(r) * d;
        r = r1;
        if(abs(r) < epsilon)
            return x;
    }
    return x;
}

