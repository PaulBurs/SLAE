#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"
#include "../include/matrix/csr_matrix.hpp"
#include "../include/system_solution/iteration/Gauss_Seidel_iteration_method.hpp"
#include "../include/system_solution/iteration/Jacobi_iteration_method.hpp"
#include "../include/system_solution/iteration/method_of_simple_iterations.hpp"
#include "../include/system_solution/iteration/Chebyshev_acceleration.hpp"
#include "../include/system_solution/direct/QR_system_solution.hpp"


template <typename T, class M>
void time_of_simple(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = method_of_simple_iterations_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << abs(x_iter - x_true) << "\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}


template <typename T, class M>
void time_of_Chebyshev(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {

    size_t time = 0;
    T delta = 0;

    for (size_t i = 0; i < 20; ++i){
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<T> x_iter = Chebyshev_acceleration(A, b, x_0, iter);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


        std::ofstream outfile(filename, std::ios_base::app);
        time += duration.count();
        delta += abs(x_iter - x_true);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = Chebyshev_acceleration(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << time / 20 << " " << delta / 20 << "\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}


template <typename T, class M>
void time_of_Gauss_Seidel(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = Gauss_Seidel_iteration_method_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << abs(x_iter - x_true) << "\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}


template <typename T, class M>
void time_of_Jacobi(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = Jacobi_iteration_method_iter(A, b, x_0, iter);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << iter << " " << duration.count() << " " << abs(x_iter - x_true) << "\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}

template <typename T, class M>
void time_of_QR(const std::string& filename, const M& A, const std::vector<T>& b, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x = decision_system_with_QR(A, b);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << duration.count() << " " << abs(x - x_true) << "\n";
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

    // ������ ������ ����� b
    std::vector<double> b = {11, 9, 13, 11, 14, 13};

    // ������� x = [1, 1, 1, 1, 1, 1]
    std::vector<double> x = {0.63218, 1.09104, 1.50541, 0.87998, 1.15260, 0.91160};

    std::vector<double> x_0(6, 666);
    dense_matrix B(6, 6, tmp);
    csr_matrix A(B);


    ////////////////////////CLEAR//////////////////////////
    std::ofstream outfile1("method_of_simple_iterations.txt", std::ios::trunc);
    if (!outfile1.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }
    outfile1.close();
    std::ofstream outfile2("Gauss_Seidel_iteration_method.txt", std::ios::trunc);
    if (!outfile2.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }
    outfile2.close();
    std::ofstream outfile3("Jacobi_iteration_method.txt", std::ios::trunc);
    if (!outfile3.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }
    outfile3.close();
    std::ofstream outfile4("QR_decision.txt", std::ios::trunc);
    if (!outfile4.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }
    outfile4.close();

    std::ofstream outfile5("Chebyshev_acceleration.txt", std::ios::trunc);
    if (!outfile5.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }
    outfile5.close();
    ////////////////////////CLEAR//////////////////////////



    for (int i = 10; i < 100000; i = i*1.1){
        time_of_simple("method_of_simple_iterations.txt", A, b, x_0, i, x);
        time_of_Gauss_Seidel("Gauss_Seidel_iteration_method.txt", A, b, x_0, i, x);
        time_of_Jacobi("Jacobi_iteration_method.txt", A, b, x_0, i, x);
    }
    for (int i = 2; i < 100000; i = i*2){
        time_of_Chebyshev("Chebyshev_acceleration.txt", A, b, x_0, i, x);
    }
    time_of_QR("QR_decision.txt", B, b, x);
    return 0;
}
