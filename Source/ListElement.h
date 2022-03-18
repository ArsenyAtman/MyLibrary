#pragma once

#include "Iterable.h"

template<class T>
class TListElement
{
public:

	TListElement(const T& Value, TListElement<T>* Prev, TListElement<T>* Next);
	TListElement(const TListElement<T>& ListElement) = delete;
	TListElement(TListElement<T>&& ListElement);

	virtual ~TListElement();

	TListElement<T>& operator = (const TListElement& ListElement) = delete;
	TListElement<T>& operator = (TListElement&& ListElement);

	T& GetValue();
	const T& GetValue() const;
	void SetValue(const T& NewValue);

	TListElement<T>* GetPrev() const;
	void SetPrev(TListElement<T>* Prev);

	TListElement<T>* GetNext() const;
	void SetNext(TListElement<T>* Next);

protected:

private:

	T Value;
	TListElement<T>* Prev;
	TListElement<T>* Next;
};

template<class T>
TListElement<T>::TListElement(const T& Value, TListElement<T>* Prev, TListElement<T>* Next)
{
	this->Value = Value;
	this->Prev = Prev;
	this->Next = Next;
}

template<class T>
TListElement<T>::TListElement(TListElement&& ListElement)
{
	this->Value = ListElement.Value;
	this->Prev = ListElement.Prev;
	this->Next = ListElement.Next;
	
	ListElement.Prev = nullptr;
	ListElement.Next = nullptr;
}

template<class T>
TListElement<T>::~TListElement()
{
	if (Prev != nullptr)
	{
		this->Prev->SetNext(this->Next);
	}

	if (Next != nullptr)
	{
		this->Next->SetPrev(this->Prev);
	}
}

template<class T>
TListElement<T>& TListElement<T>::operator = (TListElement&& ListElement)
{
	if (this == &ListElement)
	{
		return *this;
	}

	this->Value = ListElement.Value;
	this->Prev = ListElement.Prev;
	this->Next = ListElement.Next;

	ListElement.Prev = nullptr;
	ListElement.Next = nullptr;

	return *this;
}

template<class T>
T& TListElement<T>::GetValue()
{
	return Value;
}

template<class T>
const T& TListElement<T>::GetValue() const
{
	return Value;
}

template<class T>
void TListElement<T>::SetValue(const T& NewValue)
{
	Value = NewValue;
}

template<class T>
TListElement<T>* TListElement<T>::GetPrev() const
{
	return Prev;
}

template<class T>
void TListElement<T>::SetPrev(TListElement* Prev)
{
	this->Prev = Prev;
}

template<class T>
TListElement<T>* TListElement<T>::GetNext() const
{
	return Next;
}

template<class T>
void TListElement<T>::SetNext(TListElement* Next)
{
	this->Next = Next;
}
