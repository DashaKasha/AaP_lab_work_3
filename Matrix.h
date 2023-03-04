#pragma once
#include <iostream>
#include <initializer_list>
#include <cassert>
using namespace std;




//static_assert(std::is_same<initializer_list<T>, T>, false);
//std::is_same<T, int>::value || std::is_same<T, double>::value;
template <typename T = double>//, typename T2>
class Matrix
{
private:
	int cols, rows;						// sizes of matrix
	T* data;							// pointer on array of elements

public:

	// default constructor
	Matrix<T>()							
	{
		cols = rows = 0;
		data = nullptr; 
	}

	// constructor
	Matrix<T>(int r, int c = 1)			
	{
		rows = r;
		cols = c;
		data = new T[r * c];
	}

	// constructor for Matrix<T> m1 = {{...}, ... , {...}}
	Matrix<T>(initializer_list<initializer_list<T>> matrix)
	{
		rows = matrix.size();
		cols = (matrix.begin())->size();
		data = new T[rows * cols];
		int i = 0;
		for (auto row : matrix) {
			for (auto element : row) {
				data[i] = element;
				i++;
 			}
		}
	}

	Matrix<T>(initializer_list<T> matrix)
	{
		rows = matrix.size();
		cols = 1;
		data = new T[rows*cols];
		int i = 0;
		for (auto row : matrix) {
			data[i] = row;
			i++;
		}
	}
	
	// copy constructor
	Matrix<T>(const Matrix& matrix)		
	{
		rows = matrix.rows;
		cols = matrix.cols;
		data = new T[rows * cols];
		for (int i = 0; i < rows*cols; i++)
		{
			data[i] = matrix.data[i];
		}
	}

	// move constructor
	Matrix<T>(Matrix&& other)			
	{
		rows = other.rows;
		cols = other.cols;
		data = other.data;
		other.data = nullptr;
		other.rows = other.cols = 0;
	}

	// operator = 
	Matrix<T> operator = (const Matrix<T> matrix) {		
		if (rows * cols < matrix.rows * matrix.cols) {
			data = new T[matrix.rows * matrix.cols];
		}
		rows = matrix.rows;
		cols = matrix.cols;
		for (int i = 0; i < rows * cols; i++)
		{
			data[i] = matrix.data[i];
		}
		return matrix;

	}

	// input (operator >>)
	friend istream& operator >>(istream& in, Matrix<T> &matrix)  
	{
		for (int i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.cols; j++)
			{
				in >> matrix.data[i * matrix.cols + j];
			}
		}
		return in;
	}

	// output (operator <<)
	friend ostream& operator <<(ostream& out, Matrix<T> matrix)   
	{
		for (int i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.cols; j++)
			{
				out << matrix.data[i * matrix.cols + j]<<'\t';
			}
			out << endl;
		}
		out << endl;
		return out;
	}

	// operator ()  
	T &operator () (const int &r, const int&c) {	

		if (r > rows || c > cols)
		{
			throw invalid_argument("the indexes are too big\n");

		}
		return data[r * cols + c];
	}


	// matrix addition (operator +)
	Matrix<T> operator + ( const Matrix<T> &summand)  
	{
		if (rows != summand.rows || cols != summand.cols)
		{
			throw invalid_argument ("the sizes of the matrices do not match.\n");
		}
		Matrix <T> summ(rows, cols); 
		for (int i = 0; i < rows*cols; i++)
		{
			summ.data[i] = data[i] + summand.data[i];
		}
		return summ;
	}
	

	// matrix subtraction (operator -)
	Matrix<T> operator - (const Matrix<T> &a)		 
	{
		if (rows != a.rows || cols != a.cols)
		{
			throw invalid_argument ("the sizes of the matrices do not match.\n");
			
		}
		Matrix <T> minus(rows, cols);
		for (int i = 0; i < rows * cols; i++)
		{
			minus.data[i] = data[i] - a.data[i];
		}
		return minus;
	}

	// multiplying matrix by a number (operator *)
	Matrix<T> operator *(const T &n)					
	{
		Matrix <T> m(rows, cols);
		for (int i = 0; i < rows * cols; i++) 
		{
			m.data[i] = data[i] * n;
		}
		return m;
	}

	// matrix multiplication (operator *)
	Matrix <T> operator * (const Matrix<T> &b)		
	{
		if (cols != b.rows) {
			throw invalid_argument( "The number of columns of the left matrix does not equal to the number of rows of the right matrix.\n");
		}
		Matrix<T> c(rows, b.cols);					// product matrix
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < b.cols; j++)
			{
				c.data[i * b.cols + j] = 0;
				for (int k = 0; k < cols; k++)
				{
					c.data[i * b.cols + j] += data[i * cols + k] * b.data[k * b.cols + j];
				}
			}
		}
		return c;
	}

	// matrix addition (operator +=)
	Matrix <T> operator += (const Matrix<T> &summand)  
	{
		if (rows != summand.rows || cols != summand.cols)
		{
			throw invalid_argument ("the sizes of the matrices do not match.\n");
		}
		
		for (int i = 0; i < rows * cols; i++)
		{
			data[i] += summand.data[i];
		}

		return *this;
	}

	// matrix subtraction (operator -=)
	Matrix <T> operator -= (const Matrix<T> &a)		
	{
		if (rows != a.rows || cols != a.cols)
		{
			throw invalid_argument("the sizes of the matrices do not match.\n");
		}
		for (int i = 0; i < rows * cols; i++)
		{
			data[i] -= a.data[i];
		}
		return *this;
	}

	// multiplying matrix by a number (operator *=)
	Matrix <T> operator *= (const T &n)				
	{
		for (int i = 0; i < rows * cols; i++)
		{
			data[i] = data[i] * n;
		}
		return *this;
	}
	 

	

	~Matrix<T>()
	{
		delete[] data;
	}
};
