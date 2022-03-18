#pragma once

#include "Array.h"

class LAlgo
{
public:

	template<class T>
	static void Swap(T& Value1, T& Value2);

	template<class T>
	static int LinearSearch(const TArray<T>& Array, const T& ElementToFind);
};

template<class T>
void LAlgo::Swap(T& Value1, T& Value2)
{
	T Buff = Value1;
	Value1 = Value2;
	Value2 = Buff;
}

template<class T>
int LAlgo::LinearSearch(const TArray<T>& Array, const T& ElementToFind)
{
	for (int i = Array.GetLength() - 1; i >= 0; --i)
	{
		if (Array[i] == ElementToFind)
		{
			return i;
		}
	}

	return -1;
}
