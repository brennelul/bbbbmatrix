// Copyright 2024 brennelul aka fredgran

#ifndef SRC_LIBRARY_HEADER_MATRIX_OOP_HPP_
#define SRC_LIBRARY_HEADER_MATRIX_OOP_HPP_
#include <memory.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

class Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  double Minor(int row, int col);

 public:
  Matrix() noexcept;
  Matrix(int rows, int cols);
  Matrix(const double matrix[], const int rows,
         const int cols);  // for testing purposes
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  ~Matrix() noexcept;
  // operators
  double &operator()(int i, int j) const;
  Matrix operator+(const Matrix &a) const;
  Matrix operator-(const Matrix &a) const;
  Matrix operator*(const Matrix &a) const;
  Matrix operator*(const double &a) const;
  bool operator==(const Matrix &a) const;
  Matrix &operator=(const Matrix &a);
  Matrix &operator+=(const Matrix &a);
  Matrix &operator-=(const Matrix &a);
  Matrix &operator*=(const Matrix &a);
  Matrix &operator*=(const double a);
  // funcs
  bool EqMatrix(const Matrix &other) const noexcept;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const Matrix &other);
  Matrix Transpose() noexcept;
  Matrix CalcComplements();
  Matrix InverseMatrix();
  double Determinant();
  // accessors and mutators
  int GetRows() const;
  int GetCols() const;
  double **GetRaw() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void Print() const;
};

#endif  // SRC_LIBRARY_HEADER_MATRIX_OOP_HPP_
