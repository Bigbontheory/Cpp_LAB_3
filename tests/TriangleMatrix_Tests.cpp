#include <gtest/gtest.h>
#include "TriangleMatrix.hpp"

TEST(TriangleMatrixTest, Constructors) {
    TriangleMatrix<int> m1(3, TriangleMatrix<int>::TriangleType::Lower);
    EXPECT_EQ(m1.get_size(), 3);
    EXPECT_EQ(m1.get_type(), TriangleMatrix<int>::TriangleType::Lower);

    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TriangleMatrix<int> m2(arr, 3, TriangleMatrix<int>::TriangleType::Lower);
    EXPECT_EQ(m2.get(0, 0), 1);
    EXPECT_EQ(m2.get(1, 1), 3);
    EXPECT_EQ(m2.get(0, 1), 0);

    TriangleMatrix<int> m3(arr, 3, TriangleMatrix<int>::TriangleType::Upper);
    EXPECT_EQ(m3.get(0, 0), 1);
    EXPECT_EQ(m3.get(0, 1), 2);
    EXPECT_EQ(m3.get(1, 1), 4);
    EXPECT_EQ(m3.get(1, 0), 0);
}

TEST(TriangleMatrixTest, SetMethod) {
    TriangleMatrix<int> m_low(3, TriangleMatrix<int>::TriangleType::Lower);
    m_low.set(2, 0, 10);
    EXPECT_EQ(m_low.get(2, 0), 10);
    EXPECT_THROW(m_low.set(0, 2, 5), std::invalid_argument);

    TriangleMatrix<int> m_up(3, TriangleMatrix<int>::TriangleType::Upper);
    m_up.set(0, 2, 20);
    EXPECT_EQ(m_up.get(0, 2), 20);
    EXPECT_THROW(m_up.set(2, 0, 5), std::invalid_argument);
}

TEST(TriangleMatrixTest, MathOperations) {
    double arr[] = { 3.0, 4.0, 0.0 };
    TriangleMatrix<double> m(arr, 2, TriangleMatrix<double>::TriangleType::Lower);

    EXPECT_NEAR(m.norm(), 5.0, 1e-9);

    auto* scaled = m.mult_scalar(3.0);
    EXPECT_DOUBLE_EQ(scaled->get(0, 0), 9.0);
    EXPECT_DOUBLE_EQ(scaled->get(1, 0), 12.0);
    delete scaled;
}

TEST(TriangleMatrixTest, Addition) {
    int arr[] = { 1, 2, 3 };
    TriangleMatrix<int> tri(arr, 2, TriangleMatrix<int>::TriangleType::Lower);

    SquareMatrix<int> sq(2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) sq.set(i, j, 10);

    auto* result = tri.add(&sq);
    EXPECT_EQ(result->get(0, 0), 11);
    EXPECT_EQ(result->get(0, 1), 10);
    EXPECT_EQ(result->get(1, 1), 13);
    delete result;
}

TEST(TriangleMatrixTest, BoundsAndExceptions) {
    EXPECT_THROW(TriangleMatrix<int>(-1, TriangleMatrix<int>::TriangleType::Lower), std::invalid_argument);

    TriangleMatrix<int> m(2, TriangleMatrix<int>::TriangleType::Upper);
    EXPECT_THROW(m.get(2, 2), std::out_of_range);
    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
}