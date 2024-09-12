#pragma once

#include <iostream>
#include <string>
#include <fstream>

class BaseException : public std::exception
{
protected:
	std::string text;
public:
	virtual std::string what() = 0;
};

class ArithmeticException : public BaseException
{
public:
	ArithmeticException()
	{
		text = "Error. ArithmeticExeption";
	}

	ArithmeticException(std::string _text) 
	{
		text = _text;
	}

	std::string what() 
	{
		return text;
	}
};

class DivisionByZero final : public ArithmeticException
{
public:


	DivisionByZero() : ArithmeticException()
	{
		text = "Divide by zero.";
	}

	DivisionByZero(std::string _text) : ArithmeticException(_text)
	{
	}

	std::string what() 
	{
		return text;
	}
};

class MatricesSizeNotEqual final : BaseException 
{
public:

	MatricesSizeNotEqual(std::string _text = "Error: matrices are not equal.")
	{
		text = _text;
	}

	std::string what() 
	{
		return text;
	}
};

class MemoryAllocationFailed final : BaseException
{
public:

	MemoryAllocationFailed(std::string _text = "Memory allocation failed")
	{
		text = _text;
	}

	std::string what()
	{
		return text;
	}
};

