#pragma once

#include "IMatrix.hpp"
#include "DynamicArray.hpp"
#include "SquareMatrix.hpp"
#include <stdexcept>



template<typename T>
class TriangleMatrix : public IMatrix<T> {
public:

	enum class TriangleType {
		Lower,
		Upper
	};

	TriangleMatrix(int n, TriangleType type);
	TriangleMatrix(const T* items, int n, TriangleType type);
	TriangleMatrix(const TriangleMatrix<T>& other);
	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) = default;

	virtual ~TriangleMatrix() = default;

	int get_cols() const override;
	int get_rows() const override;
	int get_size() const;
	TriangleType get_type() const;
	
	const T& get(int i, int j) const override;
	void set(int i, int j, const T& value) override;
	double norm() const override;

	SquareMatrix<T>* add(const IMatrix<T>* other) const override;
	TriangleMatrix<T>* mult_scalar(T scalar) const override;


private:
	DynamicArray<T> data;
	int size;
	TriangleType type;

	static inline const T zero{};

	int get_linear_index(int rows, int cols) const;
	bool is_in_triangle(int i, int j) const;
	void check_bounds(int i, int j) const;
	static int checked_size(int size);



};

#include "TriangleMatrix.tpp"