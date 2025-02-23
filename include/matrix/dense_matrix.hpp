#pragma once
#include <iostream>
#include <vector>
#include "../include/matrix/Matrix.hpp"

template <typename T>

class dense_matrix : public Matrix{
private:
	std::vector<T> matrix_;
public:
	dense_matrix(size_t size_x, size_t size_y, const std::vector<std::vector<T>>& data) : Matrix(size_x, size_y){
		this->matrix_.resize(size_x * size_y);
		for(int x = 0; x < size_x; ++x)
			for(int y = 0; y < size_y; ++y)
				matrix_[y * size_x + x] = data[x][y];
	}

	dense_matrix(size_t size_x, size_t size_y) : Matrix(size_x, size_y){
		this->matrix_.resize(size_x * size_y);
	}


	T& operator() (size_t x, size_t y) {
		if (x >= this->get_size_x() || y >= this->get_size_y())
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		return matrix_[y * this->get_size_x() + x];
	}

	T operator() (size_t x, size_t y) const {
		if (x >= this->get_size_x() || y >= this->get_size_y())
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		return matrix_[y * this->get_size_x() + x];
	}


	std::vector<T> operator*(const std::vector<T>& vec) const {
        std::vector<T> result(get_size_x(), T(0)); // Инициализация нулями типа T
        for (size_t i = 0; i < this->get_size_x(); ++i) {
            for (size_t j = 0; j < this->get_size_y(); ++j) {
                result[i] += (*this)(i,j) * vec[j];
            }
        }
        return result;
    }

    std::vector<T> get_row(size_t item) const{
        if (item < 0 || item >= this->get_size_y()) {
            throw std::out_of_range("Row index out of bounds!\n");
        }
        std::vector<T> result;
        result.reserve(this->get_size_x());
        for(size_t x = 0; x < this->get_size_x(); ++x)
            result.push_back(matrix_[item * this->get_size_x() + x]);
        return result;
    }

    std::vector<T> get_col(size_t item) const{
        if (item < 0 || item >= this->get_size_x()) {
            throw std::out_of_range("Col index out of bounds!\n");
        }
        std::vector<T> result;
        result.reserve(this->get_size_y());
        for(size_t y = 0; y < get_size_y(); ++y)
            result.push_back(matrix_[y * this->get_size_x() + item]);
        return result;
    }

    std::vector<T> get_row(size_t item, size_t beg, size_t en) const{
        if (item < 0 || item >= this->get_size_x() || beg >= this->get_size_y()) {
            throw std::out_of_range("Row index out of bounds!\n");
        }
        std::vector<T> result;
        result.reserve(en - beg);
        for(size_t x = beg; x < en; ++x)
            result.push_back((*this)(x, item));

        return result;
    }

    std::vector<T> get_col(size_t item, size_t beg, size_t en) const{
        if (item >= this->get_size_x() || beg >= this->get_size_y() || en > this->get_size_y() || beg > en) {
            throw std::out_of_range("Col index out of bounds!\n");
        }
        std::vector<T> result;
        result.reserve(en - beg);

        for (size_t y = beg; y < en; ++y)
            result.push_back((*this)(item, y));

        return result;
    }


    void set_col(size_t col, const std::vector<T>& data, size_t start_row) {
        for (size_t i = 0; i < data.size(); ++i) {
            (*this)(col, start_row + i) = data[i];
        }
    }

    void set_row(size_t row, const std::vector<T>& data, size_t start_col) {
        for (size_t i = 0; i < data.size(); ++i) {
            (*this)(start_col + i, row) = data[i];
        }
    }

    dense_matrix<T> t() const{
        std::vector<std::vector<T>> result(this->get_size_x(), std::vector<T>(this->get_size_y()));

        for(int x = 0; x < this->get_size_x(); ++x){
            for(int y = 0; y < this->get_size_y(); ++y){
                result[x][y] = (*this)(y,x);
            }
        }

        return dense_matrix(this->get_size_x(), this->get_size_y(), result);
    }



    static dense_matrix<T> identity(size_t size_n) {
        dense_matrix<T> result(size_n, size_n);
        for (size_t i = 0; i < size_n; ++i) {
            result(i,i) = 1.0;
        }
        return result;
    }


    dense_matrix<T>& operator=(const dense_matrix<T>& data) {
        if(&data != this)
        {
            for(size_t x = 0; x < data.get_size_x(); ++x)
                for(size_t y = 0; y < data.get_size_y(); ++y)
                    (*this)(x, y) = data(x, y);
        }
        return *this;
    }

    dense_matrix<T> operator*(const dense_matrix<T>& other) const {
        // Проверяем, что столбцы первой матрицы == строкам второй
        if (get_size_y() != other.get_size_x()) {
            throw std::invalid_argument("Size mismatch: cols(A) != rows(B)");
        }

        // Результирующая матрица имеет размер: строки(A) × столбцы(B)
        dense_matrix<T> result(get_size_x(), other.get_size_y());

        for (size_t i = 0; i < get_size_x(); ++i) {         // Строки A
            for (size_t j = 0; j < other.get_size_y(); ++j) { // Столбцы B
                T sum = 0.0;
                for (size_t k = 0; k < get_size_y(); ++k) {   // Общее измерение
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
}

};

