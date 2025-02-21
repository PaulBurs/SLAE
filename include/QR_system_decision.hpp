#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "../include/dense_matrix.hpp"
#include "../include/algorithm_of_Householder.hpp"
#include "../include/vector_operations.hpp"


using T = double; // or float
std::vector<T> input_vector(size_t n){
    std::vector<T> v(n);
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    while (ss >> n) {
        v.push_back(n);
    }
    return v;

}


std::pair<dense_matrix<T>, std::vector<T>> input_A_f(){
    std::cout << "Enter the size of the space: ";
    size_t n;
    std::cin >> n;
    std::cout << "" << std::endl;
    std::cout << "Enter the matrix A line by line: " << std::endl;
    std::vector<std::vector<T>> A(n, std::vector<T>(n));
    for(size_t row = 0; row < n; ++row){
        std::vector<T> v = input_vector(n);
        if (v.size() != n)
            throw std::out_of_range("Incorrect number of items in a row!\n");
        A[row] = v;
    }

    std::cout << "Enter the vector f: " << std::endl;
    std::vector<T> f(n);
    std::vector<T> v = input_vector(n);
    if (v.size() != n)
            throw std::out_of_range("Incorrect number of items in a f!\n");
    f = v;

    return {dense_matrix(n,n,A), f};
}


template <typename T>
std::vector<T> decision_system_with_QR(const dense_matrix<T>& A, const std::vector<T>& f){
    size_t n = A.get_size_x();
    std::pair<dense_matrix<T>, dense_matrix<T>> QR = QR_decomposition(A);
    dense_matrix<T> QT = QR.first.t();
    dense_matrix<T> R = QR.second;
    std::vector<T> g = QT * f;
    std::vector<T> x(n);

    for(int i = n - 1; i >= 0; --i){
        T sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += R(i, j) * x[j];
        }
        x[i] = (g[i] - sum) / R(i, i);
    }
    return x;
}







