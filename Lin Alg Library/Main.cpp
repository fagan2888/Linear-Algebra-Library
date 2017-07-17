#include "Matrix.h"

#include <iostream>
#include <vector>

using namespace std;
int main()
{
	Matrix<double> mat1(3, 4, 2.0);
	Matrix<double> mat2(4, 3, 3.0);

	mat2(1, 2) = 1;
	mat2(0, 1) = 2;
	mat2(0, 1) = 4;
	Matrix<double> mat3 = mat1 * mat2;

	cout << mat3 << endl;

	cout << "\n";

	cout << "mat2 = \n";
	cout << mat2 << endl;

	cout << "\n";

	Matrix<double> mat5 = mat2.transpose();
	cout << mat5 << endl;

	Matrix<double> matrix = mat2 + 2;

	cout << "\n" << endl;
	cout << matrix << endl;

	std::vector<double> vec(3, 2.0);

    std:vector<double> result = mat2 * vec;

	for (std::vector<double>::iterator it = result.begin(); it != result.end(); ++it)
	{
		cout << *it << endl;
	}

	Matrix<double> ryan(5, 5, 2.2);
	ryan(2, 2) = 13; 
	std::vector<double> vect = ryan.diag_vec();

	for (std::vector<double>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << "\n";
	mat2(2, 0) = 7;
	mat2(3, 2) = 1;
	cout << mat2 << endl;

	Matrix<double> matr(5, 5, 12);
	matr(0, 0) = 2; matr(0, 1) = 234; matr(0, 2) = 98; matr(1, 2) = 7; matr(2, 0) = 4; matr(3, 2) = 6; matr(4, 4) = -1; 
	cout << matr << endl;


	cout << matr.determinant() << endl;

	Matrix<double> matr2(5, 5, -6);

	cout << matr2 << endl;

	Matrix<double> matr3 = 2 * matr2;

	cout << matr3 << endl;

	




	return 0;
}