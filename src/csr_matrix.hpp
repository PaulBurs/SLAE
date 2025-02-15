#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <dense_matrix.hpp>

template <typename T>

class csr_matrix{
private:
	size_t size_x_;
	size_t size_y_;
	std::vector<T> values_;
	std::vector<size_t> cols_;
	std::vector<size_t> rows_ = {0};
public:
	csr_matrix(const dense_matrix<T>& matrix)	{
		size_x_ = matrix.get_size_x();
		size_y_ = matrix.get_size_y();
		for(int x = 0; x < size_x_; ++x)
		{
			rows_.push_back(rows_[x]);
			for(int y = 0; y < size_y_; ++y)
				{
					if (matrix(x, y) != 0)
					{
						values_.push_back(matrix(x, y));
						cols_.push_back(x);
						rows_[x+1] += 1;
					}
				}
		}

	}


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


	csr_matrix(size_t size_x, size_t size_y, const std::map<std::pair<size_t, size_t>, T>& matrix) {
        size_x_ = size_x;
        size_y_ = size_y;
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


	T operator() (size_t x, size_t y){
		if (x >= size_x_ || y >= size_y_)
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		for(int i = rows_[y]; i < rows_[y+1]; ++i)
		{
			if (cols_[i] == x)
				return values_[i];
		}

		return 0;
	}


	T& operator() (size_t x, size_t y) const{
		if (x >= size_x_ || y >= size_y_)
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		for(int i = rows_[y]; i < rows_[y+1]; ++i)
		{
			if (cols_[i] == x)
				return values_[i];
		}

		return 0;
	}


	size_t get_size_x() const{
	    return size_x_;
	}


	size_t get_size_y() const{
	    return size_y_;
	}


	std::vector<T> operator*(const std::vector<T>& vec) const{
    if (vec.size() != rows_.size()-1)
    {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }

    std::vector<T> result;
    result.reserve(cols_.size());

    for(int y = 0; y < rows_.size(); ++y)
    {
        T sum = 0;
        for(int x = rows_[y]; x < rows_[y+1]; ++x)
        {
            sum += values_[y];
        }
        result.push_back(sum);
    }

    return result;
	}

};









