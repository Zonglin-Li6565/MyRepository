/*
 * linkedlist.h
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */

#ifndef MATRIX_LIST_LINKEDLIST_H_
#define MATRIX_LIST_LINKEDLIST_H_

namespace std
{

template <typename T>class linkedlist
{
private:
	struct helper{
		helper* next_;
		helper* previous_;
		T* value_;
		~helper();
	};
	helper head_;
	helper tail_;
public:
	int size_;
	linkedlist();
	void add(T* element);
	void insert(T* element, int index);
	void remove(int index);
	T& operator[](int index);
	virtual ~linkedlist();
};

} /* namespace std */

#endif /* MATRIX_LIST_LINKEDLIST_H_ */
