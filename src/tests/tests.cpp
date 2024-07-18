// Copyright 2024 brennelul aka fredgran

#include <gtest/gtest.h>

#include "../library/header/matrix_oop.hpp"

bool is_eq(const Matrix &A, const double B[]) {
  int rows = A.GetRows();
  int cols = A.GetCols();
  double **matrix = A.GetRaw();
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (matrix[i][j] != B[count]) return false;
      count++;
    }
  }
  return true;
}

TEST(constructors, empty) {
  Matrix src1;
  double src2[1];
  EXPECT_EQ(src1.GetRows(), 0);
  EXPECT_EQ(src1.GetCols(), 0);
  EXPECT_TRUE(is_eq(src1, src2));
}

TEST(constructors, rows_and_cols) {
  Matrix src1(3, 3);
  double test[9] = {0};
  EXPECT_EQ(src1.GetRows(), 3);
  EXPECT_EQ(src1.GetCols(), 3);
  EXPECT_TRUE(is_eq(src1, test));
}

TEST(constructors, rows_and_cols_zero) {
  EXPECT_THROW(Matrix src1(0, 0), std::out_of_range);
}

TEST(constructors, copy) {
  double test[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test, 3, 3);
  Matrix src2(src1);
  EXPECT_EQ(src2.GetRows(), 3);
  EXPECT_EQ(src2.GetCols(), 3);
  EXPECT_TRUE(is_eq(src2, test));
}

TEST(constructors, copy_zero) {
  Matrix src1;
  EXPECT_THROW(Matrix src2(src1), std::out_of_range);
}

TEST(constructors, move) {
  double test[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test, 3, 3);
  Matrix src2(std::move(src1));
  EXPECT_EQ(src2.GetRows(), 3);
  EXPECT_EQ(src2.GetCols(), 3);
  EXPECT_TRUE(is_eq(src2, test));
}

TEST(funcs, EqMatrix1) {
  double test[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test, 3, 3);
  Matrix src2(test, 3, 3);
  EXPECT_TRUE(src1.EqMatrix(src2));
}

TEST(funcs, EqMatrix2) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  EXPECT_FALSE(src1.EqMatrix(src2));
}

TEST(funcs, EqMatrix3) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_FALSE(src1.EqMatrix(src2));
}

TEST(funcs, SumMatrix1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1.SumMatrix(src2);
  double result[9] = {5, 5, 5, 5, 5, 5, 5, 5, 5};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, SumMatrix2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1.SumMatrix(src2);
  double result[9] = {0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, SumMatrix3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1.SumMatrix(src2), std::logic_error);
}

TEST(funcs, SubMatrix1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1.SubMatrix(src2);
  double result[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, SubMatrix2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1.SubMatrix(src2);
  double result[9] = {7, 7, 7, 7, 7, 7, 7, 7, 7};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, SubMatrix3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1.SubMatrix(src2), std::logic_error);
}

TEST(funcs, MulNumber1) {
  double test1[9] = {15, 15, 15, 15, 15, 15, 15, 15, 15};
  Matrix src1(test1, 3, 3);
  src1.MulNumber(3);
  double result[9] = {45, 45, 45, 45, 45, 45, 45, 45, 45};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, MulMatrix1) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1.MulMatrix(src2);
  double result[9] = {-36.75, -36.75, -36.75, -36.75, -36.75,
                      -36.75, -36.75, -36.75, -36.75};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, MulMatrix2) {
  double test1[9] = {50, 51, 52, 53, 54, 55, 56, 57, 58};
  double test2[9] = {-50, -51, -52, -53, -54, -55, -56, -57, -58};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);

  src1.MulMatrix(src2);
  double result[9] = {-8115.0, -8268.0, -8421.0, -8592.0, -8754.0,
                      -8916.0, -9069.0, -9240.0, -9411.0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(funcs, MulMatrix3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1.MulMatrix(src2), std::logic_error);
}

TEST(funcs, Transpose1) {
  double test1[9] = {50, 51, 52, 53, 54, 55, 56, 57, 58};
  Matrix src1(test1, 3, 3);
  Matrix src2 = src1.Transpose();
  double result[9] = {50, 53, 56, 51, 54, 57, 52, 55, 58};
  EXPECT_TRUE(is_eq(src2, result));
}

TEST(funcs, CalcComplements1) {
  double test1[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  Matrix src1(test1, 3, 3);
  Matrix src2 = src1.CalcComplements();
  double result[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  EXPECT_TRUE(is_eq(src2, result));
}

TEST(funcs, CalcComplements2) {
  double test1[1] = {1};
  Matrix src1(test1, 1, 1);
  Matrix src2 = src1.CalcComplements();
  double result[1] = {1};
  EXPECT_TRUE(is_eq(src2, result));
}

TEST(funcs, CalcComplements3) {
  double test1[6] = {1, 2, 3, 4, 5, 6};
  Matrix src1(test1, 2, 3);
  EXPECT_THROW(src1.CalcComplements(), std::logic_error);
}

TEST(funcs, Determinant1) {
  double test1[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  Matrix src1(test1, 3, 3);
  double src2 = src1.Determinant();
  double result = -40;
  EXPECT_DOUBLE_EQ(src2, result);
}

TEST(funcs, Determinant2) {
  double test1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix src1(test1, 3, 3);
  double src2 = src1.Determinant();
  double result = 0;
  EXPECT_DOUBLE_EQ(src2, result);
}

TEST(funcs, Determinant3) {
  double test1[6] = {1, 2, 3, 4, 5, 6};
  Matrix src1(test1, 2, 3);
  EXPECT_THROW(src1.Determinant(), std::logic_error);
}

TEST(funcs, InverseMatrix1) {
  double test1[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  Matrix src1(test1, 3, 3);
  Matrix src2 = src1.InverseMatrix();
  double result[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  EXPECT_TRUE(is_eq(src2, result));
}

TEST(funcs, InverseMatrix2) {
  double test1[6] = {1, 2, 3, 4, 5, 6};
  Matrix src1(test1, 2, 3);
  EXPECT_THROW(src1.InverseMatrix(), std::logic_error);
}

TEST(funcs, InverseMatrix3) {
  double test1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix src1(test1, 3, 3);
  EXPECT_THROW(src1.InverseMatrix(), std::logic_error);
}

TEST(operators, index) {
  double test1[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  Matrix src1(test1, 3, 3);
  EXPECT_DOUBLE_EQ(src1(2, 2), -3);
}

TEST(operators, index_zero) {
  double test1[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  Matrix src1(test1, 3, 3);
  EXPECT_THROW(src1(4, 4), std::out_of_range);
}

TEST(operators, plus1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 + src2;
  double result[9] = {5, 5, 5, 5, 5, 5, 5, 5, 5};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, plus2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 + src2;
  double result[9] = {0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, plus3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 + src2, std::logic_error);
}

TEST(operators, minus1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 - src2;
  double result[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, minus2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 - src2;
  double result[9] = {7, 7, 7, 7, 7, 7, 7, 7, 7};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, minus3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 - src2, std::logic_error);
}

TEST(operators, multi_num) {
  double test1[9] = {15, 15, 15, 15, 15, 15, 15, 15, 15};
  Matrix src1(test1, 3, 3);
  src1 = src1 * 3;
  double result[9] = {45, 45, 45, 45, 45, 45, 45, 45, 45};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrix1) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 * src2;
  double result[9] = {-36.75, -36.75, -36.75, -36.75, -36.75,
                      -36.75, -36.75, -36.75, -36.75};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrix2) {
  double test1[9] = {50, 51, 52, 53, 54, 55, 56, 57, 58};
  double test2[9] = {-50, -51, -52, -53, -54, -55, -56, -57, -58};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 = src1 * src2;
  double result[9] = {-8115.0, -8268.0, -8421.0, -8592.0, -8754.0,
                      -8916.0, -9069.0, -9240.0, -9411.0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrix3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 * src2, std::logic_error);
}

TEST(operators, compare1) {
  double test[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test, 3, 3);
  Matrix src2(test, 3, 3);
  EXPECT_TRUE(src1 == src2);
}

TEST(operators, compare2) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  EXPECT_FALSE(src1 == src2);
}

TEST(operators, compare3) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_FALSE(src1 == src2);
}

TEST(operators, pluseq1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 += src2;
  double result[9] = {5, 5, 5, 5, 5, 5, 5, 5, 5};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, pluseq2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 += src2;
  double result[9] = {0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, pluseq3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 += src2, std::logic_error);
}

TEST(operators, minuseq1) {
  double test1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
  double test2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 -= src2;
  double result[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, minuseq2) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 -= src2;
  double result[9] = {7, 7, 7, 7, 7, 7, 7, 7, 7};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, minuseq3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 -= src2, std::logic_error);
}

TEST(operators, multi_numeq) {
  double test1[9] = {15, 15, 15, 15, 15, 15, 15, 15, 15};
  Matrix src1(test1, 3, 3);
  src1 *= 3;
  double result[9] = {45, 45, 45, 45, 45, 45, 45, 45, 45};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrixeq1) {
  double test1[9] = {3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5};
  double test2[9] = {-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 *= src2;
  double result[9] = {-36.75, -36.75, -36.75, -36.75, -36.75,
                      -36.75, -36.75, -36.75, -36.75};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrixeq2) {
  double test1[9] = {50, 51, 52, 53, 54, 55, 56, 57, 58};
  double test2[9] = {-50, -51, -52, -53, -54, -55, -56, -57, -58};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 3, 3);
  src1 *= src2;
  double result[9] = {-8115.0, -8268.0, -8421.0, -8592.0, -8754.0,
                      -8916.0, -9069.0, -9240.0, -9411.0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(operators, multi_matrixeq3) {
  double test1[9] = {0};
  double test2[4] = {0};
  Matrix src1(test1, 3, 3);
  Matrix src2(test2, 2, 2);
  EXPECT_THROW(src1 *= src2, std::logic_error);
}

TEST(accessors, GetRows) {
  Matrix src1(3, 3);
  EXPECT_EQ(src1.GetRows(), 3);
}

TEST(accessors, GetCols) {
  Matrix src1(3, 3);
  EXPECT_EQ(src1.GetCols(), 3);
}

TEST(accessors, SetRows1) {
  double test1[4] = {50, 51, 52, 53};
  Matrix src1(test1, 2, 2);
  src1.SetRows(3);
  double result[6] = {50, 51, 52, 53, 0, 0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(accessors, SetRows2) {
  Matrix src1(2, 2);
  EXPECT_THROW(src1.SetRows(-1), std::out_of_range);
}

TEST(accessors, SetCols1) {
  double test1[4] = {50, 51, 52, 53};
  Matrix src1(test1, 2, 2);
  src1.SetCols(3);
  double result[6] = {50, 51, 0, 52, 53, 0};
  EXPECT_TRUE(is_eq(src1, result));
}

TEST(accessors, SetCols2) {
  Matrix src1(2, 2);
  EXPECT_THROW(src1.SetCols(-1), std::out_of_range);
}

TEST(help, copy_from_default_matrix_zero) {
  double test1[4];
  EXPECT_THROW(Matrix src1(test1, -1, 2), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
