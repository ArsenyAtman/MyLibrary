#pragma once

#include "Iterator.h"
#include "ListElement.h"
#include "List.h"

template<class T>
class TListIteratorBase
{
public:

	TListIteratorBase();

};

template<class T>
TListIteratorBase<T>::TListIteratorBase()
{
	// ...
}

template<class T>
class TListIterator : public TListIteratorBase<T>, public IIterator<T>
{
public:

	TListIterator(TList<T>* List)
	{
		this->List = List;
		CurrentListElement = List->GetFirstElement();
	}

	virtual void Next() override { CurrentListElement = CurrentListElement->GetNext(); }
	virtual T& Get() override { return CurrentListElement->GetValue(); }
	virtual bool HasMore() override { return CurrentListElement != nullptr; }

	void InsertBefore(const T& Value)
	{
		this->List->InsertBefore(CurrentListElement, Value);
	}

	void Remove()
	{
		TListElement<T>* Next = CurrentListElement->GetNext();
		this->List->Remove(CurrentListElement);
		CurrentListElement = Next;
	}

protected:

	TList<T>* List = nullptr;
	TListElement<T>* CurrentListElement = nullptr;

};

template<class T>
class TListIteratorConst : public TListIteratorBase<T>, public IIteratorConst<T>
{
public:

	TListIteratorConst(const TList<T>* List)
	{
		this->List = List;
		CurrentListElement = List->GetFirstElement();
	}

	virtual void Next() override { CurrentListElement = CurrentListElement->GetNext(); }
	virtual const T& Get() override { return CurrentListElement->GetValue(); }
	virtual bool HasMore() override { return CurrentListElement != nullptr; }

protected:

	const TList<T>* List = nullptr;
	const TListElement<T>* CurrentListElement = nullptr;

};