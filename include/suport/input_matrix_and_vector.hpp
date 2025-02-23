#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/dense_matrix.hpp"


using T = double;
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


template <typename T>
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
