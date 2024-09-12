#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <limits>
#include <cstddef>
#include <memory>
#include "Matrix.h"
#include "MyExceptions.h"

template<typename T>

class Matrix
{
private:
    T* matArray;
    int columns;
    int rows;
    int count = 1;
public:

    Matrix()= default;

    Matrix(int _columns, int _rows);

    Matrix(int _columns, int _rows, T value);

    Matrix(const Matrix<T>& matrix);

    Matrix<T>& operator = (Matrix<T>& other);

    Matrix<T>& operator = (Matrix<T>&& other) noexcept;
  
    Matrix(const char* dataStr);

    ~Matrix();

    void setMartrix();

    std::string convertToString() const;

    template<typename T> friend Matrix<T> operator + (Matrix<T> matrix, const Matrix<T>& other);
    template<typename T> friend Matrix<T> operator - (Matrix<T> matrix, const Matrix<T>& other);
    template<typename T> friend Matrix<T> operator * (Matrix<T> matrix, const Matrix<T>& other);

    Matrix<T>& operator += (const Matrix<T>& other);
    template<typename T> friend Matrix<T> operator += (const Matrix<T>& other, T value);
    Matrix<T>& operator -= (const Matrix<T>& other);
    Matrix<T>& operator *= (const Matrix<T>& other);
   

    template<typename T> friend Matrix<T> operator + (const Matrix<T>& other, const std::string& valueStr);
    template<typename T> friend Matrix<T> operator + (Matrix<T> other, T value);
    template<typename T> friend Matrix<T> operator - (const Matrix<T>& other, const std::string& valueStr);
    template<typename T> friend Matrix<T> operator - (Matrix<T> other, T value);
    template<typename T> friend Matrix<T> operator * (const Matrix& other, const std::string& valueStr);
    template<typename T> friend Matrix<T> operator * (Matrix<T> other, T value);
    template<typename T> friend Matrix<T> operator / (const Matrix<T>& other, const std::string& valueStr);
    template<typename T> friend Matrix<T> operator / (Matrix<T> other, T value);

    template<typename T> 
    friend inline bool operator < (const Matrix<T>& matrix, const Matrix<T>& other);
    template<typename T>
    friend inline bool operator > (const Matrix<T>& matrix, const Matrix<T>& other);
    template<typename T>
    friend inline bool operator <= (const Matrix<T>& matrix, const Matrix<T>& other);
    template<typename T>
    friend inline bool operator >= (const Matrix<T>& matrix, const Matrix<T>& other);
    
    template<typename T> 
    friend inline bool operator == (const Matrix<T>& matrix, const Matrix<T>& other);
    template<typename T>
    friend inline bool operator != (const Matrix<T>& matrix, const Matrix<T>& other);
};

template<typename T>
Matrix<T> operator + (Matrix<T> matrix, const Matrix<T>& other);
template<typename T>
Matrix<T> operator - (Matrix<T> matrix, const Matrix<T>& other);
template<typename T>
Matrix<T> operator * (Matrix<T>matrix, const Matrix<T>& other);

template<typename T>
Matrix<T> operator += (const Matrix<T>& other, T value);

template<typename T>
Matrix<T> operator + (Matrix<T> other, T value);
template<typename T>
Matrix<T>operator + (const Matrix<T>& other, const std::string& valueStr);

template<typename T>
Matrix<T> operator - (Matrix<T> other, T value);
template<typename T>
Matrix<T> operator - (const Matrix<T>& other, const std::string& valueStr);

template<typename T>
Matrix<T> operator * (Matrix<T> other, T value);
template<typename T>
Matrix<T> operator * (const Matrix<T>& other, const std::string& valueStr);

template<typename T>
Matrix<T> operator / (Matrix<T>other, T value);
template<typename T>
Matrix<T> operator / (const Matrix<T>& other, const std::string& valueStr);

template<typename T>
inline bool operator < (const Matrix<T>& matrix, const Matrix<T>& other);
template<typename T>
inline bool operator > (const Matrix<T>& matrix, const Matrix<T>& other);
template<typename T>
inline bool operator <= (const Matrix<T>& matrix, const Matrix<T>& other);
template<typename T>
inline bool operator >= (const Matrix<T>& matrix, const Matrix<T>& other);

template<typename T>
inline bool operator == (const Matrix<T>& matrix, const Matrix<T>& other);
template<typename T>
inline bool operator != (const Matrix<T>& matrix, const Matrix<T>& other);

template<typename T>
bool checkSumOverflow(T a, T b);
template<typename T> 
bool checkSubtractionOverflow(T a, T b);

template <typename T> 
T convertStringToNumber(std::string str);

template<typename T>
Matrix<T> operator + (Matrix<T> matrix, const Matrix<T>& other)
{
    return matrix += other;
}

template<typename T>
Matrix<T> operator - (Matrix<T> matrix, const Matrix<T>& other)
{
    return matrix -= other;
}

template<typename T>
Matrix<T> operator * (Matrix<T> matrix, const Matrix<T>& other)
{
    return matrix *= other;
}

template<typename T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& other)
{
    if (columns != other.columns && rows != other.rows) 
    {
        throw MatricesSizeNotEqual();
    }
    std::cout << " + " << std::endl;
    if (columns == other.columns && rows == other.rows)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (checkSumOverflow(matArray[i * columns + j], other.matArray[i * other.columns + j]))
                {
                    std::cout << "Overflow!" << std::endl;
                    matArray[i * other.columns + j] = 0;
                }
                else 
                { 
                    matArray[i * columns + j] += other.matArray[i * other.columns + j];
                }

            }
        }
        return *this;
    }
    return *this;
}

template<typename T>
Matrix<T> operator += (const Matrix<T>& other, T value)
{
    
    for (int i = 0; i < other.rows; i++)
    {
        for (int j = 0; j < other.columns; j++)
        {
            if (checkSumOverflow(other.matArray[i * other.columns + j], value))
            {
                std::cout << "Overflow!" << std::endl;
                other.matArray[i * other.columns + j] = 0;
            }
            else
            {
                other.matArray[i * other.columns + j] += value;
            }
           
        }
    }
    return other;
}

template<typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& other)
{

    if (columns != other.columns && rows != other.rows)
    {
        throw MatricesSizeNotEqual();
    }
    std::cout << " - " << std::endl;
    if (columns == other.columns && rows == other.rows)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (checkSubtractionOverflow(matArray[i * columns + j], other.matArray[i * columns + j]))
                {
                    std::cout << "Overflow!" << std::endl;
                    matArray[i * columns + j] = 0;
                }
                else
                {
                    matArray[i * columns + j] -= other.matArray[i * columns + j];
                }
            }
        }
        return *this;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& other)
{

    if (!(columns == other.rows))
    {
       throw MatricesSizeNotEqual();
    }
    
    if (columns == other.rows)
    {
        for (int i = 0; i < rows; i++)
        {
            
            for (int j = 0; j < other.columns; j++)
            {
                int sumMult = 0;
                for (int k = 0; k < columns; k++)
                {
                    sumMult += matArray[i * columns + k] * other.matArray[k * other.columns + j];
                }
                matArray[i * columns + j] = sumMult;
                
            }
        }
        return *this;
    }
    return *this;
}


/*
Matrix operator [+,-,*,/] (const Matrix& matrix, std::string strValue)
{
    int value = stoi(strValue);
    return matrix [+,-,*,/] value;
}
*/

template<typename T>
Matrix<T> operator + (Matrix<T>other, T value)
{

    return other += value;
}

template<typename T>
Matrix<T> operator + (const Matrix<T>& other, const std::string& valueStr)
{

    int value = convertStringToNumber<T>(valueStr);
    return other + value;
}

template<typename T>
Matrix<T> operator - (const Matrix<T>& other, const std::string& valueStr)
{
    int value = convertStringToNumber<T>(valueStr);
    
    return other - value;
}

template<typename T>
Matrix<T> operator - (Matrix<T> other, T value)
{   
    return other - value;
}

template<typename T>
Matrix<T> operator * (const Matrix<T>& other, const std::string& valueStr)
{

    int value = convertStringToNumber<T>(valueStr);
    return other * value;
}

template<typename T>
Matrix<T> operator * (Matrix<T> other, T value)
{
    return other * value;
}

template<typename T>
Matrix<T> operator / (const Matrix<T>& other, const std::string& valueStr)
{
    
    int value = convertStringToNumber<T>(valueStr);
    
    if (value == 0) 
    {
        throw DivisionByZero();
    }

    return other / value;
}

template<typename T>
Matrix<T> operator / (Matrix<T> other, T value)
{
    if (value == 0)
    {
        throw DivisionByZero();
    }
    return other / value;
}

template<typename T>
inline bool operator < (const Matrix<T>& matrix, const Matrix<T>& other)
{
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            sum1 += matrix.matArray[i * matrix.columns + j];
            sum2 += other.matArray[i * matrix.columns + j];
        }
    }

    return sum1 < sum2;
}

template<typename T>
inline bool operator > (const Matrix<T>& matrix, const Matrix<T>& other)
{
    return other < matrix;
}

template<typename T>
inline bool operator <= (const Matrix<T>& matrix, const Matrix<T>& other)
{
    return !(matrix > other);
}

template<typename T>
inline bool operator >= (const Matrix<T>& matrix, const Matrix<T>& other)
{
    return !(matrix < other);
}
   
template<typename T>
inline bool operator == (const Matrix<T>& matrix, const Matrix<T>& other)
{
    if (matrix.columns != other.columns || matrix.rows != other.rows)
    {
        return false;
    }
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            sum1 += matrix.matArray[i * matrix.columns + j];
            sum2 += other.matArray[i * matrix.columns + j];
        }
    }

    return sum1 == sum2;

}

template<typename T>
inline bool operator != (const Matrix<T>& matrix, const Matrix<T>& other)
{
    return !(matrix == other);
}

template<typename T>
Matrix<T>::Matrix(int _columns, int _rows) :
    columns(_columns),
    rows(_rows)
{
   
    this->matArray = new T[_rows * _columns];

    if (matArray == NULL) 
    {
        throw MemoryAllocationFailed();
    }
    
}

template<typename T>
Matrix<T>::Matrix(int _columns, int _rows, T value) :
    columns(_columns),
    rows(_rows)
{
    matArray = new T[_rows * _columns];

    if (matArray == NULL)
    {
        throw MemoryAllocationFailed();
    }
    
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            std::cout << "Enter element of Matrix2 " << count << ": ";
 
            matArray[i * _columns + j] = value;
        }
    }
    
}

template<typename T>
Matrix<T>::Matrix(const Matrix& matrix) :
    columns(matrix.columns),
    rows(matrix.rows)

{
    std::cout << "Copy constructor is working!" << std::endl;

    this->matArray = new T[matrix.rows * matrix.columns];
    std::cout << " obj " << std::endl;

    if (matArray == NULL)
    {
        throw MemoryAllocationFailed();
    }

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            matArray[i * columns + j] = matrix.matArray[i * matrix.columns + j];
            std::cout << " elem "<< count++ << std::endl;
        }
    }
      
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete matArray;

    memcpy(matArray, other.matArray, rows * columns * sizeof(int));
    columns = other.columns;
    rows = other.rows;

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    memcpy(matArray, other.matArray, rows * columns * sizeof(int));
    columns = other.columns;
    rows = other.rows;

    delete[] other.matArray;

    return *this;

}

template<typename T>
Matrix<T>::Matrix(const char* dataStr)
{
    char currentChar;
    int i = 0;
    int _columns = 0;
    int _rows = 0;
    int currentColumn = 0;
    int currentRow = 0;

    std::string currentNumber;

    while (currentChar = dataStr[i++])
    {
        _columns += (currentChar == ';' || currentChar == ',') && _rows == 0;
        _rows += currentChar == ';' || currentChar == ']';
    }
    if (_rows == 0 || _columns == 0) 
    {
        matArray = nullptr;
        return;
    }
    rows = _rows;
    columns = _columns;

    matArray = new T[rows * columns];

    i = 0;
    while (currentChar = dataStr[i++])
    {
        if (currentChar == '[')
        {
            currentNumber = "";
            continue;
        }
        if (currentChar == ' ')
        {
            continue;
        }
        if (currentChar == ',')
        {
            matArray[currentRow * columns + currentColumn] = convertStringToNumber<T>(currentNumber);
            currentNumber = "";
            currentColumn++;
            continue;
        }
        if (currentChar == ';' || currentChar == ']')
        {
            matArray[currentRow * columns + currentColumn] = convertStringToNumber<T>(currentNumber);
            currentNumber = "";
            currentColumn = 0;
            currentRow++;
            continue;
        }
        currentNumber += currentChar;
        
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << matArray[i * columns + j] << '\t';
        }
       // std::cout << std::endl;
    }
}

template<typename T>
Matrix<T>::~Matrix()
{
   
    std::cout << "Obj deleted." << std::endl;
    if (columns > 0 && rows > 0)
    {
        delete[] matArray;
    }
    matArray = nullptr;
    
}

template<typename T>
void Matrix<T>::setMartrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << "Enter element of Matrix " << count << ": ";
            std::cin >> matArray[i * columns + j];
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter just number: ";
                std::cin >> matArray[i * columns + j];
            }
            count++;
        }
    }
}

template<typename T>
std::string Matrix<T>::convertToString() const
{
    std::string str;
    str += "[";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            str += std::to_string(matArray[i * columns + j]);

            if (i < columns + 1)
            {
                str += ", ";
            }
        }

        if (i < rows + 1)
        {

            str += "; ";
        }
    }
    str += "]";
    return str;
}

template<typename T>
bool checkSumOverflow(T a, T b) 
{
    return (b > 0 && a > std::numeric_limits<T>::max() - b) || (b < 0 && a < std::numeric_limits<T>::min() - b);
}

template<typename T>
bool checkSubtractionOverflow(T a, T b)
{
    return  (b > 0 && a < std::numeric_limits<T>::min() + b) || (b < 0 && a > std::numeric_limits<T>::max() + b);
}

template <typename T> 
T convertStringToNumber(std::string str) 
{
    std::stringstream convert(str);
    T number;
    convert >> number;
    return number;
}

