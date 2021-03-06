/*
 * matrix.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: zonglin
 */

#include "matrix.h"
#include <algorithm>
#include <cstring>
#include <stdexcept>

void matrix::initialize(size_t rows, size_t cols)
{
  dimension_r_ = rows;
  dimension_c_ = cols;
  if(_cols_ != NULL) delete _cols_;
  _cols_ = new std::vector<double*>(cols);
  for (size_t i = 0; i < dimension_c_; i++)
  {
  	(*_cols_)[i] = new double[rows];
  }
}

double* matrix::getcolumnhead_const(size_t index) const
{
  size_t zero = 0;
  if(index < dimension_c_ && index >= zero)
  {
    return (*_cols_)[index];
  }
  return NULL;
}

double* matrix::getcolumnhead(size_t index)
{
  size_t zero = 0;
  if(index < dimension_c_ && index >= zero)
  {
    return (*_cols_)[index];
  }
  return NULL;
}

matrix::matrix()
{
  _cols_ = NULL;
	initialize(1, 1);
}

matrix::matrix(size_t rows, size_t cols)
{
  _cols_ = NULL;
	initialize(rows, cols);
}

matrix::matrix(const dimension& d)
{
  _cols_ = NULL;
	initialize(d.dimension_r_, d.dimension_c_);
}

matrix::matrix(const matrix& copy)
{
  _cols_ = NULL;
	initialize(copy.dimension_r_, copy.dimension_c_);
	for(size_t i = 0; i < dimension_r_; i++)
	{
	  for(size_t j = 0; j < dimension_c_; j++)
	  {
	    (*_cols_)[j][i] = copy.access(i, j);
	  }
	}
}

matrix::~matrix()
{
  free();
}

void matrix::free()
{
  for(size_t i = 0; i < dimension_c_; i++)
  {
    delete[] (*_cols_)[i];
  }
  delete _cols_;
  _cols_ = NULL;
}

double& matrix::access(size_t row, size_t col) const
{
  if(row < 0 || row >= dimension_r_ || col < 0 || col >= dimension_c_)
  {
    perror("index out of bound");
    exit(1);
  }
	return (*_cols_)[col][row];
}

void matrix::addcols(size_t index, size_t num_c, double value)
{
  for(size_t i = 0; i < num_c; i++)
  {
  	double* _newcol = new double[dimension_r_];
  	std::fill_n(_newcol, dimension_r_, value);
  	_cols_->insert(_cols_->begin() + index, _newcol);
  }
  dimension_c_ += num_c;
}	

void matrix::removecols(size_t index, size_t num_c)
{
  for(size_t i = 0; i < num_c; i++)
  {
  	delete (*_cols_)[i + index];
  }
  _cols_->erase(_cols_->begin() + index, _cols_->begin() + index + num_c);
  dimension_c_ -= num_c;
}

void matrix::fill(double value)
{
  for(int i = 0; i < dimension_c_; i++)
  {
    double* _head = (*_cols_)[i];
    std::fill(_head, _head + dimension_r_, value);
  }
}

matrix matrix::getrow(size_t index) const
{
	matrix temp(1, dimension_c_);
	for (size_t i = 0; i < dimension_c_; i++)
	{
		temp(0, i) = access(index, i);
	}
	return temp;
}

matrix matrix::getcol(size_t index) const
{
	matrix temp(dimension_r_, 1);
	for (size_t i = 0; i < dimension_r_; i++)
	{
		temp(i, 0) = access(i, index);
	}
	return temp;
}

dimension matrix::getdimension() const
{
	return dimension(dimension_r_, dimension_c_);
}

double& matrix::operator()(size_t row, size_t col)
{
  if(row < 0 || row >= dimension_r_ || col < 0 || col >= dimension_c_)
  {
    perror("index out of bound");
    exit(1);
  }
  return (*_cols_)[col][row];
}

matrix& matrix::operator=(const matrix& newone)
{
	if (this == &newone)
		return *this;
	free();
	initialize(newone.dimension_r_, newone.dimension_c_);
	for(size_t i = 0; i < dimension_c_; i++)
	{
	  memcpy((*_cols_)[i], (*newone._cols_)[i], dimension_r_);
	}
	return *this;
}

size_t matrix::getrowsize() const
{
  return dimension_r_;
}

size_t matrix::getcolumnsize() const
{
  return dimension_c_;
}

std::string matrix::tostring()
{
	std::ostringstream s;
	double fac = pow(10, 4);
	for (size_t i = 0; i < dimension_r_; i++)
	{
		for (size_t j = 0; j < dimension_c_; j++)
		{
			s << round((*_cols_)[j][i] * fac) / fac << '\t';
		}
		s << "\n";
	}
	return s.str();
}

bool matrix::operator==(const matrix& right) const
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
    return false;
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead_const(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      if (this_cols[i] != right_cols[i])
      {
        return false;
      }
    }
  }
  return true;
}

bool matrix::operator!=(const matrix& right) const
{
  return !((*this) == right);
}

matrix matrix::operator+(const matrix& right) const
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
    perror("trying to add two matrix with different dimension");
  matrix newmatrix(dimension_r_, dimension_c_);
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead_const(j);
    double* new_cols = newmatrix.getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      new_cols[i] = this_cols[i] + right_cols[i];
    }
  }
  return newmatrix;
}

matrix matrix::operator-(const matrix& right) const
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
    perror("trying to minus one matrix by another one with different dimension");
  matrix newmatrix(dimension_r_, dimension_c_);
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead_const(j);
    double* new_cols = newmatrix.getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      new_cols[i] = this_cols[i] - right_cols[i];
    }
  }
  return newmatrix;
}

matrix matrix::operator/(const matrix& right) const
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
  {
    perror("trying to divide one matrix by another one with different dimension");
    exit(1);
  }
  matrix newmatrix(dimension_r_, dimension_c_);
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead_const(j);
    double* new_cols = newmatrix.getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      new_cols[i] = this_cols[i] / right_cols[i];
    }
  }
  return newmatrix;
}

void matrix::operator+=(const matrix& right)
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
  {
    perror("trying to add one matrix by another one with different dimension");
    exit(1);
  }
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      this_cols[i] += right_cols[i];
    }
  }
}

void matrix::operator-=(const matrix& right)
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
  {
    perror("trying to add one matrix by another one with different dimension");
    exit(1);
  }
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      this_cols[i] -= right_cols[i];
    }
  }
}

matrix matrix::operator>>(const matrix& right) const
{
  if (dimension_c_ != right.dimension_c_
      || dimension_r_ != right.dimension_r_)
    perror("trying to do element multiplication on two matrices with different dimension");
  matrix newmatrix(dimension_r_, dimension_c_);
  for (size_t j = 0; j < dimension_c_; j++)
  {
    double* this_cols = this->getcolumnhead_const(j);
    double* new_cols = newmatrix.getcolumnhead(j);
    double* right_cols = right.getcolumnhead_const(j);
    for (size_t i = 0; i < dimension_r_; i++)
    {
      new_cols[i] = this_cols[i] * right_cols[i];
    }
  }
  return newmatrix;
}

matrix matrix::operator*(const matrix& right) const
{
  if (dimension_c_ != right.dimension_r_)
    perror("cross multiplying two matrices have incompatible dimensions");
  matrix newmatrix(dimension_r_, right.dimension_c_);
  for (size_t i = 0; i < newmatrix.dimension_r_; i++)
  {
    for (size_t j = 0; j < newmatrix.dimension_c_; j++)
    {
      double sum = 0.0;
      for (size_t t = 0; t < dimension_c_; t++)
      {
        sum += access(i, t) * right.access(t, j);
      }
      newmatrix(i, j) = sum;
    }
  }
  return newmatrix;
}

matrix matrix::operator!() const
{
  matrix newmatrix(dimension_c_, dimension_r_);
  for (size_t i = 0; i < dimension_c_; i++)
  {
    for (size_t j = 0; j < dimension_r_; j++)
    {
      newmatrix(i, j) = access(j, i);
    }
  }
  return newmatrix;
}

void matrix::randomize()
{
  srand (time(NULL));
  for(size_t i = 0; i < dimension_r_; i++)
  {
    for(size_t j = 0; j < dimension_c_; j++)
    {
      (*this)(i, j) = 2.0 * rand() / RAND_MAX - 1;
    }
  }
}

namespace std
{

matrix operator-(double left, const matrix& right)
{
  matrix newmatrix(right.getrowsize(), right.getcolumnsize());
  for (size_t i = 0; i < right.getrowsize(); i++)
  {
    for (size_t j = 0; j < right.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left - right.access(i, j);
    }
  }
  return newmatrix;
}

matrix operator-(const matrix& left, double right)
{
  matrix newmatrix(left.getrowsize(), left.getcolumnsize());
  for (size_t i = 0; i < left.getrowsize(); i++)
  {
    for (size_t j = 0; j < left.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left.access(i, j) - right;
    }
  }
  return newmatrix;
}

matrix operator/(double left, const matrix& right)
{
  matrix newmatrix(right.getrowsize(), right.getcolumnsize());
  for (size_t i = 0; i < right.getrowsize(); i++)
  {
    for (size_t j = 0; j < right.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left / right.access(i, j);
    }
  }
  return newmatrix;
}

matrix operator/(const matrix& left, double right)
{
  matrix newmatrix(left.getrowsize(), left.getcolumnsize());
  for (size_t i = 0; i < left.getrowsize(); i++)
  {
    for (size_t j = 0; j < left.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left.access(i, j) / right;
    }
  }
  return newmatrix;
}

matrix operator*(double left, const matrix& right)
{
  matrix newmatrix(right.getrowsize(), right.getcolumnsize());
  for (size_t i = 0; i < right.getrowsize(); i++)
  {
    for (size_t j = 0; j < right.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left * right.access(i, j);
    }
  }
  return newmatrix;
}

matrix operator*(const matrix& left, double right)
{
  matrix newmatrix(left.getrowsize(), left.getcolumnsize());
  for (size_t i = 0; i < left.getrowsize(); i++)
  {
    for (size_t j = 0; j < left.getcolumnsize(); j++)
    {
      newmatrix(i, j) = left.access(i, j) * right;
    }
  }
  return newmatrix;
}

matrix elementcalculation(const matrix& para, double(*_function)(double))
{
  matrix newmatrix(para.getrowsize(), para.getcolumnsize());
  for (size_t i = 0; i < para.getrowsize(); i++)
  {
    for (size_t j = 0; j < para.getcolumnsize(); j++)
    {
      newmatrix(i, j) = _function(para.access(i, j));
    }
  }
  return newmatrix;
}

matrix logmatrix(const matrix& para)
{
  return elementcalculation(para, &log);
}

matrix tanhmatrix(const matrix& para)
{
  return elementcalculation(para, &tanh);
}

double sum(const matrix& para)
{
	double sum = 0.0;
	for (size_t i = 0; i < para.getrowsize(); i++)
	{
    for (size_t j = 0; j < para.getcolumnsize(); j++)
    {
      sum += para.access(i, j);
    }
	}
	return sum;
}

}
