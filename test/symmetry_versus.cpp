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
#include "../include/system_solution/iteration/symmetry_acceleration.hpp"
#include "../include/system_solution/iteration/CG.hpp"
#include "../include/system_solution/iteration/BiCG.hpp"
#include "../include/system_solution/iteration/CGS.hpp"
#include "../include/suport/elliptical_equation.hpp"


template <typename T, class M>
void time_of_ChA(const std::string& filename, const M& A, const std::vector<T>& b,
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
void time_of_GS(const std::string& filename, const M& A, const std::vector<T>& b,
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
void time_of_J(const std::string& filename, const M& A, const std::vector<T>& b,
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
void time_of_SGD(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<T> x_iter = SGD(A, b, x_0, iter, 1e-7);
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
void time_of_SA_GS(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    auto gs_method = [](const M& A, const std::vector<T>& b,
                        const std::vector<T>& x, size_t iter, T eps) {
        return Gauss_Seidel_iteration_method<T, M>(A, b, x, iter, eps);
    };

    std::vector<T> x_iter = SA(A, b, x_0, iter, 1e-7, gs_method);
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
void time_of_SA_J(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    auto gs_method = [](const M& A, const std::vector<T>& b,
                        const std::vector<T>& x, size_t iter, T eps) {
        return Jacobi_iteration_method<T, M>(A, b, x, iter, eps);
    };

    std::vector<T> x_iter = SA(A, b, x_0, iter, 1e-7, gs_method);
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
void time_of_SA_ChA(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    auto gs_method = [](const M& A, const std::vector<T>& b,
                        const std::vector<T>& x, size_t iter, T eps) {
        return Chebyshev_acceleration<T, M>(A, b, x, iter, eps);
    };

    std::vector<T> x_iter = SA(A, b, x_0, iter, 1e-7, gs_method);
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
void time_of_SA_SGD(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();
    auto gs_method = [](const M& A, const std::vector<T>& b,
                        const std::vector<T>& x, size_t iter, T eps) {
        return SGD<T, M>(A, b, x, iter, eps);
    };

    std::vector<T> x_iter = SA(A, b, x_0, iter, 1e-7, gs_method);
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
void time_of_CG(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();

    std::vector<T> x_iter = CG(A, b, x_0, iter, 1e-15);
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
void time_of_BiCG(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();

    std::vector<T> x_iter = BiCG(A, b, x_0, iter, 1e-15);
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
void time_of_CGS(const std::string& filename, const M& A, const std::vector<T>& b,
                     const std::vector<T>& x_0, size_t iter, const std::vector<T>& x_true) {


    auto start = std::chrono::high_resolution_clock::now();

    std::vector<T> x_iter = CGS(A, b, x_0, iter, 1e-15);
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
    std::vector<double> b(100, 1);

    std::vector<double> x_0(100, 666);
    csr_matrix<double> A = generate_elliptic_csr<double>(10);
    std::vector<double> x = Gauss_Seidel_iteration_method(A, b, x_0, 2000, 1e-15);
    //A.print();


    ////////////////////////CLEAR//////////////////////////
    std::ofstream outfile1("symmetry_of_ChA.txt", std::ios::trunc);
    if (!outfile1.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile1.close();

    std::ofstream outfile2("symmetry_of_J.txt", std::ios::trunc);
    if (!outfile2.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile2.close();

    std::ofstream outfile3("symmetry_of_SGD.txt", std::ios::trunc);
    if (!outfile3.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile3.close();
    std::ofstream outfile4("symmetry_of_SA_GS.txt", std::ios::trunc);
    if (!outfile4.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile4.close();

    std::ofstream outfile5("symmetry_of_SA_J.txt", std::ios::trunc);
    if (!outfile5.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile5.close();

    std::ofstream outfile6("symmetry_of_SA_ChA.txt", std::ios::trunc);
    if (!outfile6.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile6.close();

    std::ofstream outfile7("symmetry_of_SA_SGD.txt", std::ios::trunc);
    if (!outfile7.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile7.close();

    std::ofstream outfile8("symmetry_of_SG.txt", std::ios::trunc);
    if (!outfile8.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile8.close();

    std::ofstream outfile9("symmetry_of_BiSG.txt", std::ios::trunc);
    if (!outfile9.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile9.close();

    std::ofstream outfile10("symmetry_of_CGS.txt", std::ios::trunc);
    if (!outfile10.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile10.close();

    std::ofstream outfile11("symmetry_of_QR.txt", std::ios::trunc);
    if (!outfile11.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile11.close();

    std::ofstream outfile12("symmetry_of_GS.txt", std::ios::trunc);
    if (!outfile12.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }
    outfile12.close();


    ////////////////////////CLEAR//////////////////////////



    for (int i = 10; i < 5000; i = i * 1.1){
        time_of_GS("symmetry_of_GS.txt", A, b, x_0, i, x);
        time_of_J("symmetry_of_J.txt", A, b, x_0, i, x);
        time_of_SGD("symmetry_of_SGD.txt", A, b, x_0, i, x);
        time_of_SA_GS("symmetry_of_SA_GS.txt", A, b, x_0, i, x);
        time_of_SA_J("symmetry_of_SA_J.txt", A, b, x_0, i, x);
        time_of_SA_SGD("symmetry_of_SA_SGD.txt", A, b, x_0, i, x);
        time_of_CG("symmetry_of_SG.txt", A, b, x_0, i, x);
        time_of_BiCG("symmetry_of_BiSG.txt", A, b, x_0, i, x);
        time_of_CGS("symmetry_of_CGS.txt", A, b, x_0, i, x);

    }
    for (int i = 2; i < 10000; i = i*2){
        time_of_ChA("symmetry_of_ChA.txt", A, b, x_0, i, x);
        time_of_SA_ChA("symmetry_of_SA_ChA.txt", A, b, x_0, i, x);
    }
    //time_of_QR("QR_decision.txt", A, b, x);

    return 0;
}
