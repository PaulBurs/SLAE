#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/suport/vector_operations.hpp"
#include "../include/suport/lambda_estimation.hpp"


template<typename T>
std::vector<T> generate_Chebyshev_permutation(T r) {
    std::vector<T> t = {0, 1};

    for (size_t j = 2; j <= r; j = j*2) {
        for (size_t k = 0; k < j; ++k){
            t.insert(t.begin() + 1 + k*2, j*2 - k*2 - 1);
        }
    }
    /*for(size_t i = 0; i < t.size(); ++i)
        std::cout << t[i] << " ";
    std::cout << "" << std::endl;*/

    return t;
}


template <typename T, class M>
std::vector<T> Chebyshev_acceleration(const M& A, const std::vector<T>& bv,
                                            const std::vector<T>& x_0, size_t iter, T epsilon){

    size_t MAX_ITER = 1000000;
    size_t degree_iter = 2;
    while (iter > degree_iter && MAX_ITER > degree_iter)
        degree_iter = degree_iter*2;
    degree_iter = degree_iter / 2;

    T t_0 = std::cos(M_PI / 2 / (T)degree_iter);
    T t_1 = std::sin(3 * M_PI / 2 / (T)degree_iter);
    T cos_pi_n = std::cos(M_PI / (T)degree_iter);
    T sin_pi_n = std::sin(M_PI / (T)degree_iter);
    std::vector<T> t(degree_iter);
    t[0] = t_0;
    for (size_t i = 1; i < degree_iter; ++i){
        t[i] = t[i-1] * cos_pi_n - std::sqrt(1 - t[i-1]*t[i-1]) * sin_pi_n;
    }
    T a = estimation_lambda_max(A, x_0);
    T b = estimation_lambda_min(A);

    std::vector<T> stable_t(degree_iter);
    std::vector<size_t> iter_t = generate_Chebyshev_permutation(degree_iter);
    for (size_t k = 0; k < degree_iter; ++k){
        stable_t[k] = (a + b) / 2 + (b - a) / 2 * t[iter_t[k]];
    }


    std::vector<T> x = x_0;


    for (size_t i = 0; i < degree_iter; ++i){
        std::vector<T> r = (A * x - bv) * (1 / stable_t[i]);
        x = x - r;
        if (abs(r)< epsilon)
            break;
    }
    return x;
}


template <typename T, class M>
std::vector<T> Chebyshev_acceleration(const M& A, const std::vector<T>& bv,
                                            const std::vector<T>& x_0, size_t iter){

    size_t MAX_ITER = 1000000;
    size_t degree_iter = 2;
    while (iter > degree_iter && MAX_ITER > degree_iter)
        degree_iter = degree_iter*2;
    //degree_iter = degree_iter / 2;

    T t_0 = std::cos(M_PI / 2 / (T)degree_iter);
    T t_1 = std::sin(3 * M_PI / 2 / (T)degree_iter);
    T cos_pi_n = std::cos(M_PI / (T)degree_iter);
    T sin_pi_n = std::sin(M_PI / (T)degree_iter);
    std::vector<T> t(degree_iter);
    t[0] = t_0;
    for (size_t i = 1; i < degree_iter; ++i){
        t[i] = t[i-1] * cos_pi_n - std::sqrt(1 - t[i-1]*t[i-1]) * sin_pi_n;
    }
    T a = estimation_lambda_max(A, x_0);
    //std::cout << a << std::endl;
    T b = estimation_lambda_min<T>(A);
    //T b = 2;

    std::vector<T> stable_t(degree_iter);
    std::vector<size_t> iter_t = generate_Chebyshev_permutation(degree_iter);
    for (size_t k = 0; k < degree_iter; ++k){
        /*std::cout << iter_t[k] << std::endl;*/
        stable_t[k] = (a + b) / 2 + (b - a) / 2 * t[iter_t[k]];
    }


    std::vector<T> x = x_0;


    for (size_t i = 0; i < degree_iter; ++i){
        std::vector<T> r = (A * x - bv) / stable_t[i];
        x = x - r;
    }
    return x;
}
