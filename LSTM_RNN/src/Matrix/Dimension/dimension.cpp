/*
 * dimension.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#include "dimension.h"

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

namespace std {

bool operator==(dimension& first, dimension& second)
{
	return first.diemnsion_r_ == second.diemnsion_r_ && first.dimension_c_ == second.dimension_c_;
}

}
