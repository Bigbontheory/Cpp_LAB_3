
template <typename T>
int Matrix<T>::check_index(int r, int c) {
    if (r < 0 || c < 0) {
        throw std::invalid_argument("Matrix dimensions must be positive!");
    }
    return r * c;
}

template <typename T> 
bool Matrix<T> ::check_bounds(int i, int j) const noexcept {
    return(i >= 0 && i < rows && j >= 0 && j < cols);
}

template <typename T>
bool Matrix<T>::check_row(int r) const noexcept {
    return r >= 0 && r < rows;
}

template <typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c), data(check_index(r,c)) {}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) :
    rows(other.rows),
    cols(other.cols),
    data(other.data)
{
}

template <typename T>
Matrix<T>::Matrix(int r, int c, const T* items) :
    rows(r),
    cols(c),
    data(items, check_index(r, c))
{
}

template <typename T>
Matrix<T>::Matrix():
    rows(0),
    cols(0),
    data()
{
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept : 
    rows(other.rows),
    cols(other.cols),
    data(std::move(other.data))
{
    other.rows = 0;
    other.cols = 0;
}

template <typename T>
int Matrix<T>::get_rows() const{
    return rows;
}

template <typename T>
int Matrix<T>::get_cols() const {
    return cols;
}

template <typename T>
const T& Matrix<T>::get(int i, int j) const {
    if (!check_bounds(i, j)) {
        throw std::invalid_argument("Matrix index out of bounds");
    }
    return data.get(cols * i + j);
}

template <typename T>
void Matrix<T>::set(int i, int j, const T& value) {
    if (!check_bounds(i, j)) {
        throw std::invalid_argument("Matrix out of bonds");
    }
    data.set(cols * i + j, value);
}

template <typename T>
double Matrix<T>::norm() const {
    double sum = 0.0;
    int total_elements = rows * cols;
    for (int i = 0; i < total_elements; ++i) {
        T val = data.get(i);
        sum += static_cast<double>(val) * static_cast<double>(val);
    }
    return std::sqrt(sum);
}

template <typename T>
Matrix<T>* Matrix<T>::mult_scalar(const T scalar) const {
    Matrix<T>* result = nullptr;
    try {
        result = new Matrix<T>(rows, cols);
        int total_el = rows * cols;
        for (int i = 0; i < total_el; ++i) {
            int r = i / cols;
            int c = i % cols;
            T new_value = this->get(r, c) * scalar;
            result->set(r, c, new_value);
        }
    }
    catch (...) {
        delete result;
        throw;
    }
    return result;
}

template<typename T>
Matrix<T>* Matrix<T>::add(const IMatrix<T>* other) const {
    if (!other) {
        throw std::invalid_argument("Other matrix is null");
    }
    if (this->rows != other->get_rows() || this->cols != other->get_cols()) {
        throw std::invalid_argument("Matrix dim must match for add");
    }

    Matrix<T>* result = nullptr;

    try {
        result = new Matrix<T>(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
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

template <typename T>
void Matrix<T>::swap_rows(int row1, int row2) {
    if (!this->check_row(row1) || !this->check_row(row2)) {
        throw std::out_of_range("Row index out of bounds");
    }
    if (row1 == row2) return;
    for (int j = 0; j < cols; ++j) {
        T temp = this->get(row1, j);
        this->set(row1, j, this->get(row2, j));
        this->set(row2, j, temp);
    }
}

template <typename T>
void Matrix<T>::scale_row(int row, const T& scalar) {
    if (!this->check_row(row)) {
        throw std::out_of_range("Row index out of bounds");
    }
    for (int j = 0; j < cols; ++j) {
        this->set(row, j, this->get(row, j) * scalar);
    }
}

template <typename T>
void Matrix<T>::add_row(int row1, int row2, const T& scalar) {
    if (!this->check_row(row1) || !this->check_row(row2)) {
        throw std::out_of_range("Row index out of bounds");
    }

    for (int j = 0; j < cols; ++j) {
        T val1 = this->get(row1, j);
        T val2 = this->get(row2, j);
        this->set(row2, j, val2 + (val1 * scalar));
    }
}

