#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <utility>
#include "dense_matrix.hpp"
#include "vector_operations.hpp"

template <typename T>
std::vector<T> orthogonal_transformation_of_p(const std::vector<T>& x, const std::vector<T>& v){
    T scalar_vv = scalar(v, v);

    if (scalar_vv < 1e-12) { // Избегаем деления на ноль
        return x;
    }
    std::vector<T> result = x - 2 * scalar(v, x) / scalar(v, v) * v;
    return result;
};


template <typename T>
std::pair<dense_matrix<T>, dense_matrix<T>> QR_decomposition(const dense_matrix<T>& A){

    if (A.get_size_y() != A.get_size_x()){
	    throw std::invalid_argument("You are invalid: the matrices must be the same size!");
	}
	size_t size_n = A.get_size_x();

    dense_matrix<T> R(size_n, size_n);
    R = A;
    dense_matrix<T> Q = dense_matrix<T>::identity(size_n);


    for(size_t i = 0; i < size_n; ++i){
        std::vector<T> e;
        e.resize(size_n - i);
        e[0] = 1.0;
        std::vector<T> tmp = R.get_col(i, i, size_n);
        T norm = std::sqrt(scalar(tmp, tmp));
        if (tmp[0] < 0) norm = -norm;

        std::vector<T> v = tmp - norm * e;
        T v_norm = std::sqrt(scalar(v, v));
        if (v_norm < 1e-12) continue;

        for(size_t j = i; j <size_n; ++j){
            std::vector<T> r_i = R.get_col(j, i, size_n);
            r_i = orthogonal_transformation_of_p(r_i, v);
            R.set_col(j, r_i, i);
        }

        for(size_t j = 0; j <size_n; ++j){
            std::vector<T> q_i = Q.get_row(j, i, size_n);
            q_i = orthogonal_transformation_of_p(q_i, v);
            Q.set_row(j, q_i, i);
        }
    }

    return std::make_pair(Q.t(),R.t());

};
