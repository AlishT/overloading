#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include "Loader.h"
#include "Sorter.h"
#include "Matrix.h"

template<typename T>
using DynamicArray = std::vector<T>;


template<typename T> 
class Container 
{
private:
	DynamicArray<T> dataTable;
	
public:

	void readFromLoader(const Loader& loader)
	{
		dataTable = loader.load();
	}

	DynamicArray<T> getSorted(const Sorter<T>& sorter)
	{
		dataTable = sorter.sortAndGet(dataTable);
		return dataTable;
	}


	T getFirstItem()

	{
		DynamicArray<String>::iterator it = dataTable.begin();
		return *it;
	}

	T goNextItem(int nextItem)
	{
		DynamicArray<String>::iterator it = dataTable.begin() + nextItem;
		return *it;
	}

	void addItem(T& item) 
	{
		dataTable.push_back(item);
	}

	const T& operator [](std::size_t idx) const 
	{
		return dataTable[idx];
	}

	void deleteItem(int deleteElement)
	{
		DynamicArray<String>::iterator it = dataTable.begin() + deleteElement;
		dataTable.erase(it);
		
	}

	void printItemList()
	{

		for (auto it : dataTable)
		{
			std::cout << "Item list: " << it << std::endl;
		}
	}

	using Operation = std::function<T(T, T)>;

	T calculate(DynamicArray<String>& math)
	{
		int n = dataTable.size();
		if (dataTable.empty()) 
		{
			return {};
		}
		if (n == 1)
		{
			return dataTable.front();
		}
		if (math.size() != n - 1)
		{
			return dataTable[0];
		}	
		T result = dataTable[0];

		static std::map<String, Operation> operations{
			{"+", std::plus<T>()},
			{"-", std::minus<T>()},
			{"*", std::multiplies<T>()}
		};
		for (int i = 0; i < math.size(); i++)
		{
			String mathOperator = math[i];
			
			if (operations.contains(mathOperator))
			{
				result = operations[mathOperator](result, dataTable[i + 1]);
				
				std::cout << "test " << mathOperator << std::endl;
				
			}
			else
			{
				std::cout << "Wrong math operator." << std::endl;
			}
		}

		return result;
		
	}
};


