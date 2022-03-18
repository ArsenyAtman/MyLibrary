#pragma once

#include <initializer_list>

#include "ListElement.h"
#include "Iterable.h"
#include "Stringable.h"

template<class T>
class TList : public IIterable<T>
{
public:

	TList();
	TList(const std::initializer_list<T>& List);
	TList(const TList<T>& List);
	TList(TList<T>&& List);

	virtual ~TList();

	TList& operator = (const TList<T>& List);
	TList& operator = (TList<T>&& List);

	void PushForward(const T& Value);
	void PushBack(const T& Value);

	T PopForward();
	T PopBack();

	void InsertBefore(TListElement<T>* BeforeElement, const int& Value);
	void Remove(TListElement<T>* ElementToRemove);

	void AppendList(const TList<T>& List);

	void Clear();

	T& GetFirst() { return FirstElement->GetValue(); }
	const T& GetFirst() const { return FirstElement->GetValue(); }

	T& GetLast() { return LastElement->GetValue(); }
	const T& GetLast() const { return LastElement->GetValue(); }

	TListElement<T>* GetFirstElement();
	const TListElement<T>* GetFirstElement() const;

	TListElement<T>* GetLastElement();
	const TListElement<T>* GetLastElement() const;

	virtual IIterator<T>* GetIterator() override;
	virtual IIteratorConst<T>* GetConstIterator() const override;

	bool operator == (const TList<T>& List) const;
	bool operator != (const TList<T>& List) { return !((*this) == List); }

	int GetLength() const;

protected:

private:

	TListElement<T>* FirstElement = nullptr;
	TListElement<T>* LastElement = nullptr;

	int Size = 0;

};

#include "ListIterator.h"

template<class T>
TList<T>::TList() : FirstElement(nullptr), LastElement(nullptr)
{
	Size = 0;
}

template<class T>
TList<T>::TList(const std::initializer_list<T>& List)
{
	for (const T& Value : List)
	{
		this->PushBack(Value);
	}
}

template<class T>
TList<T>::TList(const TList<T>& List)
{
	for (const T& Value : List)
	{
		this->PushBack(Value);
	}
}

template<class T>
TList<T>::TList(TList<T>&& List)
{
	FirstElement = List.FirstElement;
	LastElement = List.LastElement;
	Size = List.Size;

	List.FirstElement = nullptr;
	List.LastElement = nullptr;
}

template<class T>
TList<T>::~TList()
{
	this->Clear();
}

template<class T>
TList<T>& TList<T>::operator = (const TList<T>& List)
{
	if (this == &List)
	{
		return *this;
	}

	this->Clear();

	for (const T& Value : List)
	{
		this->PushBack(Value);
	}

	return *this;
}

template<class T>
TList<T>& TList<T>::operator = (TList<T>&& List)
{
	if (this == &List)
	{
		return *this;
	}

	this->Clear();

	FirstElement = List.FirstElement;
	LastElement = List.LastElement;
	Size = List.Size;

	List.FirstElement = nullptr;
	List.LastElement = nullptr;

	return *this;
}

template<class T>
void TList<T>::PushForward(const T& Value)
{
	TListElement<T>* NewElement = new TListElement<T>(Value, nullptr, FirstElement);
	if (FirstElement != nullptr)
	{
		FirstElement->SetPrev(NewElement);
	}
	else
	{
		LastElement = NewElement;
	}
	FirstElement = NewElement;

	++Size;
}

template<class T>
void TList<T>::PushBack(const T& Value)
{
	TListElement<T>* NewElement = new TListElement<T>(Value, LastElement, nullptr);
	if (LastElement != nullptr)
	{
		LastElement->SetNext(NewElement);
	}
	else
	{
		FirstElement = NewElement;
	}
	LastElement = NewElement;

	++Size;
}

template<class T>
T TList<T>::PopForward()
{
	T ReturnValue = GetFirstElement()->GetValue();

	TListElement<T>* ElementToPop = FirstElement;
	FirstElement = ElementToPop->GetNext();
	delete ElementToPop;

	--Size;

	return ReturnValue;
}

template<class T>
T TList<T>::PopBack()
{
	T ReturnValue = GetLastElement()->GetValue();

	TListElement<T>* ElementToPop = LastElement;
	LastElement = ElementToPop->GetPrev();
	delete ElementToPop;

	--Size;

	return ReturnValue;
}

template<class T>
void TList<T>::InsertBefore(TListElement<T>* BeforeElement, const int& Value)
{
	TListElement<T>* NewListElement = new TListElement<T>(Value, BeforeElement->GetPrev(), BeforeElement);

	if (BeforeElement->GetPrev() != nullptr)
	{
		BeforeElement->GetPrev()->SetNext(NewListElement);
	}

	BeforeElement->SetPrev(NewListElement);

	if (BeforeElement == FirstElement)
	{
		FirstElement = NewListElement;
	}
}

template<class T>
void TList<T>::Remove(TListElement<T>* ElementToRemove)
{
	if (ElementToRemove == FirstElement)
	{
		FirstElement = ElementToRemove->GetNext();
	}

	if (ElementToRemove == LastElement)
	{
		LastElement = ElementToRemove->GetPrev();
	}

	delete ElementToRemove;
}

template<class T>
void TList<T>::AppendList(const TList<T>& List)
{
	for (const T& Value : List)
	{
		this->PushBack(Value);
	}
}

template<class T>
void TList<T>::Clear()
{
	while (FirstElement != nullptr)
	{
		PopForward();
	}
}

template<class T>
TListElement<T>* TList<T>::GetFirstElement()
{
	return FirstElement;
}

template<class T>
const TListElement<T>* TList<T>::GetFirstElement() const
{
	return FirstElement;
}

template<class T>
TListElement<T>* TList<T>::GetLastElement()
{
	return LastElement;
}

template<class T>
const TListElement<T>* TList<T>::GetLastElement() const
{
	return LastElement;
}

template<class T>
IIterator<T>* TList<T>::GetIterator()
{
	return new TListIterator<T>(this);
}

template<class T>
IIteratorConst<T>* TList<T>::GetConstIterator() const
{
	return new TListIteratorConst<T>(this);
}

template<class T>
bool TList<T>::operator == (const TList<T>& List) const
{
	if (this == &List)
	{
		return true;
	}

	if (this->GetLength() != List.GetLength())
	{
		return false;
	}

	IIteratorConst<T>* Iterator1 = this->GetConstIterator();
	IIteratorConst<T>* Iterator2 = List.GetConstIterator();
	while (Iterator1->HasMore())
	{
		if (Iterator1->Get() != Iterator2->Get())
		{
			return false;
		}

		Iterator1->Next();
		Iterator2->Next();
	}

	delete Iterator1;
	delete Iterator2;

	return true;
}

template<class T>
int TList<T>::GetLength() const
{
	return Size;
}
