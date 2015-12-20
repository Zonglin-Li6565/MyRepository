/*
 * matrix.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: zonglin
 */

#include "matrix.h"
#include <algorithm>
#include <stdexcept>
#define EXTRA 5

matrix::row_::row_()
{
	array_ = new double[5];
	size_ = 5;
}

matrix::row_::row_(int size)
{
	array_ = new double[size];
	size_ = size;
}

double& matrix::row_::operator[](int index)
{
	if (index > size_)
		throw std::runtime_error("index out of bound");
	return array_[index];
}

matrix::matrix()
{
	dimension_c_ = 1;
	dimension_r_ = 1;
	arraycols = dimension_c_ + EXTRA;
	for (int i = 0; i < dimension_r_; i++)
	{
		row_heads.add(*(new row_(arraycols)));
	}
}

matrix::matrix(int rows, int cols)
{
	dimension_r_ = rows;
	dimension_c_ = cols;
	arraycols = dimension_c_ + EXTRA;
	for (int i = 0; i < dimension_r_; i++)
	{
		row_heads.add(*(new row_(arraycols)));
	}
}

matrix::matrix(dimension& d)
{
	dimension_c_ = d.dimension_c_;
	dimension_r_ = d.diemnsion_r_;
	arraycols = dimension_c_ + EXTRA;
	for (int i = 0; i < dimension_r_; i++)
	{
		row_heads.add(*(new row_(arraycols)));
	}
}

matrix::matrix(dimension& d, std::string name)
{
	name_ = name;
	dimension_c_ = d.dimension_c_;
	dimension_r_ = d.diemnsion_r_;
	arraycols = dimension_c_ + EXTRA;
	for (int i = 0; i < dimension_r_; i++)
	{
		row_heads.add(*(new row_(arraycols)));
	}
}

matrix::matrix(matrix& copy)
{
	dimension* dim = copy.getdimension();
	dimension_c_ = dim->dimension_c_;
	dimension_r_ = dim->diemnsion_r_;
	arraycols = dimension_c_ + EXTRA;
	for (int i = 0; i < dimension_r_; i++)
	{
		row_heads.add(*(new row_(arraycols)));
		for (int j = 0; j < dimension_c_; j++)
		{
			row_heads[i][j] = copy[i][j];
		}
	}
}

dimension* matrix::getdimension()
{
	return new dimension(dimension_r_, dimension_c_);
}

matrix::~matrix()
{
	delete &row_heads;
	delete &dimension_c_;
	delete &dimension_r_;
	delete &arraycols;
}

void matrix::addrows(int index, int num_r)
{
	if (index < 0 || index > dimension_r_)
		throw std::runtime_error("invalid index number to add rows");
	dimension_r_ += num_r;
	for (int i = 0; i < num_r; i++)
		row_heads.insert(new row_(arraycols), index);
}

void matrix::addcols(int index, int num_c)
{
	if (index < 0 || index > dimension_c_)
		throw std::runtime_error("invalid index number to add columns.");
	dimension_c_ += num_c;
	if (dimension_c_ > arraycols)
	{
		arraycols = dimension_c_ + num_c + EXTRA;
		for (int i = 0; i < row_heads.size_; i++)
		{
			row_& newrow = *new row_(arraycols);
			row_& currentrow = row_heads[i];
			for (int j = 0; j < index; j++)
				newrow[j] = currentrow[j];
			for (int j = index + num_c; j < dimension_c_; j++)
				newrow[j] = currentrow[j - num_c];
			row_heads[i] = newrow;
		}
	}
	else
	{
		for(int i = 0; i < dimension_r_; i++)
		{
			row_& row = row_heads[i];
			for(int j = dimension_c_ - 1; j >= index + num_c; j --)
				row[j] = row[j - num_c];
			for(int j = 0; j < num_c; j++)
				row[j + index] = 0;
		}
	}
}

void matrix::removerows(int index, int num_r)
{
	if (index < 0 || index > dimension_r_)
		throw std::runtime_error("invalid index number to add rows");
	dimension_r_ -= num_r;
	for (int i = 0; i < num_r; i++)
		row_heads.remove(index);
}

void matrix::removecols(int index, int num_c)
{
	if (index < 0 || index > dimension_c_)
		throw std::runtime_error("invalid index number to add columns.");
	dimension_c_ -= num_c;
	if (dimension_c_ < arraycols - 2 * EXTRA)
	{
		arraycols = dimension_c_ + EXTRA;
		for (int i = 0; i < row_heads.size_; i++)
		{
			row_& newrow = *new row_(arraycols);
			row_& currentrow = row_heads[i];
			for (int j = 0; j < index; j++)
				newrow[j] = currentrow[j];
			for (int j = index; j < dimension_c_; j++)
				newrow[j] = currentrow[j + num_c];
			row_heads[i] = newrow;
		}
	}
	else
	{
		for(int i = 0; i < dimension_r_; i++)
		{
			row_& row = row_heads[i];
			for(int j = dimension_c_ + num_c; j > index + num_c; j--)
				row[j - num_c] = row[j];
		}
	}
}

matrix& matrix::getrow(int index)
{
	dimension newdim(1, dimension_c_);
	matrix& temp = *new matrix(newdim);
	for (int i = 0; i < dimension_c_; i++)
		temp[0][i] = row_heads[index][i];
	return temp;
}

matrix& matrix::getcol(int index)
{
	dimension newdim(dimension_r_, 1);
	matrix& temp = *new matrix(newdim);
	for (int i = 0; i < dimension_r_; i++)
		temp[i][0] = row_heads[i][index];
	return temp;
}

matrix::row_& matrix::operator[](int index)
{
	if(index < 0 || index >= dimension_r_)
		throw std::runtime_error("row number out of bound");
	return row_heads[index];
}

matrix& matrix::operator=(const matrix& newone)
{
	if (this == &newone)
		return *this;
	this->row_heads = newone.row_heads;
	this->dimension_c_ = newone.dimension_c_;
	this->dimension_r_ = newone.dimension_r_;
	this->arraycols = newone.arraycols;
	this->dim_ = newone.dim_;
	this->name_ = newone.name_;
	return *this;
}

std::string matrix::tostring()
{
	std::ostringstream s;
	double fac = pow(10, 3);
	for (int i = 0; i < dimension_r_; i++)
	{
		for (int j = 0; j < dimension_c_; j++)
		{
			s << round(row_heads[i][j] * fac) / fac << '\t';
		}
		s << "\n";
	}
	return s.str();
}

namespace std {

bool operator==(matrix& first, matrix& second)
{
	if (first.dimension_c_ != second.dimension_c_
			|| first.dimension_r_ != second.dimension_r_)
		return false;
	for (int i = 0; i < first.dimension_r_; i++)
	{
		for (int j = 0; j < first.dimension_c_; j++)
		{
			if (first[i][j] != second[i][j])
				return false;
		}
	}
	return true;
}

bool operator!=(matrix& first, matrix& second)
{
	return !(first == second);
}

matrix& operator+(matrix& first, matrix& second)
{
	if (first.dimension_c_ != second.dimension_c_
			|| first.dimension_r_ != second.dimension_r_)
		throw runtime_error(
				"trying to add two matrix with different dimension");
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = first[i][j] + second[i][j];
	return newmatrix;
}

matrix& operator-(matrix& first, matrix& second)
{
	if (first.dimension_c_ != second.dimension_c_
			|| first.dimension_r_ != second.dimension_r_)
		throw runtime_error(
				"trying to add two matrix with different dimension");
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = first[i][j] - second[i][j];
	return newmatrix;
}

matrix& operator/(matrix& first, matrix& second)
{
	if (first.dimension_c_ != second.dimension_c_
			|| first.dimension_r_ != second.dimension_r_)
		throw runtime_error(
				"trying to add two matrix with different dimension");
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = first[i][j] / second[i][j];
	return newmatrix;
}

matrix& operator/(matrix& first, double second)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = first[i][j] / second;
	return newmatrix;
}

matrix& operator/(double first, matrix& second)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(second.dimension_r_, second.dimension_c_)));
	for (int i = 0; i < second.dimension_r_; i++)
		for (int j = 0; j < second.dimension_c_; j++)
			newmatrix[i][j] = first / second[i][j];
	return newmatrix;
}

matrix& operator*(double first, matrix& second)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(second.dimension_r_, second.dimension_c_)));
	for (int i = 0; i < second.dimension_r_; i++)
		for (int j = 0; j < second.dimension_c_; j++)
			newmatrix[i][j] = first * second[i][j];
	return newmatrix;
}

matrix& operator*(matrix& first, double second)
{
	return second * first;
}

matrix& operator>>(matrix& first, matrix& second)
{
	if (first.dimension_c_ != second.dimension_c_
			|| first.dimension_r_ != second.dimension_r_)
		throw runtime_error(
				"trying to add two matrix with different dimension");
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = first[i][j] * second[i][j];
	return newmatrix;
}

matrix& log(matrix& first)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = log(first[i][j]);
	return newmatrix;
}

matrix& tanh(matrix& first)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, first.dimension_c_)));
	for (int i = 0; i < first.dimension_r_; i++)
		for (int j = 0; j < first.dimension_c_; j++)
			newmatrix[i][j] = tanh(first[i][j]);
	return newmatrix;
}

double sum(matrix& first)
{
	double sum = 0.0;
	for(int i = 0; i < first.dimension_r_; i++)
		for(int j = 0; j < first.dimension_c_; j++)
			sum += first[i][j];
	return sum;
}

matrix& operator*(matrix& first, matrix& second)
{
	if(first.dimension_c_ != second.dimension_r_)
		throw runtime_error("incorrect dimension of two matrix");
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_r_, second.dimension_c_)));
	for(int i = 0; i < newmatrix.dimension_r_; i++)
	{
		for(int j = 0; j < newmatrix.dimension_c_; j++)
		{
			double sum = 0.0;
			for(int t = 0; t < first.dimension_c_; t++)
				sum += first[i][t] * second[t][j];
			newmatrix[i][j] = sum;
		}
	}
	return newmatrix;
}

matrix& operator!(matrix& first)
{
	matrix& newmatrix = *new matrix(
			*(new dimension(first.dimension_c_, first.dimension_r_)));
	for(int i = 0; i < first.dimension_c_; i++)
		for(int j = 0; j < first.dimension_r_; j++)
			newmatrix[i][j] = first[j][i];
	return newmatrix;
}
} /* namespace std */
