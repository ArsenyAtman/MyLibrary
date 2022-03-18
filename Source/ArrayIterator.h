#pragma once

#include "Iterator.h"
#include "Array.h"

template<class T>
class TArrayIteratorBase
{
public:

	TArrayIteratorBase()
	{
		CurrentIndex = 0;
	}
	
protected:

	void GoToNext(const TArray<T>* Array)
	{
		++CurrentIndex;
	}

	bool HasMoreElements(const TArray<T>* Array)
	{
		return CurrentIndex != Array->GetLength();
	}

	int CurrentIndex = 0;

};

template<class T>
class TArrayIterator : public TArrayIteratorBase<T>, public IIterator<T>
{
public:

	TArrayIterator(TArray<T>* Array)
	{
		this->Array = Array;
	}

	virtual void Next() override { this->GoToNext(Array); }
	virtual T& Get() override { return Array->GetElement(this->CurrentIndex); }
	virtual bool HasMore() override { return this->HasMoreElements(Array); }

private:

	TArray<T>* Array;

};

template<class T>
class TArrayIteratorConst : public TArrayIteratorBase<T>, public IIteratorConst<T>
{
public:

	TArrayIteratorConst(const TArray<T>* Array)
	{
		this->Array = Array;
	}

	virtual void Next() override { this->GoToNext(Array); }
	virtual const T& Get() override { return Array->GetElement(this->CurrentIndex); }
	virtual bool HasMore() override { return this->HasMoreElements(Array); }

private:

	const TArray<T>* Array;

};
