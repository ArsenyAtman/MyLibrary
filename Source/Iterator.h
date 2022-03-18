#pragma once

template <class T>
class IIteratorBase
{
public:

	virtual void Next() = 0;
	virtual bool HasMore() = 0;
	
};

template <class T>
class IIterator : public IIteratorBase<T>
{
public:

	virtual T& Get() = 0;

};

template <class T>
class IIteratorConst : public IIteratorBase<T>
{
public:

	virtual const T& Get() = 0;

};