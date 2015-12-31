/*
 * forwardnode.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: zonglin
 */

#include "forwardnode.h"

forwardnode::forwardnode()
{
  m_ = 0;
  _weights_ = NULL;
  _weighterrors_ = NULL;
  _input_ = NULL;
	_activation_ = NULL;
	_derivative_ = NULL;
}

forwardnode::forwardnode(dimension& outputdimension, dimension& inputdimension)
{
	if(outputdimension.dimension_r_ != inputdimension.dimension_r_)
	{
	  perror("invalid output and input dimension.");
	  exit(1);
	}
	m_ = inputdimension.dimension_r_;
	_weights_ = new matrix(outputdimension.dimension_c_, inputdimension.dimension_c_ + 1);
	_weighterrors_ = new matrix(_weights_->getdimension());
	_weights_->randomize();
	_activation_ = NULL;
	_derivative_ = NULL;
}

matrix forwardnode::forward(const matrix& input)
{
  if(_input_ != NULL) delete _input_;
	_input_ = new matrix(input);
	_input_->addcols(0, 1, 1.0);
	if(_activation_ == NULL)
	{
	  perror("Activation function not yet set");
	  exit(1);
	}
	return _activation_((*_input_) * (!(*_weights_)));
}

matrix forwardnode::backward(const matrix& error, double lambda)
{
	matrix der_input = _derivative_(*_input_);
	_weighterrors_ = &(*_weighterrors_ + (!error * (*_input_)));
	//////////////////////////regularization//////////////////////////
  _weighterrors_ = &(*_weighterrors_ + lambda * (*_weights_));
	matrix input_grad = error * (*_weights_) >> der_input;
  input_grad.removecols(0, 1);
	return input_grad;
}

void forwardnode::updateweights()
{
  if(_weighterrors_ == NULL || _weights_ == NULL)
  {
    perror("No gradient of weight to update, or no weights available. Check whether using the default constructor");
    exit(1);
  }
	_weights_ = &(*_weights_ - *_weighterrors_);
	delete _weighterrors_;
	_weighterrors_ = new matrix(_weights_->getdimension());
}

void forwardnode::setactivationfunction(const matrix& (*activation)(matrix&))
{
	_activation_ = activation;
}

void forwardnode::setderivativeactivation(const matrix& (*derivative)(matrix&))
{
	_derivative_ = derivative;
}

forwardnode::~forwardnode()
{
  delete _weights_;
  delete _weighterrors_;
  delete _input_;
}
