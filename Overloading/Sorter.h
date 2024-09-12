#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include "Matrix.h" 


template<typename T>

class Sorter
{
public:
	using PredicateType = std::function<bool(const T& left, const T& right)>;

	virtual DynamicArray<T> sortAndGet(DynamicArray<T>& dataToSort) const = 0;
	
	virtual DynamicArray<T> sortWithPredicate(DynamicArray<T>& dataSort,
		 PredicateType& predicate) const = 0;

};

template<typename T>

class QuickSort : public Sorter<T>
{
public:
	Sorter<T>::PredicateType predicateType = [](int a, int b) -> bool
	{
		return a > b;
	};

	DynamicArray<T> sorting(DynamicArray<T>& dataToSort, T left, T right) const
	{
		if (left < right)
		{
			int pivot = right;
			for (int i = right - 1; i >= left; i--)
			{
				if (dataToSort[i] > dataToSort[pivot])
				{
					int temp = dataToSort[pivot];
					dataToSort[pivot] = dataToSort[i];
					dataToSort[i] = dataToSort[pivot - 1];
					dataToSort[pivot - 1] = temp;
					pivot--;
				}
			}
			sorting(dataToSort, left, pivot - 1);
			sorting(dataToSort, pivot + 1, right);
		}
		return dataToSort;
	}

	DynamicArray<T> sortingWithPredicate(DynamicArray<T>& dataToSort, T left, T right, Sorter<T>::PredicateType& predicate) const
	{
		/*predicate = [](int a, int b) -> bool
		{
			return a > b;
		};*/

		predicate = predicateType;
		
		if (left < right)
		{
			int pivot = right;
			for (int i = right - 1; i >= left; i--)
			{
				if (predicate(dataToSort[i], dataToSort[pivot]))
				{
					int temp = dataToSort[pivot];
					dataToSort[pivot] = dataToSort[i];
					dataToSort[i] = dataToSort[pivot - 1];
					dataToSort[pivot - 1] = temp;
					pivot--;
				}
			}
			sorting(dataToSort, left, pivot - 1);
			sorting(dataToSort, pivot + 1, right);
		}
		return dataToSort;
	}

	DynamicArray<T> sortAndGet(DynamicArray<T>& dataToSort) const override
	{
		return sorting(dataToSort, 0, dataToSort.size() - 1);
	}

	DynamicArray<T> sortWithPredicate(DynamicArray<T>& dataSort,
		 Sorter<T>::PredicateType& predicate) const override
	{
		return sortingWithPredicate(dataSort, 0, dataSort.size() - 1, predicate);
	}

};

template<typename T>
class UsualSort : public Sorter<T>
{
public:
	DynamicArray<T> sortAndGet(DynamicArray<T>& dataToSort) const override
	{
		std::sort(dataToSort.begin(), dataToSort.end());
		return dataToSort;
	}

	DynamicArray<T> sortWithPredicate(DynamicArray<T>& dataSort, 
		 Sorter<T>::PredicateType& predicate) const override 
	{
		std::sort(dataSort.begin(), dataSort.end(), predicate);
		return dataSort;
	}
};
