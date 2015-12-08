/*
 * odinarynode.h
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#ifndef ODINARYNODE_H_
#define ODINARYNODE_H_

namespace std
{

class odinarynode
{
private:
	matrix value_;
	matrix error_;
public:
	matrix getvalue();
	matrix forwardpropagate(...);
	matrix backpropagate(...);
	odinarynode(dimension in_dimen, dimension out_dimen);
	odinarynode(matrix initial, dimension in_dimen, dimension out_dimen);
	virtual ~odinarynode();
};

} /* namespace std */

#endif /* ODINARYNODE_H_ */
