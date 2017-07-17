#ifndef Matrix_H
#define Matrix_H

#include <vector>

template <typename T> class Matrix {
private:
	std::vector<std::vector<T> > mat;
	unsigned rows;
	unsigned cols;

public:
	Matrix(unsigned _rows, unsigned _cols, const T& _initial);
	Matrix(const Matrix<T>& rhs);
	virtual ~Matrix();

	// Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
	Matrix<T>& operator=(const Matrix<T>& rhs);

	// Matrix mathematical operations                                                                                                                                                                                               
	Matrix<T> operator+(const Matrix<T>& rhs);
	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T> operator-(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T> operator*(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);
	Matrix<T> transpose();

	// Matrix/scalar operations                                                                                                                                                                                                     
	Matrix<T> operator+(const T& rhs) const;
	Matrix<T> operator-(const T& rhs);
	Matrix<T> operator*(const T& rhs);
	Matrix<T> operator/(const T& rhs);

	// Matrix/vector operations                                                                                                                                                                                                     
	std::vector<T> operator*(const std::vector<T>& rhs);
	std::vector<T> diag_vec() const;

	// Other Functions
	Matrix<T> crossedMatrix(const unsigned& crossedColumn) const; // crosses out crossedRow and crossedColumn
	T determinant() const;

	// Access the individual elements                                                                                                                                                                                               
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	// Access the row and column sizes                                                                                                                                                                                              
	unsigned get_rows() const;
	unsigned get_cols() const;

	// insertion operator overload 
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
	
	// Friend Functions that allow the user to write expressions in a different order 

	friend Matrix<T> operator+(const T& type, const Matrix& matrix) { return matrix + type; }

	friend Matrix<T> operator-(const T& type, Matrix<T>& matrix) { return matrix - type; };

	friend Matrix<T> operator*(const T& type, Matrix<T>& matrix) { return matrix * type; };

	friend Matrix<T> operator/(const T& type, Matrix<T>& matrix) { return matrix / type; };

};



#include "Matrix.cpp"

#endif