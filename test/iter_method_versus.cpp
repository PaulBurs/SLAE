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
#include "../include/system_solution/iteration/successive_over_relaxation_method.hpp"
#include "../include/system_solution/direct/QR_system_solution.hpp"
#include "../include/system_solution/iteration/symmetry_Gauss_Seidel_iteration_method.hpp"
#include "../include/system_solution/iteration/steepest_gradient_descent_method.hpp"


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
void time_of_symmetry_Gauss_Seidel(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = symmetry_Gauss_Seidel_iteration_method(A, b, x_0, iter);
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
void time_of_SOR(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = SOR(A, b, x_0, iter);
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
void time_of_SOR_test(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true, const T omega){


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = SOR_test(A, b, x_0, iter, omega);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        outfile << omega << " " << duration.count() << " " << abs(x_iter - x_true) << "\n";
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}

template <typename T, class M>
void time_of_SGD(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = SGD(A, b, x_0, iter);
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
    {152, 5, 0, 77, 95, 0, 0, 51, 0, 0},
    {0, 166, 9, 0, 0, 0, 55, 0, 33, 0},
    {0, 0, 51, 0, 8, 0, 0, 0, 0, 0},
    {11, 0, 0, 61, 0, 0, 0, 100, 85, 3},
    {0, 0, 0, 0, 789, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 0, 16, 0, 0, 0, 95},
    {0, 0, 85, 0, 56, 0, 74, 0, 0, 0},
    {55, 0, 0, 0, 0, 0, 0, 668, 0, 0},
    {0, 0, 0, 63, 0, 0, 0, 0, 463, 0},
    {0, 69, 0, 0, 3, 62, 0, 0, 0, 561}
};

    // Вектор правой части b
    std::vector<double> b = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<double> x_0(10, 666);
    dense_matrix B(10, 10, tmp);
    csr_matrix A(B);
    std::vector<double> x = decision_system_with_QR(B, b);


    ////////////////////////CLEAR//////////////////////////
    std::ofstream outfile1("method_of_simple_iterations.txt", std::ios::trunc);
    if (!outfile1.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile1.close();
    std::ofstream outfile2("Gauss_Seidel_iteration_method.txt", std::ios::trunc);
    if (!outfile2.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile2.close();
    std::ofstream outfile3("Jacobi_iteration_method.txt", std::ios::trunc);
    if (!outfile3.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile3.close();
    std::ofstream outfile4("QR_decision.txt", std::ios::trunc);
    if (!outfile4.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile4.close();

    std::ofstream outfile5("Chebyshev_acceleration.txt", std::ios::trunc);
    if (!outfile5.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile5.close();

    std::ofstream outfile6("successive_over_relaxation_method.txt", std::ios::trunc);
    if (!outfile6.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile6.close();

    std::ofstream outfile7("symmetry_Gauss_Seidel_iteration_method.txt", std::ios::trunc);
    if (!outfile7.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile7.close();

    std::ofstream outfile8("steepest_gradient_descent_method.txt", std::ios::trunc);
    if (!outfile8.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile8.close();

    std::ofstream outfile9("SOR_omega.txt", std::ios::trunc);
    if (!outfile9.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile9.close();
    ////////////////////////CLEAR//////////////////////////



    for (int i = 10; i < 2500; i = i*1.1){
        time_of_simple("method_of_simple_iterations.txt", A, b, x_0, i, x);
        time_of_Gauss_Seidel("Gauss_Seidel_iteration_method.txt", A, b, x_0, i, x);
        time_of_Jacobi("Jacobi_iteration_method.txt", A, b, x_0, i, x);
        time_of_SOR("successive_over_relaxation_method.txt", A, b, x_0, i, x);
        time_of_symmetry_Gauss_Seidel("symmetry_Gauss_Seidel_iteration_method.txt", A, b, x_0, i, x);
        time_of_SGD("steepest_gradient_descent_method.txt", A, b, x_0, i, x);
    }
    for (int i = 2; i < 10000; i = i*2){
        time_of_Chebyshev("Chebyshev_acceleration.txt", A, b, x_0, i, x);
    }

    double omega = SOR_omega(A, b);
    for(int i = -1000; i < 1000; ++i){
        time_of_SOR_test("SOR_omega.txt", A, b, x_0, 100, x, omega * i / 10 + 0.01);
    }
    time_of_QR("QR_decision.txt", B, b, x);
    return 0;
}
