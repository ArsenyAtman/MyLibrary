#pragma once

#include "Source/Array.h"

class Algo
{
public:

	template<class T>
	static void Swap(T& Value1, T& Value2);

	template<class T>
	static int LinearSearch(const TArray<T>& Array, const T& ElementToFind);
};
