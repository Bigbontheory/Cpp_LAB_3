#include <gtest/gtest.h>
#include "SquareMatrix.hpp"

TEST(SquareMatrixTest, ConstructorAndSize) {
    SquareMatrix<int> sm1(4);
    EXPECT_EQ(sm1.get_size(), 4);
    EXPECT_EQ(sm1.get_rows(), 4);
    EXPECT_EQ(sm1.get_cols(), 4);

    SquareMatrix<int> smDefault;
    EXPECT_EQ(smDefault.get_size(), 0);
}

TEST(SquareMatrixTest, ArrayConstructor) {
    int data[] = {
        1, 2,
        3, 4
    };
    SquareMatrix<int> sm(data, 2);

    EXPECT_EQ(sm.get(0, 0), 1);
    EXPECT_EQ(sm.get(0, 1), 2);
    EXPECT_EQ(sm.get(1, 0), 3);
    EXPECT_EQ(sm.get(1, 1), 4);
}

TEST(SquareMatrixTest, NullArrayException) {
    EXPECT_THROW(SquareMatrix<int> sm(nullptr, 3), std::invalid_argument);
}

TEST(SquareMatrixTest, TraceCalculation) {
    int data[] = {
        10, 1, 2,
        3, 20, 4,
        5, 6, 30
    };
    SquareMatrix<int> sm(data, 3);

    EXPECT_EQ(sm.trace(), 60);
}


TEST(SquareMatrixTest, ScalarMultiplication) {
    int data[] = { 1, 2, 3, 4 };
    SquareMatrix<int> sm(data, 2);


    SquareMatrix<int>* result = sm.mult_scalar(10);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->get_size(), 2);
    EXPECT_EQ(result->get(0, 0), 10);
    EXPECT_EQ(result->get(1, 1), 40);

    delete result;
}


TEST(SquareMatrixTest, Addition) {
    int d1[] = { 1, 0, 0, 1 };
    int d2[] = { 5, 5, 5, 5 };
    SquareMatrix<int> sm1(d1, 2);
    SquareMatrix<int> sm2(d2, 2);

    SquareMatrix<int>* result = sm1.add(&sm2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->get(0, 0), 6);
    EXPECT_EQ(result->get(0, 1), 5);
    EXPECT_EQ(result->get(1, 1), 6);

    delete result;
}


TEST(SquareMatrixTest, CopyConstructor) {
    int data[] = { 7, 8, 9, 10 };
    SquareMatrix<int> sm1(data, 2);
    SquareMatrix<int> sm2(sm1);

    EXPECT_EQ(sm2.get_size(), 2);
    EXPECT_EQ(sm2.get(1, 0), 9);

    sm2.set(1, 0, 99);
    EXPECT_EQ(sm1.get(1, 0), 9);
}