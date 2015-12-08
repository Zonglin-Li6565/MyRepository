/*
 * dimension.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#include "dimension.h"

namespace std
{

dimension::dimension(int r, int c)
{
	dimension_c_ = c;
	diemnsion_r_ = r;
}

dimension::~dimension()
{
	delete &dimension_c_;
	delete &diemnsion_r_;
}

} /* namespace std */
