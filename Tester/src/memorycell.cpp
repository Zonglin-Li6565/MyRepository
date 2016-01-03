/*
 * memorycell.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: zonglin
 */

#include "memorycell.h"

void memorycell::updatevalue(const matrix& value)
{
	if(!(value.getdimension() == _currentvalue_->getdimension()))
		throw std::runtime_error("Try to put matrix with inconsistent dimension");
	*_previousvalue_ = *_currentvalue_;
	*_currentvalue_ = value;
}

memorycell::memorycell()
{
	_currentvalue_ = new matrix(1, 1);
	_previousvalue_ = NULL;
}

memorycell::memorycell(const dimension& dim)
{
	_currentvalue_ = new matrix(dim);
	_previousvalue_ = NULL;
}

memorycell::~memorycell()
{
	delete &_currentvalue_;
	delete &_previousvalue_;
}

