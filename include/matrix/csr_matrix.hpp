#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>  // Для форматирования вывода
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

    csr_matrix(size_t size_x, size_t size_y) :
	     Matrix(size_x, size_y){	}


	csr_matrix(size_t size_x, size_t size_y, const std::map<std::pair<size_t, size_t>, T>& matrix) : Matrix(size_x, size_y)
    {
        rows_.resize(size_y + 1, 0);
        // Считаем элементы в каждой строке транспонированной матрицы
        for (const auto& [key, val] : matrix) {
            size_t transposed_row = key.first; // Новая строка = исходный столбец
            if (transposed_row < size_y) {
                rows_[transposed_row + 1]++;
            }
        }
        // Накопительная сумма для rows_
        for (size_t i = 1; i <= size_y; ++i) {
            rows_[i] += rows_[i - 1];
        }
        // Заполняем cols_ и values_
        values_.resize(rows_[size_y]);
        cols_.resize(rows_[size_y]);
        std::vector<size_t> counters(size_y, 0);
        for (const auto& [key, val] : matrix) {
            size_t transposed_row = key.first;  // Новая строка = исходный столбец
            size_t transposed_col = key.second; // Новый столбец = исходная строка
            if (transposed_row >= size_y || transposed_col >= size_x) continue;
            size_t pos = rows_[transposed_row] + counters[transposed_row];
            cols_[pos] = transposed_col;
            values_[pos] = val;
            counters[transposed_row]++;
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


	/*T& operator() (size_t x, size_t y) {
		if (x >= get_size_x() || y >= get_size_y())
			throw std::out_of_range("You are invalid: incorrect indexing!\n");

		for(int i = rows_[y]; i < rows_[y+1]; ++i)
		{
			if (cols_[i] == x)
				return values_[i];
		}

		return T(0);
	}*/



	std::vector<T> operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->get_size_x()) {
        throw std::invalid_argument("Vector size must match matrix columns.");
    }

    std::vector<T> result(this->get_size_y(), T(0));

    for (size_t y = 0; y < this->get_size_y(); ++y) {
        T sum = 0;
        for (size_t x = this->rows_[y]; x < this->rows_[y + 1]; ++x) {
            size_t col = cols_[x];
            if (col >= vec.size()) {
                throw std::out_of_range("Column index " + std::to_string(col) + " is invalid.");
            }
            sum += this->values_[x] * vec[col];
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


    csr_matrix<T> t() const {
        std::map<std::pair<size_t, size_t>, T> transposed_map;
        for (size_t row = 0; row < get_size_x(); ++row) {
            for (size_t idx = rows_[row]; idx < rows_[row + 1]; ++idx) {
                size_t original_col = cols_[idx];
                T value = values_[idx];
                // Ключ: (исходный столбец, исходная строка) -> значение
                transposed_map[{original_col, row}] = value;
            }
        }
        return csr_matrix<T>(get_size_y(), get_size_x(), transposed_map);
    }

    void print(size_t column_width = 4) const {
        size_t rows = get_size_x();
        size_t cols = get_size_y();

        for (size_t i = 0; i < rows; ++i) {
            // Проверка на выход за границы массива rows_
            if (i + 1 >= rows_.size()) {
                throw std::runtime_error("Invalid CSR matrix structure.");
            }

            size_t row_start = rows_[i];
            size_t row_end = rows_[i + 1];

            // Создаем временный вектор для строки
            std::vector<T> row_vector(cols, 0);

            // Заполняем ненулевые элементы
            for (size_t k = row_start; k < row_end; ++k) {
                size_t col = cols_[k];
                if (col >= cols) {
                    throw std::out_of_range("Column index out of bounds.");
                }
                row_vector[col] = values_[k];
            }

            // Выводим строку
            for (const auto& val : row_vector) {
                std::cout << std::setw(column_width) << val << " ";
            }
            std::cout << std::endl;
        }
    }
};









