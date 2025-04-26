#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <functional>
#include <utility>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/suport/vector_operations.hpp"
#include "../include/suport/lambda_estimation.hpp"
#include "../include/system_solution/iteration/Gauss_Seidel_iteration_method.hpp"
#include "../include/system_solution/iteration/Jacobi_iteration_method.hpp"
#include "../include/system_solution/iteration/steepest_gradient_descent_method.hpp"
#include "../include/system_solution/iteration/Chebyshev_acceleration.hpp"



template <typename T, class M, typename METHOD>
std::vector<T> SA(const M& A, const std::vector<T>& b,
                                            const std::vector<T>& x_0, size_t iter, T epsilon, METHOD method){
    T pho = estimation_lambda_max(A, b);
    T omega = 2.0 / (2.0 - pho * pho);
    std::pair<std::vector<T>, std::vector<T>> y_0(x_0, method(A, b, x_0, 1, epsilon));
    for(size_t i = 0; i < iter; ++i){
        omega = 1 / (1 - omega * omega / 4);
        std::pair<std::vector<T>, std::vector<T>> y(y_0.second, omega * (method(A, b, y_0.second, 1, epsilon) - y_0.first) + y_0.first);
        if (abs(y.first - y.second) < epsilon)
            break;
        y_0 = y;
    }

    return y_0.second;
}
