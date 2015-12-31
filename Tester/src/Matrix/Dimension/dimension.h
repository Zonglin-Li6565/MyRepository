/*
 * dimension.h
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */
#include<string>
#ifndef DIMENSION_H_
#define DIMENSION_H_

class dimension
{
public:
	size_t dimension_c_;
	size_t dimension_r_;
	dimension(size_t r, size_t c);
	dimension();
	virtual ~dimension();
	bool operator==(dimension& second);
	std::string tostring();
};

#endif /* DIMENSION_H_ */
