
template<typename T>
SquareMatrix<T>::SquareMatrix() : Matrix<T>(0, 0) {}

template<typename T>
SquareMatrix<T>::SquareMatrix(int n) : Matrix<T>(n, n) {}

template<typename T>
SquareMatrix<T>::SquareMatrix(const T* items, int n) : Matrix<T>(n, n) {
    if (items == nullptr && n > 0) {
        throw std::invalid_argument("Source array is null");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            this->set(i, j, items[i * n + j]);
        }
    }
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other)
    : Matrix<T>(other) {} 

template <typename T>
int SquareMatrix<T>::get_size() const {
    return this->get_rows();
}

template <typename T>
T SquareMatrix<T>::trace() const {
    T sum = 0;
    int n = get_size();
    for (int i = 0; i < n; ++i) {
        sum += this->get(i, i);
    }
    return sum;
}

template <typename T>
SquareMatrix<T>* SquareMatrix<T>::mult_scalar(const T scalar) const {
    int n = this->get_size();
    SquareMatrix<T>* result = new SquareMatrix<T>(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result->set(i, j, this->get(i, j) * scalar);
        }
    }
    return result;
}

template <typename T>
SquareMatrix<T>* SquareMatrix<T>::add(const IMatrix<T>* other) const {
    if (!other) {
        throw std::invalid_argument("Other matrix pointer is null");
    }
    if (this->get_rows() != other->get_rows() || this->get_cols() != other->get_cols()) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    int n = this->get_size();
    SquareMatrix<T>* result = new SquareMatrix<T>(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result->set(i, j, this->get(i, j) + other->get(i, j));
        }
    }
    return result;
}