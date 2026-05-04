#include <gtest/gtest.h>
#include "Matrix.hpp"

TEST(MatrixTest, ConstructorAndSize) {
    Matrix<int> m(3, 5);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 5);
}

TEST(MatrixTest, GetAndSet) {
    Matrix<int> m(2, 2);
    m.set(0, 0, 10);
    m.set(1, 1, 20);

    EXPECT_EQ(m.get(0, 0), 10);
    EXPECT_EQ(m.get(1, 1), 20);
    EXPECT_EQ(m.get(0, 1), 0);
}

TEST(MatrixTest, BoundsException) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.get(5, 5), std::invalid_argument);
    EXPECT_THROW(m.set(-1, 0, 10), std::invalid_argument);
}

TEST(MatrixTest, Addition) {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);

    m1.set(0, 0, 1); m1.set(0, 1, 2);
    m2.set(0, 0, 10); m2.set(0, 1, 20);

    Matrix<int>* result = m1.add(&m2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->get(0, 0), 11);
    EXPECT_EQ(result->get(0, 1), 22);

    delete result;
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix<int> m(2, 2);
    m.set(0, 0, 5);

    Matrix<int>* result = m.mult_scalar(2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->get(0, 0), 10);

    delete result;
}

TEST(MatrixTest, NormCalculation) {
    Matrix<double> m(1, 2);
    m.set(0, 0, 3.0);
    m.set(0, 1, 4.0);

    EXPECT_DOUBLE_EQ(m.norm(), 5.0);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m1(2, 2);
    m1.set(0, 0, 99);

    Matrix<int> m2(m1);

    EXPECT_EQ(m2.get(0, 0), 99);
    m2.set(0, 0, 1);
    EXPECT_EQ(m1.get(0, 0), 99);
}

TEST(MatrixTest, ZeroMatrix) {
    Matrix<int> m(1, 1);
    m.set(0, 0, 0);
    EXPECT_DOUBLE_EQ(m.norm(), 0.0);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix<int> m1(2, 2);
    m1.set(0, 0, 5);

    Matrix<int> m2(std::move(m1));

    EXPECT_EQ(m2.get(0, 0), 5);
    EXPECT_EQ(m1.get_rows(), 0);
}

TEST(MatrixTest, AdditionIncompatibleSize) {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(3, 3);

    EXPECT_THROW(m1.add(&m2), std::invalid_argument);
}

#include <gtest/gtest.h>
#include "Matrix.hpp"

TEST(MatrixTest, SwapRows) {
    Matrix<int> m(3, 2);
    m.set(0, 0, 1); m.set(0, 1, 2);
    m.set(1, 0, 3); m.set(1, 1, 4);
    m.set(2, 0, 5); m.set(2, 1, 6);

    m.swap_rows(0, 2);

    EXPECT_EQ(m.get(0, 0), 5);
    EXPECT_EQ(m.get(0, 1), 6);
    EXPECT_EQ(m.get(1, 0), 3);
    EXPECT_EQ(m.get(2, 0), 1);
    EXPECT_EQ(m.get(2, 1), 2);
}

TEST(MatrixTest, ScaleRow) {
    Matrix<double> m(2, 2);
    m.set(0, 0, 2.0); m.set(0, 1, 4.0);

    m.scale_row(0, 0.5);

    EXPECT_DOUBLE_EQ(m.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.get(0, 1), 2.0);
}

TEST(MatrixTest, AddRow) {
    Matrix<int> m(2, 2);
    m.set(0, 0, 1); m.set(0, 1, 2);
    m.set(1, 0, 10); m.set(1, 1, 20);

    m.add_row(0, 1, 3);

    EXPECT_EQ(m.get(1, 0), 13);
    EXPECT_EQ(m.get(1, 1), 26);
    EXPECT_EQ(m.get(0, 0), 1);
}

TEST(MatrixTest, ElementaryOpsExceptions) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.swap_rows(0, 5), std::out_of_range);
    EXPECT_THROW(m.scale_row(-1, 2), std::out_of_range);
    EXPECT_THROW(m.add_row(0, 10, 1), std::out_of_range);
}

TEST(MatrixTest, SwapSameRow) {
    Matrix<int> m(1, 1);
    m.set(0, 0, 42);
    ASSERT_NO_THROW(m.swap_rows(0, 0));
    EXPECT_EQ(m.get(0, 0), 42);
}