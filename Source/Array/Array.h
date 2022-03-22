#pragma once

#include <initializer_list>

#include "../Iterator/Iterable.h"

template<class T>
class TArray : public IIterable<T>
{
public:

	explicit TArray(int Size = 0);
	TArray(const std::initializer_list<T>& List);
	TArray(const TArray<T>& Array);
	TArray(TArray<T>&& Array) noexcept;

	virtual ~TArray();

	TArray<T>& operator = (const TArray<T>& Array);
	TArray<T>& operator = (TArray<T>&& Array) noexcept;

	T& operator [] (const int Index) { return GetElementByIndex(Index); }
	const T& operator [] (const int Index) const { return GetElementByIndex(Index); }

	T& GetElement(const int Index) { return GetElementByIndex(Index); }
	const T& GetElement(const int Index) const { return GetElementByIndex(Index); }

	void Append(const TArray<T>& Array);
	void Add(const T& Value);
	void InsertBefore(const int Index, const T& Value);
	T RemoveAt(const int Index);

	void Clear();

	int GetLength() const { return ActualSize; }

	virtual IIterator<T>* GetIterator() override;
	virtual IIteratorConst<T>* GetConstIterator() const override;

	bool operator == (const TArray<T>& Array) const;
	bool operator != (const TArray<T>& Array) const { return !((*this) == Array); }

protected:

private:

	void RelocateMemory(int NewSize);

	inline T& GetElementByIndex(const int Index) const;

	T** ArrayOfElements = nullptr;

	int ActualSize = 0;
	int MaxSize = 0;

};

#include "../Exception/Exception.h"
#include "ArrayIterator.h"

template<class T>
TArray<T>::TArray(int Size)
{
	ActualSize = 0;
	MaxSize = Size;
	ArrayOfElements = new T * [MaxSize]; // allocate memory
}

template<class T>
TArray<T>::TArray(const std::initializer_list<T>& List)
{
	ActualSize = static_cast<int>(List.size());
	MaxSize = ActualSize + static_cast<int>(static_cast<double>(ActualSize) / 3);
	ArrayOfElements = new T * [MaxSize];

	int i = 0;
	for (const T& Value : List)
	{
		ArrayOfElements[i] = new T(Value);
		++i;
	}
}

template<class T>
TArray<T>::TArray(const TArray<T>& Array) // copy method
{
	ActualSize = Array.ActualSize;
	MaxSize = Array.MaxSize;
	ArrayOfElements = new T * [MaxSize];

	for (int i = 0; i < ActualSize; ++i)
	{
		ArrayOfElements[i] = new T(Array[i]);
	}
}

template<class T>
TArray<T>::TArray(TArray<T>&& Array) noexcept
{
	ActualSize = Array.ActualSize;
	MaxSize = Array.MaxSize;
	ArrayOfElements = Array.ArrayOfElements;

	Array.ArrayOfElements = nullptr;
}

template<class T>
TArray<T>::~TArray()
{
	Clear();
}

template<class T>
TArray<T>& TArray<T>::operator = (const TArray<T>& Array) // copy method
{
	if (this == &Array)
	{
		return *this;
	}

	Clear();

	ActualSize = Array.ActualSize;
	MaxSize = Array.MaxSize;
	ArrayOfElements = new T * [MaxSize];

	for (int i = 0; i < ActualSize; ++i)
	{
		ArrayOfElements[i] = new T(Array[i]);
	}

	return *this;
}

template<class T>
TArray<T>& TArray<T>::operator = (TArray<T>&& Array) noexcept
{
	if (this == &Array)
	{
		return *this;
	}

	Clear();

	ActualSize = Array.ActualSize;
	MaxSize = Array.MaxSize;
	ArrayOfElements = Array.ArrayOfElements;

	Array.ArrayOfElements = nullptr;

	return *this;
}

template<class T>
void TArray<T>::Append(const TArray<T>& Array)
{
	int NewSize = this->GetLength() + Array.GetLength();
	this->RelocateMemory(NewSize);
	for (const T& Value : Array)
	{
		this->Add(Value);
	}
}

template<class T>
void TArray<T>::Add(const T& Value)
{
	if (ActualSize == MaxSize)
	{
		RelocateMemory(MaxSize + 1);
	}

	int IndexOfLastElement = ActualSize;
	++ActualSize;
	ArrayOfElements[IndexOfLastElement] = new T(Value);
}

template<class T>
void TArray<T>::InsertBefore(const int Index, const T& Value)
{
	if (ActualSize == MaxSize)
	{
		RelocateMemory(MaxSize + 1);
	}

	int i = ActualSize;
	++ActualSize;
	while (i > Index)
	{
		ArrayOfElements[i] = ArrayOfElements[i - 1];
		--i;
	}

	ArrayOfElements[Index] = new T(Value);
}

template<class T>
T TArray<T>::RemoveAt(const int Index)
{
	T ReturnValue = *(ArrayOfElements[Index]);

	delete[] ArrayOfElements[Index];

	int i = Index;
	const int MaxIndex = ActualSize - 2;
	while (i <= MaxIndex)
	{
		ArrayOfElements[i] = ArrayOfElements[i + 1];
		++i;
	}

	ArrayOfElements[i] = nullptr;

	--ActualSize;

	if (ActualSize < MaxSize / 2)
	{
		RelocateMemory(ActualSize + 1);
	}

	return ReturnValue;
}

template<class T>
void TArray<T>::Clear() // dealloc memory
{
	if (ArrayOfElements != nullptr)
	{
		for (int i = 0; i < ActualSize; i++)
		{
			delete ArrayOfElements[i];
		}
		delete[] ArrayOfElements;
		ArrayOfElements = nullptr;
	}
	ActualSize = 0;
	MaxSize = 0;
}

template<class T>
void TArray<T>::RelocateMemory(int NewSize) // for max size
{
	int NewMaxSize = NewSize * 2;
	T** NewArrayOfElements = new T*[NewMaxSize];

	for (int i = 0; i < ActualSize; ++i)
	{
		NewArrayOfElements[i] = ArrayOfElements[i];
	}

	MaxSize = NewMaxSize;

	delete[] ArrayOfElements;
	ArrayOfElements = NewArrayOfElements;
}

template<class T>
T& TArray<T>::GetElementByIndex(const int Index) const
{
	if (Index >= 0 && Index < GetLength() && ArrayOfElements != nullptr)
	{
		return *(ArrayOfElements[Index]);
	}
	else
	{
		throw AException("Exception thrown: Incorrect index.");
	}
}

template<class T>
IIterator<T>* TArray<T>::GetIterator()
{
	return new TArrayIterator<T>(this);
}

template<class T>
IIteratorConst<T>* TArray<T>::GetConstIterator() const
{
	return new TArrayIteratorConst<T>(this);
}

template<class T>
bool TArray<T>::operator == (const TArray<T>& Array) const
{
	if (this == &Array)
	{
		return true;
	}

	if (this->GetLength() != Array.GetLength())
	{
		return false;
	}

	for (int i = this->GetLength() - 1; i >= 0; --i)
	{
		if (this->GetElement(i) != Array.GetElement(i))
		{
			return false;
		}
	}

	return true;
}
