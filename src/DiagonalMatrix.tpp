
template <typename T>
bool DiagonalMatrix<T>::check_range(int i, int j) const {
    return (i >= 0 && i < size && j >= 0 && j < size);
}

template <typename T>
DiagonalMatrix<T>::DiagonalMatrix() : size(0), data(0) {}

template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(int size) : size(size), data(size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
}

template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(const T* items, int size) : size(size), data(size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
    for (int i = 0; i < size; ++i) {
        data.set(i, items[i]);
    }
}

template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T>& other)
    : size(other.size), data(other.data) {
}

template <typename T>
const T& DiagonalMatrix<T>::get(int i, int j) const {
    if (!check_range(i, j)) {
        throw std::out_of_range("Index out of range");
    }
    if (i == j) {
        return data.get(i);
    }
    return zero;
}

template <typename T>
int DiagonalMatrix<T>::get_rows() const {
    return size;
}

template<typename T>
int DiagonalMatrix<T>::get_size() const {
    return size;
}

template <typename T>
int DiagonalMatrix<T>::get_cols() const {
    return size;
}

template <typename T>
void DiagonalMatrix<T>::set(int i, int j, const T& value) {
    if (!check_range(i, j)) {
        throw std::out_of_range("Index out of range");
    }

    if (i != j) {
        if (value != T{}) { 
            throw std::invalid_argument("Cannot set non-zero value outside the diagonal");
        }
        return;
    }

    data.set(i, value);
}

template <typename T>
double DiagonalMatrix<T>::norm() const {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        T val = data.get(i);
        sum += static_cast<double>(val * val);
    }
    return std::sqrt(sum);
}

template <typename T>
DiagonalMatrix<T>* DiagonalMatrix<T>::mult_scalar(T scalar) const {
    DiagonalMatrix<T>* result = nullptr;

    try {
        result = new DiagonalMatrix<T>(size);
        for (int i = 0; i < size; ++i) {
            result->data.set(i, this->data.get(i) * scalar);
        }
    }
    catch (...) {
        delete result;
        throw;
    }

    return result;
}

template <typename T>
SquareMatrix<T>* DiagonalMatrix<T>::add(const IMatrix<T>* other) const {
    if (this->get_rows() != other->get_rows() || this->get_cols() != other->get_cols()) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    int n = this->size;
    SquareMatrix<T>* result = nullptr;

    try {
        result = new SquareMatrix<T>(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                T sum = this->get(i, j) + other->get(i, j);
                result->set(i, j, sum);
            }
        }
    }
    catch (...) {
        delete result;
        throw;
    }

    return result;
}


