/*
 * memorycell.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: zonglin
 */

#include "memorycell.h"

void memorycell::updatevalue(matrix value)
{
	if(!(value.getdimension() == currentvalue_.getdimension()))
		throw std::runtime_error("Try to put matrix with inconsistent dimension");
	previousvalue_ = currentvalue_;
	currentvalue_ = value;
}

memorycell::memorycell()
{
	currentvalue_ = *new matrix(1, 1);
}

memorycell::memorycell(dimension dim)
{
	currentvalue_ = *new matrix(dim);
}

memorycell::~memorycell()
{
	delete &currentvalue_;
	delete &previousvalue_;
}

