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
private:
  matrix* _currentvalue_;
  matrix* _previousvalue_;
public:
	void updatevalue(const matrix& value);
	memorycell();
	memorycell(const dimension& dim);
	~memorycell();
};

#endif /* MEMORYCELL_H_ */
