#pragma once

#include "Matrix.hpp"
#include <stdexcept>

template<typename T>
class SquareMatrix : public Matrix<T> {
public:
	SquareMatrix();
	explicit SquareMatrix(int n);
	SquareMatrix(const T* items, int n);
	SquareMatrix(const SquareMatrix<T>& other);
	SquareMatrix<T>& operator=(const SquareMatrix<T>&) = default;
	virtual ~SquareMatrix() override = default;
	
	int get_size() const;
	T trace() const;

	SquareMatrix<T>* add(const IMatrix<T>* other) const override;
	SquareMatrix<T>* mult_scalar(const T scalar) const override;
};

#include "SquareMatrix.tpp"