#ifndef Matrix_cpp
#define Matrix_cpp

#include "Matrix.h"
// Parameter Constructor                                                                                                                                                      
template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
	mat.resize(_rows);
	for (unsigned i = 0; i<mat.size(); i++) {
		mat[i].resize(_cols, _initial);
	}
	rows = _rows;
	cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
	mat = rhs.mat;
	rows = rhs.get_rows();
	cols = rhs.get_cols();
}

// (Virtual) Destructor                                                                                                                                                       
template<typename T>
Matrix<T>::~Matrix() {}

// Assignment Operator                                                                                                                                                        
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
	if (&rhs == this)
		return *this;

	unsigned new_rows = rhs.get_rows();
	unsigned new_cols = rhs.get_cols();

	mat.resize(new_rows);
	for (unsigned i = 0; i<mat.size(); i++) {
		mat[i].resize(new_cols);
	}

	for (unsigned i = 0; i<new_rows; i++) {
		for (unsigned j = 0; j<new_cols; j++) {
			mat[i][j] = rhs(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;

	return *this;
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->mat[i][j] + rhs(i, j);
		}
	}

	return result;
}

// Cumulative addition of this matrix and another                                                                                                                             
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
	unsigned rows = rhs.get_rows();
	unsigned cols = rhs.get_cols();

	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			this->mat[i][j] += rhs(i, j);
		}
	}

	return *this;
}

// Subtraction of this matrix and another                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
	unsigned rows = rhs.get_rows();
	unsigned cols = rhs.get_cols();
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->mat[i][j] - rhs(i, j);
		}
	}

	return result;
}

// Cumulative subtraction of this matrix and another                                                                                                                          
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
	unsigned rows = rhs.get_rows();
	unsigned cols = rhs.get_cols();

	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			this->mat[i][j] -= rhs(i, j);
		}
	}

	return *this;
}

// Matrix Multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
	Matrix<T> result(this->get_rows(), rhs.get_cols(), 0.0); 
	int dotProduct;
	for (unsigned n = 0; n < this->get_rows(); ++n) // rows of first matrix
	{
		for (unsigned p = 0; p < rhs.get_cols(); ++p) // columns of second matrix 
		{
			for (unsigned m = 0; m < this->get_cols(); ++m)
			{
				result(n, p) += (*this)(n,m) * rhs(m, p);
			}
		}
	}
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*= (const Matrix<T>& rhs)
{
	Matrix result = (*this) * rhs;
	(*this) = result;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix Trans(cols, rows, 0.0); // transpose has cols rows and rows cols 
	for (unsigned i = 0; i < Trans.get_rows(); ++i)
	{
		for (unsigned j = 0; j < Trans.get_cols(); ++j)
		{
			Trans(i, j) = (*this)(j, i);
		}
	}
	return Trans; 
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T& rhs) const
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols; ++j)
		{
			result(i,j) = (*this)(i, j) + rhs;
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs)
{
	Matrix result(rows, cols, 0.0);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			result(i, j) = (*this)(i, j) - rhs;
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols; ++j)
		{
			result(i, j) = (*this)(i, j) * rhs;
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols; ++j)
		{
			result(i, j) = (*this)(i, j) / rhs;
		}
	}
	return result;
}

template <typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& rhs)
{
	std::vector<T> result(rows, 0.0);
	if (cols == rhs.size())
	{
		for (unsigned n = 0; n < rows; ++n)
		{
			for (unsigned m = 0; m < cols; ++m)
			{
				result[n] += (*this)(n, m) * rhs[m];
			}
		}
	}
	else
	{
		cout << "size mismatch!" << endl;
	}
	return result;
}

template <typename T>
std::vector<T> Matrix<T>::diag_vec() const
{
	std::vector<T> result(rows, 0.0);
	if (rows == cols)
	{
		for (unsigned n = 0; n < rows; ++n)
		{
			result[n] = (*this)(n,n);
		}
	}
	return result; 
}

template <typename T>
Matrix<T> Matrix<T>::crossedMatrix(const unsigned& crossedColumn) const // used for determinant calculation 
{ // this function produces a new matrix used with a user specified column crossed and the first row crossed 
	Matrix result(rows - 1, cols - 1, 0.0);
	for (int n = 1; n < rows; ++n) // always cross out the first row for determinant calculation 
	{
		for (int m = 0; m < crossedColumn; ++m) // transition over crossedMatrix 
		{
			result(n-1, m) = (*this)(n, m);
		}
		for (int m = crossedColumn; m < cols - 1; ++m) // moving over 
		{
			result(n-1, m) = (*this)(n, m + 1);
		}
	}
	return result; 
}

template<typename T>
T Matrix<T>::determinant() const // only works for square matrices
{
	T result = 0;
	if (rows == 1)
	{
		result = (*this)(0, 0);
	}
	else
	{
		for (unsigned m = 0; m < cols; ++m)
		{
			result += pow((-1), m) * (*this)(0, m) * ((*this).crossedMatrix(m)).determinant();
		}
	}
	return result;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
	return this->mat[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
	return this->mat[row][col];
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned Matrix<T>::get_rows() const 
{
	return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned Matrix<T>::get_cols() const 
{
	return this->cols;
} 


template<typename T>
std::ostream& operator<< (std::ostream& os, const Matrix<T>& matrix)
{
	for (int i = 0; i < matrix.get_rows(); i++) 
	{
		for (int j = 0; j < matrix.get_cols(); j++) 
		{
			std::cout << matrix(i, j) << ", ";
		}
		std::cout << std::endl;
	}
	return os; 
}


#endif
