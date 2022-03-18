#pragma once

#include "Iterator.h"
#include "IteratorWrap.h"

template<class T>
class IIterable
{
public:

	virtual IIterator<T>* GetIterator() = 0;
	virtual IIteratorConst<T>* GetConstIterator() const = 0;

	AIteratorWrap<T> begin() { return AIteratorWrap<T>(GetIterator()); }
	AIteratorWrapConst<T> begin() const { return AIteratorWrapConst<T>(GetConstIterator()); }
	int end() const { return 0; }
};
