/*
 * forwardnode.h
 *
 *  Created on: Dec 20, 2015
 *      Author: zonglin
 */
#include "Matrix/matrix.h"
#include <cstring>
#include <cstdio>
#ifndef FORWARDNODE_H_
#define FORWARDNODE_H_

class forwardnode
{
private:
  size_t m_;
  matrix* _weights_;
  matrix* _weighterrors_;
  matrix* _input_;
  matrix(*_activation_)(matrix&);
  matrix(*_derivative_)(matrix&);
public:
  /**
   * Default constructor. Set everything to NULL or 0
   */
	forwardnode();
	/**
	 * Copy constructor. The two instance will be independent to each other.
	 */
	forwardnode(const forwardnode& copy);
	/**
	 * Specify the input and output dimension; Assuming the number of data sets
	 * is the number of rows of input matrix.
	 */
	forwardnode(dimension& outputdimension, dimension& inputdimension);
	/**
	 * Forward propagation through this node. The output is the output of this node.
	 */
	matrix forward(const matrix& input);
	/**
	 * Backward propagation through this node. The output is the error of previous node
	 */
	matrix backward(const matrix& error, double lambda);
	/**
	 * Set the activation function
	 */
	void setactivationfunction(const matrix&(*activation)(matrix&));
	/**
	 * Set the derivative of activation function
	 */
	void setderivativeactivation(const matrix&(*derivative)(matrix&));
	/**
	 * Update weights. Before this function is called, the gradients will only accumulate,
	 * left the weights unchanged.
	 */
	void updateweights();
	/**
	 * Destructor
	 */
	~forwardnode();
};
#endif /* FORWARDNODE_H_ */
