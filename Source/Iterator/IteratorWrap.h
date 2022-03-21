#pragma once

template<class T>
class AIteratorWrapBase
{
public:

	AIteratorWrapBase() : Iterator(nullptr)
	{
		// ...
	}

	virtual ~AIteratorWrapBase()
	{
		delete Iterator;
	}

	AIteratorWrapBase(const AIteratorWrapBase<T>& IteratorWrap) = delete;
	AIteratorWrapBase<T>& operator = (const AIteratorWrapBase<T>& IteratorWrap) = delete;

	AIteratorWrapBase(AIteratorWrapBase<T>&& IteratorWrap)
	{
		this->Iterator = IteratorWrap.Iterator;
		IteratorWrap.Iterator = nullptr;
	}

	AIteratorWrapBase<T>& operator = (AIteratorWrapBase<T>&& IteratorWrap)
	{
		if (this == &IteratorWrap)
		{
			return *this;
		}

		this->Iterator = IteratorWrap.Iterator;
		IteratorWrap.Iterator = nullptr;

		return *this;
	}

	void operator ++ () { Iterator->Next(); }
	bool operator != (int) { return Iterator->HasMore(); }

protected:

	IIteratorBase<T>* Iterator = nullptr;
};

template<class T>
class AIteratorWrap : public AIteratorWrapBase<T>
{
public:

	AIteratorWrap(IIterator<T>* Iterator)
	{
		this->Iterator = Iterator;
	}

	T& operator * () { return dynamic_cast<IIterator<T>*>(this->Iterator)->Get(); }
};

template<class T>
class AIteratorWrapConst : public AIteratorWrapBase<T>
{
public:

	AIteratorWrapConst(IIteratorConst<T>* Iterator)
	{
		this->Iterator = Iterator;
	}

	const T& operator * () { return dynamic_cast<IIteratorConst<T>*>(this->Iterator)->Get(); }
};
