#pragma once

#include "DynamicArray.hpp"
#include "IMatrix.hpp"
#include "cmath"
#include <stdexcept>

template<class T>
class Vector {
public:
    Vector();
    explicit Vector(int n);
    Vector(const T* items, int n);
    Vector(const Vector<T>& other) = default;
    Vector(Vector<T>&& other) noexcept = default;
    ~Vector() = default;

    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other) noexcept = default;

    const T& get(int index) const;
    int get_size() const;
    void set(int index, const T& value);

    const T& operator[](int index) const;

    T dot(const Vector<T>& other) const;
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& scalar) const;
    double norm() const;

private:
    DynamicArray<T> data;

    static int check_size(int n);
    void compare_sizes(const Vector<T>& other) const;
    void check_index(int index) const;
};

#include "Vector.tpp"