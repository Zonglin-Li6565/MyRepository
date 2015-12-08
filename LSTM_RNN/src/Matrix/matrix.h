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
#include "./Dimension/dimension.h"
#include "./List/linkedlist.h"

namespace std
{

class matrix
{
private:
	struct row_{
		int size_;
		double* array_;
		row_();
		row_(int size);
		double& operator[](int index);
	};
	linkedlist<row_> row_heads;
	int dimension_c_;
	int dimension_r_;
	int arraycols;
public:
	dimension dim_;
	string name_;
	matrix();										//done
	matrix(dimension& d);							//done
	matrix(dimension& d, string name);			    //done
	matrix(matrix& copy);							//done
	void addrows(int index, int num_r);				//done
	void addcols(int index, int num_c);				//done
	void removerows(int index, int num_r);			//done
	void removecols(int index, int num_c);			//done
	matrix* getrow(int index);						//done
	matrix* gotcol(int index);						//done
	dimension* getdimension();						//done
	matrix& operator=(const matrix& newone);		//done
	row_& operator[](int index);					//done
	string tostring();
	virtual ~matrix();								//done
};
//logical operations
bool operator!=(const matrix& first, const matrix& second);
bool operator==(const matrix& first, const matrix& second);
//the element level operations
matrix* operator+(const matrix& first, const matrix& second);					//matrix matrix addition
matrix* operator-(const matrix& first, const matrix& second);					//matrix matrix subtraction
matrix* operator/(const matrix& first, const matrix& second);					//matrix matrix division
matrix* operator/(double first, const matrix& second);							//matrix number division
matrix* operator/(const matrix& first, double second);							//matrix number division
matrix* operator*(double first, const matrix& second);							//matrix number multiplication
matrix* operator*(const matrix& first, double second);							//matrix number multiplication
matrix* operator>>(const matrix& first, const matrix& second);					//matrix matrix multiplication
matrix* log(const matrix& first);												//get a new matrix filled with log of each elements in original matrix
double sum(const matrix& first);												//get the sum of all the elements in the matrix
//the matrix level operations
matrix* operator*(const matrix& first, const matrix& second);					//matrix matrix multiplication
matrix* operator!(const matrix& first);											//transpose
} /* namespace std */

#endif /* MATRIX_H_ */
