/*
 * dimension.h
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#ifndef DIMENSION_H_
#define DIMENSION_H_

class dimension
{
public:
	int dimension_c_;
	int diemnsion_r_;
	dimension(int r, int c);
	dimension();
	virtual ~dimension();
};

namespace std {
bool operator==(dimension& first, dimension& second);
}

#endif /* DIMENSION_H_ */
