#pragma once

template<typename T>
class IMatrix {
public:
	virtual ~IMatrix() = default;

	virtual int get_rows() const = 0;
	virtual int get_cols() const = 0;

	virtual const T& get (int i, int j) const = 0;
	virtual void set(int i, int j, const T& value) = 0;

	virtual double get_norm() const = 0; 
	virtual IMatrix<T>* mult_scalar(T scalar) const = 0;
	virtual IMatrix<T>* add(const IMatrix<T>* other) const = 0;
	virtual IMatrix<T>* clone() const = 0;
};