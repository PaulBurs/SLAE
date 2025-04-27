#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <utility>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"
#include <map>
#include <stdexcept>

template <typename T>
csr_matrix<T> generate_elliptic_csr(size_t grid_size) {
    const size_t N = grid_size;
    const size_t matrix_size = N * N;
    std::map<std::pair<size_t, size_t>, T> matrix_entries;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            size_t node = i * N + j;

            // Диагональный элемент
            matrix_entries[{node, node}] = 4.0;

            // Соседи: вверх, вниз, влево, вправо
            std::vector<std::pair<size_t, size_t>> neighbors = {
                {i-1, j},  // Вверх
                {i+1, j},  // Вниз
                {i, j-1},  // Влево
                {i, j+1}   // Вправо
            };

            for (const auto& neighbor : neighbors) {
                size_t ni = neighbor.first;
                size_t nj = neighbor.second;
                if (ni < N && nj < N) { // Проверка на выход за границы
                    size_t neighbor_node = ni * N + nj;
                    matrix_entries[{node, neighbor_node}] = -1.0;
                }
            }
        }
    }

    return csr_matrix<T>(matrix_size, matrix_size, matrix_entries);
}
