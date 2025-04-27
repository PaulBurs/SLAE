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
std::vector<T> BiCG(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, size_t iter, T epsilon){
    M At = A.t();
    /*for (size_t i = 0; i < size(b); ++i){
        std::cout << At(0, i) << " " << A(i, 0) << std::endl;
    }
    std::cout << "-----------------------" << std::endl;*/

    std::vector<T> x = x_0;
    std::vector<T> r = A * x - b ;
    std::vector<T> rt = r;
    std::vector<T> d = r;
    std::vector<T> dt = r;
    std::vector<T> tmp_r;
    std::vector<T> tmp_rt;

    for(size_t i = 0; i < iter; ++i){
        T alpha = scalar(rt,r) / scalar(dt, A * d);
        tmp_r = r;
        tmp_rt = rt;
        r = r - alpha * (A * d);
        rt = rt - alpha * (At * dt);

        T beta = scalar(rt,r) / scalar(tmp_rt, tmp_r);
        d = r + beta * d;
        dt = rt + beta * dt;

        x = x - alpha * d;
        //std::cout << abs(r) << std::endl;
        if(abs(r) < epsilon){
            //std::cout << "RESULT: " << abs(A * x - b) << std:: endl;
            return x;
        }
    }
    return x;
}
