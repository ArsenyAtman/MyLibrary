#pragma once

#include "../Array/Array.h"
#include "../List/List.h"
#include "../List/ListElement.h"
#include "../Iterator/Iterable.h"
#include "../Iterator/Iterator.h"

enum class ESortType
{
	Ascending,
	Descending
};

class LAlgo
{
public:

	template<class T>
	static void Swap(T& Value1, T& Value2);

	template<class T>
	static int LinearSearch(const IIterable<T>& Iterable, const T& ElementToFind);

	template<class T>
	static int BinarySearch(const TArray<T>& SortedArray, const T& ElementToFind);

	template<class T>
	static void QuickSort(const TArray<T>& Array, ESortType SortType);

	template<class T>
	static void MergeSort(const TList<T>& List, ESortType SortType);

	template<class T>
	static void Reverse(const TArray<T>& Array);

	template<class T>
	static void Reverse(const TList<T>& List);

	static bool IsEven(int Number);
};

template<class T>
void LAlgo::Swap(T& Value1, T& Value2)
{
	T Buff = Value1;
	Value1 = Value2;
	Value2 = Buff;
}

template<class T>
int LAlgo::LinearSearch(const IIterable<T>& Iterable, const T& ElementToFind)
{
	IIterator<T>* Iterator = Iterable.GetConstIterator();

	int i = 0;
	while (Iterator->HasMore())
	{
		if (Iterator->Get() == ElementToFind)
		{
			delete Iterator;
			return i;
		}

		++i;
		Iterator->Next();
	}

	delete Iterator;

	return -1;
}

template<class T>
int LAlgo::BinarySearch(const TArray<T>& SortedArray, const T& ElementToFind)
{

}

template<class T>
void LAlgo::QuickSort(const TArray<T>& Array, ESortType SortType)
{

}

template<class T>
void LAlgo::MergeSort(const TList<T>& List, ESortType SortType)
{

}

template<class T>
void LAlgo::Reverse(const TArray<T>& Array)
{
	int ForwardElement = 0;
	int BackwardElement = Array.GetLength() - 1;

	while (ForwardElement < BackwardElement)
	{
		LAlgo::Swap(Array[ForwardElement], Array[BackwardElement]);

		++ForwardElement;
		--BackwardElement;
	}
}

template<class T>
void LAlgo::Reverse(const TList<T>& List)
{
	TListElement<T>* ForwardElement = List.GetFirstElement();
	TListElement<T>* BackwardElement = List.GetLastElement();

	while (ForwardElement != BackwardElement || ForwardElement->GetNext() != BackwardElement)
	{
		LAlgo::Swap(ForwardElement->GetValue(), BackwardElement->GetValue);

		ForwardElement = ForwardElement->GetNext();
		BackwardElement = BackwardElement->GetPrev();
	}
}