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
	static void QuickSort(TArray<T>& Array, ESortType SortType);

	template<class T>
	static void MergeSort(TList<T>& List, ESortType SortType);

	template<class T>
	static void Reverse(TArray<T>& Array);

	template<class T>
	static void Reverse(TList<T>& List);

	static bool IsEven(int Number);

protected:

	using DSortComparsion = bool(*)(int, int);

	template<class T>
	static void QuickSortAlgo(TArray<T>& Array, int FirstIndex, int LastIndex, DSortComparsion LeftComparsion, DSortComparsion RightComparsion);

	template<class T>
	static int Partition(TArray<T>& Array, int FirstIndex, int LastIndex, DSortComparsion LeftComparsion, DSortComparsion RightComparsion);

	static bool IsLess(const int Value1, const int Value2);
	static bool IsMore(const int Value1, const int Value2);
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
	IIteratorConst<T>* Iterator = Iterable.GetConstIterator();

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
	int LeftIndex = 0;
	int RightIndex = SortedArray.GetLength() - 1;

	while (LeftIndex != RightIndex)
	{
		int MiddleIndex = LeftIndex + (RightIndex - LeftIndex) / 2;

		if (SortedArray[MiddleIndex] == ElementToFind)
		{
			return MiddleIndex;
		}
		else if (SortedArray[MiddleIndex] < ElementToFind)
		{
			LeftIndex = MiddleIndex + 1;
		}
		else if (SortedArray[MiddleIndex] > ElementToFind)
		{
			RightIndex = MiddleIndex - 1;
		}
	}

	if (SortedArray[LeftIndex] == ElementToFind)
	{
		return LeftIndex;
	}
	else
	{
		return -1;
	}
}

template<class T>
void LAlgo::QuickSort(TArray<T>& Array, ESortType SortType)
{
	switch (SortType)
	{
	case ESortType::Ascending:
		LAlgo::QuickSortAlgo(Array, 0, Array.GetLength() - 1, &LAlgo::IsLess, &LAlgo::IsMore);
		break;

	case ESortType::Descending:
		LAlgo::QuickSortAlgo(Array, 0, Array.GetLength() - 1, &LAlgo::IsMore, &LAlgo::IsLess);
		break;
	}
	
}

template<class T>
void LAlgo::MergeSort(TList<T>& List, ESortType SortType)
{

}

template<class T>
void LAlgo::Reverse(TArray<T>& Array)
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
void LAlgo::Reverse(TList<T>& List)
{
	TListElement<T>* ForwardElement = List.GetFirstElement();
	TListElement<T>* BackwardElement = List.GetLastElement();

	while ((ForwardElement != BackwardElement) && (ForwardElement->GetPrev() != BackwardElement))
	{
		LAlgo::Swap(ForwardElement->GetValue(), BackwardElement->GetValue());

		ForwardElement = ForwardElement->GetNext();
		BackwardElement = BackwardElement->GetPrev();
	}
}

template<class T>
void LAlgo::QuickSortAlgo(TArray<T>& Array, int FirstIndex, int LastIndex, DSortComparsion LeftComparsion, DSortComparsion RightComparsion)
{
	if (FirstIndex < LastIndex)
	{
		int PartitionIndex = LAlgo::Partition(Array, FirstIndex, LastIndex, LeftComparsion, RightComparsion);
		LAlgo::QuickSortAlgo(Array, FirstIndex, PartitionIndex - 1, LeftComparsion, RightComparsion);
		LAlgo::QuickSortAlgo(Array, PartitionIndex + 1, LastIndex, LeftComparsion, RightComparsion);
	}
}

template<class T>
int LAlgo::Partition(TArray<T>& Array, int FirstIndex, int LastIndex, DSortComparsion LeftComparsion, DSortComparsion RightComparsion)
{
	int Pivot = Array[(FirstIndex + LastIndex) / 2];
	while (true)
	{
		while (LeftComparsion(Array[FirstIndex], Pivot))
		{
			++FirstIndex;
		}
		while (RightComparsion(Array[LastIndex], Pivot))
		{
			--LastIndex;
		}

		if (FirstIndex >= LastIndex)
		{
			return LastIndex;
		}

		LAlgo::Swap(Array[FirstIndex], Array[LastIndex]);
	}
}