#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#icnlude <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/system_decision/iteration/Gauss_Seidel_iteration_method.hpp"
#include "../include/system_decision/iteration/Jacobi_iteration_method.hpp"
#include "../include/system_decision/iteration/method_of_simple_iterations.hpp"


template <typename T>
void time_of_simple(const std::string& filename, const dense_matrix<T>& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = method_of_simple_iterations_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << std::abs(x_iter - x_true) << " ms\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}


template <typename T>
void time_of_Gauss_Seidel(const std::string& filename, const dense_matrix<T>& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = Gauss_Seidel_iteration_method_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << std::abs(x_iter - x_true) << " ms\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}


template <typename T>
void time_of_Jacobi(const std::string& filename, const dense_matrix<T>& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = Jacobi_iteration_method_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << std::abs(x_iter - x_true) << " ms\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}



int main() {
    double EPSILON = 1e-6;
    std::vector<std::vector<double>> tmp = {
        {4, 1, 2, 0, 3, 1},
        {1, 5, 0, 2, 1, 0},
        {2, 0, 6, 1, 0, 2},
        {0, 2, 1, 7, 1, 0},
        {3, 1, 0, 1, 8, 1},
        {1, 0, 2, 0, 1, 9}
    };

    // Вектор правой части b
    std::vector<double> b = {11, 9, 13, 11, 14, 13};

    // Решение x = [1, 1, 1, 1, 1, 1]
    std::vector<double> x = {1, 1, 1, 1, 1, 1};

    std::vector<double> x_0 = {}
    dense_matrix<T> A(6, 6, tmp);


    for (int i = 10; i < 10000; i = i*1.33){
        measure_and_log("method_of_simple_iterations.txt", A, b, x_0, i, x);
        measure_and_log("Gauss_Seidel_iteration_method.txt", A, b, x_0, i, x);
        measure_and_log("Jacobi_iteration_method.txt", A, b, x_0, i, x);

    }
    return 0;
}
