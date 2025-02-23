#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <algorithm>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/QR_decomposition/algorithm_of_Householder.hpp"

const double EPSILON = 1e-8;

TEST(HouseholderQR, CorrectDimensions) {
    // Тест 1: Проверка корректности размеров матриц
    std::vector<std::vector<double>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    dense_matrix matA(3, 3, A);

    auto [Q, R] = QR_decomposition(matA);

    ASSERT_EQ(Q.get_size_x(), 3);
    ASSERT_EQ(Q.get_size_y(), 3);
    ASSERT_EQ(R.get_size_x(), 3);
    ASSERT_EQ(R.get_size_y(), 3);
}

TEST(HouseholderQR, RIsUpperTriangular) {
    // Тест 2: Проверка верхней треугольности R
    std::vector<std::vector<double>> A = {
        {12, -51, 4},
        {6, 167, -68},
        {-4, 24, -41}
    };
    dense_matrix matA(3, 3, A);

    auto [Q, R] = QR_decomposition(matA);

    // Проверка размеров R
    ASSERT_EQ(R.get_size_x(), 3) << "Invalid R rows count";
    ASSERT_EQ(R.get_size_y(), 3) << "Invalid R cols count";
    // Проверка верхнетреугольности
    for (size_t i = 0; i < R.get_size_x(); ++i) {
        for (size_t j = 0; j < i; ++j) { // Элементы ниже диагонали
            EXPECT_NEAR(R(i, j), 0.0, EPSILON)
                << "Non-zero element below diagonal at [" << i << "][" << j << "]";
        }
    }

    // Дополнительно: проверка, что диагональные элементы не нулевые
    for (size_t i = 0; i < R.get_size_x(); ++i) {
        EXPECT_GT(std::abs(R(i, i)), 1e-10)
            << "Zero diagonal element at [" << i << "][" << i << "]";
    }
}

TEST(HouseholderQR, QIsOrthogonal) {
    // Тест 3: Проверка ортогональности Q
    std::vector<std::vector<double>> A = {
        {2, -1, 3},
        {1, 5, -2},
        {4, 0, 6}
    };
    dense_matrix matA(3, 3, A);

    auto [Q, R] = QR_decomposition(matA);
    dense_matrix QT = Q.t();
    dense_matrix<double> product(3, 3);
    product = QT * Q;
    for (size_t i = 0; i < product.get_size_x(); ++i) {
        for (size_t j = 0; j < product.get_size_y(); ++j) {
            if (i == j) {
                EXPECT_NEAR(product(i, j), 1.0, EPSILON);
            } else {
                EXPECT_NEAR(product(i, j), 0.0, EPSILON);
            }
        }
    }
}

TEST(HouseholderQR, QRDecompositionAccuracy) {
    // Тест 4: Проверка A = Q*R
    std::vector<std::vector<double>> A = {
        {3, 1, 2},
        {1, 5, 7},
        {2, 7, 9}
    };
    dense_matrix matA(3, 3, A);

    auto [Q, R] = QR_decomposition(matA);
    dense_matrix QR = Q * R;

    for (size_t i = 0; i < matA.get_size_x(); ++i) {
        for (size_t j = 0; j < matA.get_size_y(); ++j) {
            EXPECT_NEAR(QR(i, j), A[i][j], EPSILON);
        }
    }
}

TEST(HouseholderQR, IdentityMatrix) {
    // Тест 5: Проверка единичной матрицы
    std::vector<std::vector<double>> I = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    dense_matrix matI(3, 3, I);

    auto [Q, R] = QR_decomposition(matI);

    // Проверка Q = I
    for (size_t i = 0; i < Q.get_size_x(); ++i) {
        for (size_t j = 0; j < Q.get_size_y(); ++j) {
            EXPECT_NEAR(Q(i, j), I[i][j], EPSILON);
        }
    }

    // Проверка R = I
    for (size_t i = 0; i < R.get_size_x(); ++i) {
        for (size_t j = 0; j < R.get_size_y(); ++j) {
            EXPECT_NEAR(R(i, j), I[i][j], EPSILON);
        }
    }
}
