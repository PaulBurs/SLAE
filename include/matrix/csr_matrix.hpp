#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "../include/matrix/Matrix.hpp"
#include "../include/matrix/dense_matrix.hpp"
#include "../include/suport/vector_operations.hpp"

template <typename T>

class csr_matrix : public Matrix{
private:
	std::vector<T> values_ = {};
	std::vector<size_t> cols_ = {};
	std::vector<size_t> rows_ = {0};
public:
    csr_matrix();

	csr_matrix(const dense_matrix<T>& matrix) : Matrix(matrix.get_size_x(), matrix.get_size_y())	{
		for(int x = 0; x < get_size_x(); ++x)
		{
			rows_.push_back(rows_[x]);
			for(int y = 0; y < get_size_y(); ++y)
				{
					if (matrix(x, y) != 0)
					{
						values_.push_back(matrix(x, y));
						cols_.push_back(y);
						rows_[x+1] += 1;
					}
				}
		}

	}

	csr_matrix(size_t size_x, size_t size_y, std::vector<T> values, std::vector<size_t> cols, std::vector<size_t> rows) :
	     Matrix(size_x, size_y), values_(values), cols_(cols), rows_(rows)	{	}


	/*csr_matrix(size_t size_x, size_t size_y, const vector<vector<T>>& matrix)	{
		size_x_ = size_x;
		size_y_ = size_y;
		for(int x = 0; x < size_x; ++x)
		{
			rows_.push_back(rows_[x]);
			for(int y = 0; y < size_y; ++y)
				{
					if (matrix(x, y) != 0)
					{
						values_.push_back(matrix[x, y]);
						cols_.push_back(x);
						rows_[x+1] += 1;
					}
				}
		}

	}*/


	csr_matrix(size_t size_x, size_t size_y, const std::map<std::pair<size_t, size_t>, T>& matrix) : Matrix(size_x, size_y){
        rows_.resize(size_y + 1, 0);

        for (const auto& elem : matrix) {
            size_t row = elem.first.second;
            if (row < size_y) {
                rows_[row + 1]++;
            }
        }

        for (size_t i = 1; i <= size_y; ++i) {
            rows_[i] += rows_[i - 1];
        }

        values_.resize(rows_[size_y]);
        cols_.resize(rows_[size_y]);
        std::vector<size_t> counters(size_y, 0);

        for (const auto& elem : matrix) {
            size_t col = elem.first.first;
            size_t row = elem.first.second;
            T value = elem.second;

            if (row >= size_y || col >= size_x) continue;

            size_t pos = rows_[row] + counters[row];
            if (pos >= values_.size()) continue;

            cols_[pos] = col;
            values_[pos] = value;
            counters[row]++;
        }
    }


    static csr_matrix<T> identity(size_t size_n) {
        dense_matrix<T> dense = dense_matrix<T>::identity(size_n);
        csr_matrix<T> csr(dense);
        return csr;
    }


	T operator() (size_t x, size_t y) const{
		if (x >= get_size_x() || y >= get_size_y())
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		for(int i = rows_[y]; i < rows_[y+1]; ++i)
		{
			if (cols_[i] == x)
				return values_[i];
		}

		return T(0);
	}


	T& operator() (size_t x, size_t y) {
		if (x >= get_size_x() || y >= get_size_y())
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		for(int i = rows_[y]; i < rows_[y+1]; ++i)
		{
			if (cols_[i] == x)
				return values_[i];
		}

		return T(0);
	}



	std::vector<T> operator*(const std::vector<T>& vec) const{

    if (vec.size() != this->get_size_x())
    {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }

    std::vector<T> result(this->get_size_y(), T(0));

    for(int y = 0; y < this->get_size_y(); ++y)
    {
        T sum = 0;
        for(int x = this->rows_[y]; x < this->rows_[y+1]; ++x)
        {
            sum += this->values_[x] * vec[cols_[x]];
        }
        result[y] = sum;
    }

    return result;
	}

	csr_matrix<T> operator*(const T x) const{
        std::vector<T> tmp = this->values_;
	    csr_matrix<T> m(this->get_size_x(), this->get_size_y(), x * tmp, cols_, rows_);
        return m;
	}

	csr_matrix<T> operator=(const csr_matrix<T> x){
	    csr_matrix<T> m(this->get_size_x(), this->get_size_y(), values_, cols_, rows_);
        return m;
	}

	/*std::vector<T> operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->get_size_x()) {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }


    std::vector<T> result(this->get_size_y(), 0);

    for (size_t i = 0; i < this->get_size_y()-1; ++i) {
        const size_t row_start = rows_[i];
        const size_t row_end = rows_[i + 1];

        for (size_t j = row_start; j < row_end; ++j) {
            result[i] += values_[j] * vec[cols_[j]];
        }
    }

    return result;
}*/

};









