/*
 * dimension.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#include "dimension.h"

namespace std
{

dimension::dimension()
{
	dimension_c_ = 1;
	diemnsion_r_ = 1;
}

dimension::dimension(int r, int c)
{
	dimension_c_ = c;
	diemnsion_r_ = r;
}

dimension::~dimension()
{
}

} /* namespace std */
