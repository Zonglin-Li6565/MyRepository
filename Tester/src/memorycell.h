/*
 * memorycell.h
 *
 *  Created on: Dec 20, 2015
 *      Author: zonglin
 */
#include "Matrix/matrix.h"
#ifndef MEMORYCELL_H_
#define MEMORYCELL_H_

class memorycell
{
public:
	matrix currentvalue_;
	matrix previousvalue_;
	void updatevalue(matrix value);
	memorycell();
	memorycell(dimension dim);
	virtual ~memorycell();
};

#endif /* MEMORYCELL_H_ */
