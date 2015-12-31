/*
 * dimension.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#include "dimension.h"
#include <sstream>
#include <iostream>

bool dimension::operator==(dimension& second)
{
	return dimension_r_ == second.dimension_r_ && dimension_c_ == second.dimension_c_;
}

dimension::dimension()
{
	dimension_c_ = 1;
	dimension_r_ = 1;
}

dimension::dimension(size_t r, size_t c)
{
	dimension_c_ = c;
	dimension_r_ = r;
}

dimension::~dimension()
{
}

std::string dimension::tostring()
{
  std::stringstream strm;
  strm << '(' << dimension_r_ << " x " << dimension_c_ << ')';
  return strm.str();
}
