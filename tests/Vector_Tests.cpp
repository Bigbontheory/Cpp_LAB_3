#include <gtest/gtest.h>
#include <cmath>

#include "Vector.hpp"
#include "IMatrix.hpp"

template <class T>
class MockMatrix : public IMatrix<T> {
private:
    int rows;
    int cols;
    T** data;

public:
    MockMatrix(int r, int c, T** d) : rows(r), cols(c), data(d) {}

    int get_rows() const override { return rows; }
    int get_cols() const override { return cols; }

    const T& get(int i, int j) const override { return data[i][j]; }
    void set(int i, int j, const T& value) override { data[i][j] = value; }

    double norm() const override { return 0.0; }
    IMatrix<T>* mult_scalar(T scalar) const override { return nullptr; }
    IMatrix<T>* add(const IMatrix<T>* other) const override { return nullptr; }
};

TEST(VectorConstructorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorConstructorTest, SizeConstructorValid) {
    Vector<int> v(5);
    EXPECT_EQ(v.get_size(), 5);
}

TEST(VectorConstructorTest, SizeConstructorInvalidThrows) {
    EXPECT_ANY_THROW(Vector<int> v(-1));
}

TEST(VectorConstructorTest, ArrayConstructorValid) {
    int arr[] = { 1, 2, 3, 4, 5 };
    Vector<int> v(arr, 5);
    EXPECT_EQ(v.get_size(), 5);
    EXPECT_EQ(v.get(0), 1);
    EXPECT_EQ(v.get(4), 5);
}

TEST(VectorConstructorTest, ArrayConstructorInvalidThrows) {
    int arr[] = { 1, 2, 3 };
    EXPECT_ANY_THROW(Vector<int> v(arr, -3));
}

TEST(VectorConstructorTest, CopyConstructor) {
    int arr[] = { 10, 20, 30 };
    Vector<int> original(arr, 3);
    Vector<int> copy(original);

    EXPECT_EQ(copy.get_size(), original.get_size());
    EXPECT_EQ(copy.get(0), 10);
    EXPECT_EQ(copy.get(2), 30);
}

TEST(VectorAccessTest, GetOutOfBoundsThrows) {
    Vector<int> v(3);
    EXPECT_ANY_THROW(v.get(-1));
    EXPECT_ANY_THROW(v.get(3));
}

TEST(VectorAccessTest, SetOutOfBoundsThrows) {
    Vector<int> v(3);
    EXPECT_ANY_THROW(v.set(10, -1));
    EXPECT_ANY_THROW(v.set(10, 3));
}

TEST(VectorAccessTest, OperatorSquareBrackets) {
    int arr[] = { 5, 6, 7 };
    Vector<int> v(arr, 3);

    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 6);
    EXPECT_ANY_THROW(v[-1]);
    EXPECT_ANY_THROW(v[3]);
}

TEST(VectorMathTest, NormCalculation) {
    double arr[] = { 3.0, -4.0, 0.0 };
    Vector<double> v(arr, 3);
    EXPECT_NEAR(v.norm(), 5.0, 1e-9);
}

TEST(VectorMathTest, DotProductValid) {
    int arr1[] = { 1, 2, 3 };
    int arr2[] = { 4, 5, 6 };
    Vector<int> v1(arr1, 3);
    Vector<int> v2(arr2, 3);

    EXPECT_EQ(v1.dot(v2), 32);
}

TEST(VectorMathTest, DotProductDimensionMismatchThrows) {
    Vector<int> v1(3);
    Vector<int> v2(4);

    EXPECT_ANY_THROW(v1.dot(v2));
}

TEST(VectorOperatorsTest, OperatorAssignmentSelf) {
    int arr[] = { 1, 2, 3 };
    Vector<int> v(arr, 3);

    v = v;
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_EQ(v.get(0), 1);
}

TEST(VectorOperatorsTest, OperatorAssignmentMismatchThrows) {
    Vector<int> v1(2);
    Vector<int> v2(3);

    EXPECT_ANY_THROW(v1 = v2);
}

TEST(MatrixVectorOperatorsTest, MultiplicationMismatchThrows) {
    Vector<int> x(2);
    auto lambda_check = [&]() {
        MockMatrix<int> A(2, 3, nullptr);
        if (A.get_cols() != x.get_size()) {
            throw std::invalid_argument("Matrix-Vector size mismatch");
        }
        };
    EXPECT_ANY_THROW(lambda_check());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}