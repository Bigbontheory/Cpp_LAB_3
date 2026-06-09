template<class T>
Vector<T>::Vector()
    : data() {
}

template<class T>
Vector<T>::Vector(int n)
    : data(check_size(n)) {
}

template<class T>
Vector<T>::Vector(const T* items, int n)
    : data(items, check_size(n)) {
}

template<class T>
const T& Vector<T>::get(int index) const {
    check_index(index);
    return data.get(index);
}

template<class T>
int Vector<T>::get_size() const {
    return data.get_size();
}

template<class T>
void Vector<T>::set(int index, const T& value) {
    check_index(index);
    data.set(index, value);
}

template<class T>
double Vector<T>::norm() const {
    double sum = 0;
    for (int i = 0; i < get_size(); i++) {
        using std::abs;
        auto value = static_cast<double>(abs(this->get(i)));
        sum += value * value;
    }
    return std::sqrt(sum);
}

template<class T>
const T& Vector<T>::operator[](int index) const {
    check_index(index);
    return data.get(index);
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    compare_sizes(other);
    Vector<T> result(get_size());
    for (int i = 0; i < get_size(); i++)
        result.set(i, this->get(i) + other.get(i));
    return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    compare_sizes(other);
    Vector<T> result(get_size());
    for (int i = 0; i < get_size(); i++)
        result.set(i, this->get(i) - other.get(i));
    return result;
}

template<class T>
Vector<T> Vector<T>::operator*(const T& scalar) const {
    Vector<T> result(get_size());
    for (int i = 0; i < get_size(); i++)
        result.set(i, this->get(i) * scalar);
    return result;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other)
        return *this;

    if (this->get_size() != other.get_size()) {
        throw std::runtime_error("Different vector sizes");
    }

    data = other.data;
    return *this;
}

template<class T>
Vector<T> operator*(const IMatrix<T>& A, const Vector<T>& x) {
    if (A.get_cols() != x.get_size())
        throw std::invalid_argument("Matrix-Vector size mismatch");

    Vector<T> result(A.get_rows());
    for (int i = 0; i < A.get_rows(); i++) {
        T sum = T{};
        for (int j = 0; j < A.get_cols(); j++) {
            sum += A.get(i, j) * x[j];
        }
        result.set(i, sum);
    }
    return result;
}

template<class T>
int Vector<T>::check_size(int n) {
    if (n < 0)
        throw std::invalid_argument("Vector's size must be positive");
    return n;
}

template<class T>
void Vector<T>::check_index(int index) const {
    if (index < 0 || index >= get_size())
        throw std::out_of_range("Index out of range");
}

template<class T>
void Vector<T>::compare_sizes(const Vector<T>& other) const {
    if (get_size() != other.get_size())
        throw std::invalid_argument("Vector dimensions mismatch");
}

template<class T>
T Vector<T>::dot(const Vector<T>& other) const {
    compare_sizes(other);
    T result = T{};
    for (int i = 0; i < get_size(); i++) {
        result += this->get(i) * other.get(i);
    }
    return result;
}