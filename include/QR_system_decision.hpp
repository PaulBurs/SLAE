#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "../include/dense_matrix.hpp"
#include "../include/algorithm_of_Householder.hpp"
#include "../include/vector_operations.hpp"
#include "../include/input_matrix_and_vector.hpp"


template <typename T>
std::vector<T> decision_system_with_QR(const dense_matrix<T>& DATA, const std::vector<T>& f){
    size_t n = DATA.get_size_x();
    dense_matrix<T> A(n,n);
    A = DATA.t();
    std::pair<dense_matrix<T>, dense_matrix<T>> QR = QR_decomposition(A);
    dense_matrix<T> QT = QR.first.t();
    dense_matrix<T> R = QR.second;
    std::vector<T> g = QT * f;
    std::vector<T> x(n);

    for(int i = n - 1; i >= 0; --i){
        T sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += R(i, j) * x[j];
        }
        x[i] = (g[i] - sum) / R(i, i);
    }
    return x;
}







