#pragma once
#include "IMatrix.hpp"
#include "DynamicArray.hpp"

template <typename T>
class Matrix : public IMatrix<T> {
private:
	DynamicArray<T> data;
	int rows;
	int cols;
	static int check_index(int r, int c);
	bool check_bounds(int r, int c) const noexcept;

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, const T* items);
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other) noexcept;
	virtual ~Matrix() = default;

	Matrix<T>& operator=(const Matrix<T>& other);
	Matrix<T>& operator=(const Matrix<T>&& other) noexcept;

	int get_rows() const override;
	int get_cols() const override;
	const T& get(int i, int j) const override;
	void set (int i, int j, const T& value) override;
	double norm() const override;
	Matrix<T>* mult_scalar(T scalar) const override;
	Matrix<T>* add(const IMatrix<T>* other) const override;
	Matrix<T>* clone() const override;
};

#include "Matrix.tpp"