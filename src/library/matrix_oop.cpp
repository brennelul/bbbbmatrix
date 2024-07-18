// Copyright 2024 brennelul aka fredgran

#include "header/matrix_oop.hpp"

// void Matrix::Print() const {
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       std::cout << matrix_[i][j] << " ";
//     }
//     std::cout << "\n";
//   }
// }

Matrix::Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("rows or cols less or equal zero");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{0.};
  }
}

Matrix::Matrix(const double matrix[], const int rows, const int cols)
    : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("rows or cols less or equal zero");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  int count = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix[count];
      count++;
    }
  }
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  if (other.rows_ <= 0 || other.cols_ <= 0) {
    throw std::out_of_range("rows or cols less or equal zero");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

bool Matrix::EqMatrix(const Matrix &other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) return false;
    }
  }

  return true;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("size is not the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("size is not the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "cols of the first matrix not equal to the rows of the second");
  }
  Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

Matrix Matrix::Transpose() noexcept {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("matrix is not square");
  }
  Matrix result(cols_, rows_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    double min = 0.0, sign = 0.0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        min = this->Minor(i, j);
        sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
        result.matrix_[i][j] = sign * min;
      }
    }
  }
  return result;
}

double Matrix::Minor(int row, int col) {
  Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        minor.matrix_[i - (i < row ? 0 : 1)][j - (j < col ? 0 : 1)] =
            matrix_[i][j];
      }
    }
  }
  double result = minor.Determinant();
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("matrix is not square");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  Matrix det(rows_ - 1, cols_ - 1);
  double result = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 1; j < rows_; j++) {
      for (int k = 0; k < cols_; k++) {
        if (k != i) det.matrix_[j - 1][k - (k < i ? 0 : 1)] = matrix_[j][k];
      }
    }
    double sign = i % 2 == 0 ? 1.0 : -1.0;
    double cofactor = det.Determinant();
    result += sign * matrix_[0][i] * cofactor;
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("not square");
  }

  double determinant = this->Determinant();

  if (std::fabs(determinant) < 1e-7) {
    throw std::logic_error("determinant is 0");
  }

  Matrix result = this->CalcComplements().Transpose();
  result.MulNumber(1 / determinant);

  return result;
}

double &Matrix::operator()(int i, int j) const {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0) {
    throw std::out_of_range("incorrect value");
  }
  return matrix_[i][j];
}

Matrix Matrix::operator+(const Matrix &a) const {
  Matrix sum = *this;
  sum += a;
  return sum;
}

Matrix Matrix::operator-(const Matrix &a) const {
  Matrix sum = *this;
  sum -= a;
  return sum;
}

Matrix Matrix::operator*(const Matrix &a) const {
  Matrix sum = *this;
  sum *= a;
  return sum;
}

Matrix Matrix::operator*(const double &a) const {
  Matrix sum = *this;
  sum *= a;
  return sum;
}

bool Matrix::operator==(const Matrix &a) const { return this->EqMatrix(a); }

Matrix &Matrix::operator=(const Matrix &a) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = a.rows_;
  cols_ = a.cols_;
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = a.matrix_[i][j];
    }
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) {
  if (other.rows_ <= 0 || other.cols_ <= 0) {
    throw std::out_of_range("rows or cols less or equal zero");
  }
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &a) {
  this->SumMatrix(a);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &a) {
  this->SubMatrix(a);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &a) {
  this->MulMatrix(a);
  return *this;
}

Matrix &Matrix::operator*=(const double a) {
  this->MulNumber(a);
  return *this;
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

double **Matrix::GetRaw() const { return matrix_; }

void Matrix::SetRows(int rows) {
  if (rows <= 0) std::out_of_range("error");
  if (rows != rows_) {
    Matrix temp(rows, cols_);
    for (int i = 0; i < std::min(rows, rows_); i++) {
      for (int j = 0; j < cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(temp);
  }
}

void Matrix::SetCols(int cols) {
  if (cols <= 0) std::out_of_range("error");
  if (cols != cols_) {
    Matrix temp(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < std::min(cols, cols_); j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(temp);
  }
}
