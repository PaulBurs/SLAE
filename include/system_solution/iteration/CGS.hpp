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
std::vector<T> CGS(const M& A, const std::vector<T>& b,
                   const std::vector<T>& x_0, size_t iter, T epsilon) {
    std::vector<T> x = x_0;
    std::vector<T> r = b - A * x; // Исправлен знак
    std::vector<T> rt = r;        // rt = r0 (начальная невязка)
    std::vector<T> d = r;
    std::vector<T> u = r;

    for (size_t i = 0; i < iter; ++i) {
        // Проверка деления на ноль
        T denominator = scalar(rt, A * d);
        if (std::abs(denominator) < 1e-12) break;

        T alpha = scalar(rt, r) / denominator;
        std::vector<T> q = u - alpha * (A * d);
        x = x + alpha * (u + q);
        std::vector<T> tmp_r = r;
        r = r - alpha * (A * (u + q));

        if (abs(r) < epsilon) // Используйте L2-норму
            return x;

        T beta = scalar(rt, r) / scalar(rt, tmp_r);
        u = r + beta * q;
        d = u + beta * (q + beta * d);
    }
    return x;
}
