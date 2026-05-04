#include <gtest/gtest.h>
#include "DiagonalMatrix.hpp"

TEST(DiagonalMatrixTest, Constructors) {
    DiagonalMatrix<int> m1;
    EXPECT_EQ(m1.get_size(), 0);

    DiagonalMatrix<double> m2(5);
    EXPECT_EQ(m2.get_size(), 5);
    EXPECT_DOUBLE_EQ(m2.get(2, 2), 0.0);

    int arr[] = { 10, 20, 30 };
    DiagonalMatrix<int> m3(arr, 3);
    EXPECT_EQ(m3.get(0, 0), 10);
    EXPECT_EQ(m3.get(1, 1), 20);
    EXPECT_EQ(m3.get(2, 2), 30);
    EXPECT_EQ(m3.get(0, 1), 0);
}

TEST(DiagonalMatrixTest, SetMethod) {
    DiagonalMatrix<int> m(3);

    m.set(1, 1, 100);
    EXPECT_EQ(m.get(1, 1), 100);

    EXPECT_THROW(m.set(0, 1, 5), std::invalid_argument);
    EXPECT_NO_THROW(m.set(0, 1, 0));
    EXPECT_THROW(m.set(5, 5, 10), std::out_of_range);
}

TEST(DiagonalMatrixTest, MathOperations) {
    double arr[] = { 3.0, 4.0 };
    DiagonalMatrix<double> m(arr, 2);

    EXPECT_NEAR(m.norm(), 5.0, 1e-9);

    auto* scaled = m.mult_scalar(2.0);
    EXPECT_DOUBLE_EQ(scaled->get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(scaled->get(1, 1), 8.0);
    delete scaled;
}

TEST(DiagonalMatrixTest, Addition) {
    int arr[] = { 1, 2 };
    DiagonalMatrix<int> diag(arr, 2);

    SquareMatrix<int> other(2);
    other.set(0, 0, 10);
    other.set(0, 1, 5);
    other.set(1, 0, 5);
    other.set(1, 1, 10);

    auto* result = diag.add(&other);

    EXPECT_EQ(result->get(0, 0), 11);
    EXPECT_EQ(result->get(0, 1), 5);
    EXPECT_EQ(result->get(1, 1), 12);

    delete result;
}

TEST(DiagonalMatrixTest, Exceptions) {
    EXPECT_THROW(DiagonalMatrix<int> m(-1), std::invalid_argument);

    DiagonalMatrix<int> m(2);
    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
}