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
#include <vector>
#include <algorithm>
#include <cstdio>
#include "./Dimension/dimension.h"

class matrix
{
private:
  	std::vector< double* >* _cols_;
  	size_t dimension_c_;
  	size_t dimension_r_;
  	void initialize(size_t rows, size_t cols);
  	void free();
public:
	matrix();
	matrix(size_t rows, size_t cols);
	matrix(dimension& d);
	matrix(const matrix& copy);
	~matrix();
	double& access(size_t row, size_t col) const;
	void addrows(size_t index, size_t num_r);
	void addcols(size_t index, size_t num_c, double value);
	void removerows(size_t index, size_t num_r);
	void removecols(size_t index, size_t num_c);
	/**
	 * The returned matrix is independent to the original one.
	 */
	matrix getrow(size_t index) const;
	/**
	 * The returned matrix is independent to the original one.
	 */
	matrix getcol(size_t index) const;
	dimension getdimension() const;
	double& operator()(size_t row, size_t col);
	/**
	 * The objects on both sides are independent to each other;
	 */
	matrix& operator=(const matrix& newone);
	/**
	 * Get the number of rows
	 */
	size_t getrowsize() const;
	/**
	 * Get the number of columns
	 */
	size_t getcolumnsize() const;
	/**
	 * To string
	 */
  std::string tostring();
	/////////////////////////logical operations/////////////////////////
  /**
   * Equals
   */
  bool operator==(const matrix& right) const;
	/**
	 * Not equals
	 */
	bool operator!=(const matrix& right) const;
	////////////////////the element level operations////////////////////
	/**
	 * Matrix matrix addition
	 */
	matrix operator+(const matrix& right) const;
	/**
	 * Matrix matrix subtraction
	 */
	matrix operator-(const matrix& right) const;
	/**
	 * Matrix matrix division
	 */
	matrix operator/(const matrix& right) const;
	/**
	 * Matrix matrix multiplication
	 */
	matrix operator>>(const matrix& right) const;
	/////////////////////the matrix level operations////////////////////
	/**
	 * Matrix matrix multiplication
	 */
	matrix operator*(const matrix& right) const;
	/**
	 * Transpose
	 */
	matrix operator!() const;
	/**
	 * Shuffle the elements in the matrix with value in [-1, 1]
	 */
	void randomize();
};

namespace std
{
////////////////////the element level operations////////////////////
/**
 * Number matrix division
 */
matrix operator/(double left, const matrix& right);
/**
 * Matrix number division
 */
matrix operator/(const matrix& left, double right);
/**
 * Matrix number multiplication
 */
matrix operator*(double left, const matrix& right);
/**
 * Number matrix multiplication
 */
matrix operator*(const matrix& left, double right);
/**
 * Perform the element calculation with function specified as _function on
 * the elements of matrix para
 */
matrix elementcalculation(const matrix& para, double(*_function)(double));
/**
 * A new independent matrix which is the log of the original one
 */
matrix logmatrix(const matrix& para);
/**
 * A new independent matrix which is the tanh of the original one
 */
matrix tanhmatrix(const matrix& para);
/**
 * Get the sum of all elements in the matrix
 */
double sum(const matrix& para);
/////////////////////the matrix level operations////////////////////
//matrix& verticalmerge(matrix& first, matrix& second);
//matrix& horizontalmerge(matrix& first, matrix& second);
}

#endif /* MATRIX_H_ */
