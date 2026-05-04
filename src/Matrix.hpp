#pragma once
#include "IMatrix.hpp"
#include "DynamicArray.hpp"
#include <stdexcept>
#include <cmath>

template <typename T>
class Matrix : public IMatrix<T> {
private:
	DynamicArray<T> data;
	static int check_index(int r, int c);
	bool check_bounds(int r, int c) const noexcept;

protected:
	bool check_row(int r) const noexcept; // долждна быть в 
	int rows;
	int cols;

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, const T* items);
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other) noexcept;
	Matrix& operator=(const Matrix&) = default;
	virtual ~Matrix() = default;

	int get_rows() const override;
	int get_cols() const override;
	const T& get(int i, int j) const override;
	void set (int i, int j, const T& value) override;
	double norm() const override;
	Matrix<T>* mult_scalar(const T scalar) const override;
	Matrix<T>* add(const IMatrix<T>* other) const override;

	void swap_rows(int row1, int row2);
	void scale_row(int row, const T& scalar);
	void add_row(int row1, int row2, const T& scalar);
};

#include "Matrix.tpp"