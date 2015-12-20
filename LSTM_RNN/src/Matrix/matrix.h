/*
 * matrix.h
 *
 *  Created on: Nov 25, 2015
 *      Author: zonglin
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "./Dimension/dimension.h"
#include "./List/linkedlist.cpp"

class matrix
{
private:
	struct row_
	{
		int size_;
		double* array_;
		row_();
		row_(int size);
		double& operator[](int index);
	};
	linkedlist<row_> row_heads;
	int arraycols;
public:
	int dimension_c_;
	int dimension_r_;
	dimension dim_;
	std::string name_;
	matrix();										//done
	matrix(int rows, int cols);						//done
	matrix(dimension& d);							//done
	matrix(dimension& d, std::string name);			//done
	matrix(matrix& copy);							//done
	void addrows(int index, int num_r);				//done
	void addcols(int index, int num_c);				//done
	void removerows(int index, int num_r);			//done
	void removecols(int index, int num_c);			//done
	matrix& getrow(int index);						//done
	matrix& getcol(int index);						//done
	dimension* getdimension();						//done
	matrix& operator=(const matrix& newone);		//done
	row_& operator[](int index);					//done
	std::string tostring();
	virtual ~matrix();								//done
};

namespace std {

//logical operations
bool operator!=(matrix& first, matrix& second);
bool operator==(matrix& first, matrix& second);
//the element level operations
matrix& operator+(matrix& first, matrix& second);		//matrix matrix addition
matrix& operator-(matrix& first, matrix& second);	//matrix matrix subtraction
matrix& operator/(matrix& first, matrix& second);		//matrix matrix division
matrix& operator/(double first, matrix& second);		//matrix number division
matrix& operator/(matrix& first, double second);		//matrix number division
matrix& operator*(double first, matrix& second);//matrix number multiplication
matrix& operator*(matrix& first, double second);//matrix number multiplication
matrix& operator>>(matrix& first, matrix& second);//matrix matrix multiplication
matrix& log(matrix& first);	//get a new matrix filled with log of each elements in original matrix
matrix& tanh(matrix& first);
double sum(matrix& first);		//get the sum of all the elements in the matrix
//the matrix level operations
matrix& operator*(matrix& first, matrix& second);//matrix matrix multiplication
matrix& operator!(matrix& first);
matrix& verticalmerge(matrix& first, matrix& second);
matrix& horizontalmerge(matrix& first, matrix& second);
}


#endif /* MATRIX_H_ */
