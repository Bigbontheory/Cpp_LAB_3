#pragma once 
#include "IMatrix.hpp"
#include <stdexcept>
#include <cmath>
#include"DynamicArray.hpp"

template <typename T>
struct Triplet{
	int row;
	int col;
	T value;
};

template <typename T>
class SparseMatrix : public IMatrix<T> {
public:
	SparseMatrix();
	SparseMatrix(int rows, int cols);
	SparseMatrix(const T* items, int rows, int cols, int count);
	SparseMatrix(const SparseMatrix<T>& other);
	SparseMatrix& operator=(const SparseMatrix&) = default;
	~SparseMatrix() override = default;

	const T& get(int i, int j) const override;

	int get_rows() const override;
	int get_cols() const override;

	int get_data_size() const;

	void set(int i, int j, const T& value) override;

	SparseMatrix<T>* add(const IMatrix<T>* other) const override;
	SparseMatrix<T>* mult_scalar(const T scalar) const override;
	double norm() const override;


private:
	int rows;
	int cols;
	DynamicArray<Triplet<T>> data;
	static inline const T zero{};

	static int check_size(int rows, int cols, int count);
	static void check_dimensions(int rows, int cols);
	bool in_bounds(int i, int j) const noexcept;
	int bin_search(int i, int j) const;
};

#include "SparseMatrix.tpp"
