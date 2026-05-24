
template<typename T>
void TriangleMatrix<T>::check_bounds(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw std::out_of_range("TriangleMatrix: index out of bounds");
    }
}

template<typename T>
bool TriangleMatrix<T>::is_in_triangle(int i, int j) const {
    if (type == TriangleType::Lower) {
        return i >= j;
    }
    else {
        return i <= j;
    }
}

template<typename T>
int TriangleMatrix<T>::get_linear_index(int i, int j) const {
    if (type == TriangleType::Lower) {

        return (i * (i + 1)) / 2 + j;
    }
    else {
        return i * size - (i * (i - 1)) / 2 + (j - i);
    }
}

template<typename T>
int TriangleMatrix<T>::checked_size(int size) {
    if (size < 0)
        throw std::invalid_argument("TriangleMatrix: size cannot be negative");

    if (size > 0 && size > (INT_MAX / (size + 1)))
        throw std::overflow_error("TriangleMatrix: size is too large, storage calculation overflows");

    return size * (size + 1) / 2;
}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(int n, TriangleType type)
    : size(n),
    type(type),
    data(checked_size(n))
{
}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(const T* items, int n, TriangleType type)
    : size(n),
    type(type),
    data(checked_size(n))
{
    if (items == nullptr && n > 0) {
        throw std::invalid_argument("TriangleMatrix: source items pointer is null");
    }

    int count = checked_size(n);
    for (int i = 0; i < count; ++i) {
        data.set(i, items[i]);
    }
}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other)
    : size(other.size),
    type(other.type),
    data(other.data)
{
}

template<typename T>
int TriangleMatrix<T>::get_cols() const {
    return size;
}

template<typename T>
int TriangleMatrix<T>::get_rows() const {
    return size;
}

template<typename T>
int TriangleMatrix<T>::get_size() const {
    return size;
}

template<typename T>
typename TriangleMatrix<T>::TriangleType TriangleMatrix<T>::get_type() const {
    return type;
}

template<typename T>
const T& TriangleMatrix<T>::get(int i, int j) const {
    check_bounds(i, j);
    if (!is_in_triangle(i, j)) {
        return zero;
    }
    return data.get(get_linear_index(i, j));
}

template<typename T>
void TriangleMatrix<T>::set(int i, int j, const T& value) {
    check_bounds(i, j);

    if (!is_in_triangle(i, j)) {
        if (!(value == zero)) {
            throw std::invalid_argument("TriangleMatrix: cannot set non-zero value outside the triangle zone");
        }
        return;
    }
    data.set(get_linear_index(i, j), value);
}

template<typename T>
double TriangleMatrix<T>::norm() const {
    double sum_sq = 0.0;
    int count = checked_size(size);

    for (int k = 0; k < count; ++k) {
        T value = data.get(k);
        sum_sq += static_cast<double>(value * value);
    }

    return std::sqrt(sum_sq);
}

template<typename T>
SquareMatrix<T>* TriangleMatrix<T>::add(const IMatrix<T>* other) const {
    if (!other) {
        throw std::invalid_argument("TriangleMatrix::add - Other matrix is null");
    }
    if (this->size != other->get_rows() || this->size != other->get_cols()) {
        throw std::invalid_argument("TriangleMatrix::add - Matrix dimensions must match");
    }

    SquareMatrix<T>* result = nullptr;

    try {
        result = new SquareMatrix<T>(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                T sum_val = this->get(i, j) + other->get(i, j);
                result->set(i, j, sum_val);
            }
        }
    }
    catch (...) {
        delete result;
        throw;
    }

    return result;
}

template<typename T>
TriangleMatrix<T>* TriangleMatrix<T>::mult_scalar(T scalar) const {
    TriangleMatrix<T>* result = nullptr;

    try {
        result = new TriangleMatrix<T>(size, type);
        int count = checked_size(size);

        for (int k = 0; k < count; ++k) {
            T new_value = this->data.get(k) * scalar;
            result->data.set(k, new_value);
        }
    }
    catch (...) {
        delete result;
        throw;
    }

    return result;
}
