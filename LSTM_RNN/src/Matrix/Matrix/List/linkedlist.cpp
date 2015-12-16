/*
 * linkedlist.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: zonglin
 */
#include <stdexcept>
#include <iostream>

namespace std
{

template <typename T>class linkedlist
{
private:
	struct helper{
		helper* next_;
		helper* previous_;
		T* value_;
//		virtual ~helper()
//		{
//			if(value_ != NULL) delete value_;
//		}
	};
	helper head_;
	helper tail_;
public:
	int size_;
	linkedlist()
	{
		size_ = 0;
		head_.next_ = &tail_;
		head_.previous_ = 0;
		tail_.previous_ = &head_;
		tail_.next_ = 0;
	}
	void add(T* element)
	{
		insert(element, size_);
	}
	void add(T& element)
	{
		insert(&element, size_);
	}
	void insert(T* element, int index)
	{
		if(index > size_)
			throw runtime_error("index out of bound");
		helper* newelement = new helper();
		newelement->value_ = element;
		helper* current = &head_;
		for(int i = 0; i < index; i++)
		{
			current = current->next_;
		}
		newelement->previous_ = current;
		newelement->next_ = current->next_;
		current->next_->previous_ = newelement;
		current->next_ = newelement;
		size_ ++;
	}
	void remove(int index)
	{
		cout << "removing " << index << endl;
		if(index >= size_)
			throw runtime_error("index out of bound");
		helper* current = &head_;
		for(int i = 0; i <= index; i++)
			current = current->next_;
		current->previous_->next_ = current->next_;
		current->next_->previous_ = current->previous_;
		size_ --;
		delete current;
	}
	T& operator[](int index)
	{
		if(index >= size_)
			throw runtime_error("index out of bound");
		helper* current = &head_;
		for(int i = 0; i <= index; i++)
			current = current->next_;
		return *(current->value_);
	}
	virtual ~linkedlist()
	{
		for(int i = size_ - 1; i >= 0; i--){
			cout << "going to remove " << i << endl;
			remove(i);
			cout << "size = " << size_ << endl;
		}
	}
};

} /* namespace std */
