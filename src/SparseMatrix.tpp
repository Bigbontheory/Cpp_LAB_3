

template<typename T>
int SparseMatrix<T>::bin_search(int i, int j) const {
	int left = 0;
	int right = data.get_size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		const auto& current = data.get(mid);
		if (current.row == i && current.col == j) {
			return mid;
		}
		if (current.row < i || (current.row == i && current.col < j)) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}

template<typename T>
void SparseMatrix<T>::check_dimensions(int rows, int cols) {
	if (rows < 0 || cols < 0) {
		throw std::invalid_argument("dimensions cant be negative");
	}
}

template<typename T>
int SparseMatrix<T>::check_size(int rows, int cols, int count) {
	check_dimensions(rows, cols);
	if (count < 0) {
		throw std::invalid_argument("count cant be negative");
	}
	return count;
}

template<typename T>
SparseMatrix<T>::SparseMatrix() : rows(0), cols(0), data() {}

template<typename T>
SparseMatrix<T>::SparseMatrix(int rows, int cols) : rows(rows), cols(cols), data() {
	check_dimensions(rows, cols);
}

template<typename T>
SparseMatrix<T>::SparseMatrix(const T*items, int rows, int cols, int count) :
	rows(rows),
	cols(cols),
	data(items, count) {
	check_dimensions(rows, cols);
}

template<typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& other) :
	rows(other.rows),
	cols(other.cols),
	data(other.data)
	{ }


template<typename T>
bool SparseMatrix<T>::in_bounds (int i, int j) const noexcept {
	return (i >= 0 && i < rows) && (j >= 0 && j < cols);
}

template<typename T>
const T& SparseMatrix<T>::get(int i, int j) const {
	if (!in_bounds(i, j)) {
		throw std::out_of_range("Index out of bounds");
	}
	int index = bin_search(i, j);
	if (index == -1) {
		return zero;
	}
	return data.get(index).value;
}

template<typename T>
int SparseMatrix<T>::get_rows() const {
	return rows;
}

template<typename T>
int SparseMatrix<T>:: get_cols() const{
	return cols;
}

template<typename T>
int SparseMatrix<T>::get_data_size() const{
	return data.get_size();
}

template<typename T>
void SparseMatrix<T>::set(int i, int j, const T& value) {
    if (!in_bounds(i, j)) {
        throw std::out_of_range("index out of range");
    }

    int index = bin_search(i, j);
    if (index != -1) {
        if (value == T()) {
            data.remove_at(index);
            return;
        }
        data.set(index, Triplet<T>{i, j, value});
    }
    else {
        if (value == T()) return;
        data.resize(data.get_size() + 1);
        int dst = data.get_size() - 1;
        while (dst > 0 && (data.get(dst - 1).row > i ||
            (data.get(dst - 1).row == i && data.get(dst - 1).col > j)))
        {
            data.set(dst, data.get(dst - 1));
            dst--;
        }
        data.set(dst, Triplet<T>{i, j, value});
    }
}

template <typename T>
SparseMatrix<T>* SparseMatrix<T>::add(const IMatrix<T>* other) const {
    if (!other) throw std::invalid_argument("matrix is null");
    if (rows != other->get_rows() || cols != other->get_cols())
        throw std::invalid_argument("dimensions mismatch");

    SparseMatrix<T>* result = new SparseMatrix<T>(rows, cols);
    try {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                T sum = get(i, j) + other->get(i, j);
                if (sum != T()) result->set(i, j, sum);
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
SparseMatrix<T>* SparseMatrix<T>::mult_scalar(const T scalar) const {
    SparseMatrix<T>* result = new SparseMatrix<T>(rows, cols);
    if (scalar == T()) return result;
    for (int i = 0; i < data.get_size(); ++i) {
        const auto& current = data.get(i);
        T new_val = current.value * scalar;
        if (new_val != T()) result->set(current.row, current.col, new_val);
    }
    return result;
}

template <typename T>
double SparseMatrix<T>::norm() const {
    double sum_of_squares = 0.0;
    for (int i = 0; i < data.get_size(); ++i) { 
        double val = static_cast<double>(data.get(i).value);
        sum_of_squares += val * val;
    }
    return std::sqrt(sum_of_squares);
}



