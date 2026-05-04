#pragma once

#include "DynamicArray.hpp"
#include "SquareMatrix.hpp"
#include <cmath>
#include <stdexcept>

template<typename T>
class DiagonalMatrix : public IMatrix<T> {
public:
	DiagonalMatrix();
	explicit DiagonalMatrix(int n);
	DiagonalMatrix(const T* items, int n);
	DiagonalMatrix(const DiagonalMatrix<T>& other);
	DiagonalMatrix<T>& operator=(const DiagonalMatrix<T>& other) = default;
	virtual ~DiagonalMatrix() override = default;

	const T& get(int row, int collum) const override;
	int get_rows() const override;
	int get_cols() const override;
	int get_size() const;

	double norm() const override;
	void set(int i, int j, const T& value) override;
	SquareMatrix<T>* add(const IMatrix<T>* other) const override;
	DiagonalMatrix<T>* mult_scalar(T scalar) const override;

private:
	DynamicArray<T> data;
	int size;
	static inline const T zero{};
	bool check_range(int i, int j) const;

};

#include "DiagonalMatrix.tpp"