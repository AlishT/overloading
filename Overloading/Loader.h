#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include "Matrix.h"

template<typename T>

using DynamicArray = std::vector<T>;
using String = std::string;

class Loader
{
protected:
	mutable DynamicArray<String> cachedData;

public:
	virtual const DynamicArray<String>& load() const = 0;
	
	const DynamicArray<String>& getLastLoadedData() const
	{
		return cachedData;
	}
	virtual void print() const = 0;
};

template<typename T>
class ConsoleLoader : public Loader
{
public:

	const DynamicArray<String>& load() const override
	{
		String line;
		cachedData.clear();
		
		std::cout << "Enter consol string: ";
		while (true)
		{
			std::getline(std::cin, line);
			cachedData.push_back(line);

			if (line.empty()) 
			{
				break;
			}
		}
		
		return cachedData;

	}

	void print() const
	{
		std::cout << "Consol string: ";
		for (int i = 0; i < cachedData.size(); i++) 
		{
			std::cout << cachedData[i] << std::endl;
		}
	};
};

template<typename T>
class FileLoader : public Loader
{
public:
	String filePath;

	const DynamicArray<String>& load() const override
	{
		String line;
		if (filePath.empty())
		{
			std::cout << "No file path specified." << std::endl;
			return cachedData;
		}
		
		std::fstream fs;

		fs.open(filePath, std::fstream::in);

		if (!fs.is_open()) 
		{
			std::cout << "File not found." << std::endl;
		}
		else 
		{
			cachedData.clear();
			
			while (true)
			{
				getline(fs, line);
				cachedData.push_back(line);
				
				if (fs.eof()) 
				{ 
					break; 
				}
			}
		}
	
		fs.close();

		return cachedData;
	}

	void print() const
	{
		std::cout << "File string: " << std::endl;
		for (int i = 0; i < cachedData.size(); i++)
		{
			std::cout << cachedData[i] << "\t";
		}
		std::cout << std::endl;
		
	};
};