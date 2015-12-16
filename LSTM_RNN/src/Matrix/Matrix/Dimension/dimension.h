/*
 * dimension.h
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#ifndef DIMENSION_H_
#define DIMENSION_H_

namespace std
{

class dimension
{
public:
	int dimension_c_;
	int diemnsion_r_;
	dimension(int r, int c);
	dimension();
	virtual ~dimension();
};

} /* namespace std */

#endif /* DIMENSION_H_ */
