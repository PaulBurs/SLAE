#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <algorithm>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/system_solution/direct/QR_system_solution.hpp"

const double EPSILON = 1e-8;

TEST(DecisionQR, CorrectValues) {
    // Тест 1: Проверка корректности размеров матриц
    std::vector<std::vector<double>> A_tmp = {
        {3, 2, -1},
        {2, -2, 4},
        {-1, 0.5, -1}
    };
    dense_matrix A(3, 3, A_tmp);
    std::vector<double> f = {1.0, -2.0, 0.0};
    std::vector<double> x = {1, -2, -2};

    std::vector<double> my_x = decision_system_with_QR(A, f);
    for(size_t i = 0; i < 3; ++i)
        EXPECT_NEAR(x[i], my_x[i], EPSILON);
}

