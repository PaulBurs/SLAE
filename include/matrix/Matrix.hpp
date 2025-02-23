#pragma once

class Matrix {
private:
    size_t size_x_;
    size_t size_y_;

protected:
    Matrix(size_t size_x, size_t size_y){
    size_x_ = size_x;
    size_y_ = size_y;
}

public:
    virtual ~Matrix() = default;

    size_t get_size_x() const
	{
	    return size_x_;
	}

	size_t get_size_y() const
	{
	    return size_y_;
	}
};
