#include <gtest/gtest.h>
#include "SparseMatrix.hpp"

TEST(SparseMatrixTest, DefaultConstructor) {
    SparseMatrix<int> m;
    EXPECT_EQ(m.get_rows(), 0);
    EXPECT_EQ(m.get_cols(), 0);
    EXPECT_EQ(m.get_data_size(), 0);
}

TEST(SparseMatrixTest, SizeConstructor) {
    SparseMatrix<double> m(5, 8);
    EXPECT_EQ(m.get_rows(), 5);
    EXPECT_EQ(m.get_cols(), 8);
    EXPECT_EQ(m.get_data_size(), 0);
}

TEST(SparseMatrixTest, CopyConstructor) {
    SparseMatrix<int> original(3, 3);
    original.set(1, 1, 42);

    SparseMatrix<int> copy(original);
    EXPECT_EQ(copy.get_rows(), 3);
    EXPECT_EQ(copy.get_cols(), 3);
    EXPECT_EQ(copy.get_data_size(), 1);
    EXPECT_EQ(copy.get(1, 1), 42);
}

TEST(SparseMatrixTest, NegativeDimensionsException) {
    EXPECT_THROW(SparseMatrix<int> m(-1, 5), std::invalid_argument);
    EXPECT_THROW(SparseMatrix<int> m(5, -1), std::invalid_argument);
    EXPECT_THROW(SparseMatrix<int> m(-1, -1), std::invalid_argument);
}

TEST(SparseMatrixTest, IndexOutOfBoundsException) {
    SparseMatrix<int> m(3, 3);

    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, -1), std::out_of_range);
    EXPECT_THROW(m.get(3, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, 3), std::out_of_range);

    EXPECT_THROW(m.set(-1, 0, 10), std::out_of_range);
    EXPECT_THROW(m.set(0, -1, 10), std::out_of_range);
    EXPECT_THROW(m.set(3, 0, 10), std::out_of_range);
    EXPECT_THROW(m.set(0, 3, 10), std::out_of_range);
}

TEST(SparseMatrixTest, SetAndGetElements) {
    SparseMatrix<int> m(4, 4);

    EXPECT_EQ(m.get(2, 2), 0);

    m.set(2, 2, 15);
    EXPECT_EQ(m.get(2, 2), 15);
    EXPECT_EQ(m.get_data_size(), 1);

    m.set(2, 2, 99);
    EXPECT_EQ(m.get(2, 2), 99);
    EXPECT_EQ(m.get_data_size(), 1);

    m.set(0, 0, 0);
    EXPECT_EQ(m.get(0, 0), 0);
    EXPECT_EQ(m.get_data_size(), 1);

    m.set(2, 2, 0);
    EXPECT_EQ(m.get(2, 2), 0);
    EXPECT_EQ(m.get_data_size(), 0);
}

TEST(SparseMatrixTest, InsertionOrderAndBinarySearch) {
    SparseMatrix<int> m(5, 5);

    m.set(2, 2, 22);
    m.set(0, 1, 1);
    m.set(4, 4, 44);
    m.set(2, 1, 21);
    m.set(0, 0, -1);

    EXPECT_EQ(m.get(0, 0), -1);
    EXPECT_EQ(m.get(0, 1), 1);
    EXPECT_EQ(m.get(2, 1), 21);
    EXPECT_EQ(m.get(2, 2), 22);
    EXPECT_EQ(m.get(4, 4), 44);

    EXPECT_EQ(m.get(2, 3), 0);
}

TEST(SparseMatrixTest, MultScalar) {
    SparseMatrix<double> m(2, 2);
    m.set(0, 0, 3.0);
    m.set(1, 1, -1.5);

    auto* res1 = m.mult_scalar(2.0);
    EXPECT_DOUBLE_EQ(res1->get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(res1->get(1, 1), -3.0);
    EXPECT_EQ(res1->get_data_size(), 2);
    delete res1;

    auto* res_zero = m.mult_scalar(0.0);
    EXPECT_DOUBLE_EQ(res_zero->get(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(res_zero->get(1, 1), 0.0);
    EXPECT_EQ(res_zero->get_data_size(), 0);
    delete res_zero;
}

TEST(SparseMatrixTest, Norm) {
    SparseMatrix<double> m(3, 3);
    EXPECT_NEAR(m.norm(), 0.0, 1e-9);

    m.set(0, 1, 3.0);
    m.set(2, 2, 4.0);
    EXPECT_NEAR(m.norm(), 5.0, 1e-9);
}

TEST(SparseMatrixTest, AdditionValid) {
    SparseMatrix<int> m1(2, 2);
    m1.set(0, 0, 5);
    m1.set(1, 1, 10);

    SparseMatrix<int> m2(2, 2);
    m2.set(0, 0, 2);
    m2.set(1, 1, 2);

    auto* result = m1.add(&m2);

    EXPECT_EQ(result->get_rows(), 2);
    EXPECT_EQ(result->get_cols(), 2);

    EXPECT_EQ(result->get(0, 0), 7);
    EXPECT_EQ(result->get(0, 1), 0);
    EXPECT_EQ(result->get(1, 1), 12);

    delete result;
}

TEST(SparseMatrixTest, AdditionDimensionsMismatchException) {
    SparseMatrix<int> m1(2, 2);
    SparseMatrix<int> m2(3, 2);

    EXPECT_THROW(m1.add(&m2), std::invalid_argument);
}