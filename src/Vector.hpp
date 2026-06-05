#pragma once

#include "DynamicArray.hpp"
#include "IMatrix.hpp"
#include "cmath"

template<class T>
class Vector {

public:
    Vector();
    Vector(int n);
    Vector(T* items, int n);
    Vector(const Vector<T>& other);

    ~Vector() = default;

    const T& get(int index) const;

    int get_size() const;

    void set(const T& value, int index);

    const T& operator[](int index) const;

    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& scalar) const;
    Vector<T>& operator=(const Vector<T>& other);

    T dot(const Vector<T>& other) const; 
    double norm() const;

private:
    DynamicArray<T> data;
    int n;

    static int check_size(int n);
    void compare_sizes(const Vector<T>& other) const;
    void check_index(int index) const;
};

#include "Vector.tpp"