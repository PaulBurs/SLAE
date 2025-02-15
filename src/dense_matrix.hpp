#pragma once
#include <iostream>
#include <vector>

template <typename T>

class dense_matrix{
private:
	size_t size_x_;
	size_t size_y_;
	std::vector<T> matrix_;
public:
	dense_matrix(size_t size_x, size_t size_y, const std::vector<std::vector<T>>& matrix)
	{
		size_x_ = size_x;
		size_y_ = size_y;
		matrix_.reserve(size_x_ * size_y_);
		for(int x = 0; x < size_x; ++x)
			for(int y = 0; y < size_y; ++y)
				matrix_[x * size_y + y] = matrix[x][y];
	}

	T& operator() (size_t x, size_t y)
	{
		if (x >= size_x_ || y >= size_y_)
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		return matrix_[x * size_y_ + y];
	}

	T operator() (size_t x, size_t y) const
	{
		if (x >= size_x_ || y >= size_y_)
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		return matrix_[x * size_y_ + y];
	}

	size_t get_size_x() const
	{
	    return size_x_;
	}

	size_t get_size_y() const
	{
	    return size_y_;
	}

	std::vector<T> operator * (const std::vector<T>& vec) const{
    if (vec.size() != size_y_)
    {
        throw std::invalid_argument("You are invalid: the vectors must be the same size!");
    }

    std::vector<T> result;
    result.reserve(size_x_);

    for (int y = 0; y < size_y_; ++y)
    {
        T sum = 0;
        for (int x = 0; x < size_x_; ++x)
        {
            sum += vec[y] * matrix_[x + y * size_x_];
        }
        result.push_back(sum);
    }

    return result;
};

};
