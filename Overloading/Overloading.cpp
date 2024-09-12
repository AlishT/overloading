
#include <iostream>
#include <string>
#include <vector>

#include "Matrix.h"
#include "Loader.h"
#include "Sorter.h"
#include "Container.h"

using namespace std;

int main()
{
    int mColumn;
    int mRow;

    cout << "Enter column: ";
    cin >> mColumn;
    cout << "Enter row: ";
    cin >> mRow;
    if (mColumn < 1)
    {
        mColumn = 1;
        cout << "Column must be > 0, column " << mColumn << endl;
    }
    if (mRow < 1)
    {
        mRow = 1;
        cout << "Row must be > 0, column = " << mRow << endl;
    }
  
    Matrix<int> matr(mColumn, mRow);
    matr.setMartrix();
    Matrix<int> copyMatrix(matr);

    Matrix<int> matr1(mColumn, mRow);
    matr1.setMartrix();

    Matrix<int> matr2(mColumn, mRow);
    matr2.setMartrix();
    
    try
    {
        Matrix<int> sumMatr = matr + matr1;

        string valueStr = "123";
        Matrix<int> sumMatr2 = matr + matr1 + valueStr + 22 + matr2;

        Matrix<int> minusMatr = matr - matr1;

        Matrix<int> multiplication = matr * matr1;

        matr += matr;
        matr += 345;

        cout << "Sum Matrix: " << sumMatr.convertToString() << endl;
        cout << "Sum Matrix2: " << sumMatr2.convertToString() << endl;
        cout << "Multiplication: " << multiplication.convertToString() << endl;
        cout << "minus: " << minusMatr.convertToString() << endl;

        matr.convertToString();
        copyMatrix.convertToString();
        

        cout << "String: " << matr.convertToString() << endl;

        multiplication = multiplication / 0;      
        
    }
    catch(MatricesSizeNotEqual ex1)
    {
        cout << ex1.what() << endl;
    }
    catch(DivisionByZero ex2)
    {
        cout << ex2.what() << endl;
    }
    catch(MemoryAllocationFailed ex3)
    {
        cout << ex3.what() << endl;
    }
    
    int value = 0;
    Matrix<int> valueData(mColumn, mRow, value);

    int** dataSrc;
    dataSrc = new int* [mColumn];
    for (int i = 0; i < mColumn; i++)
    {
        dataSrc[i] = new int[mRow];
    }
    
    string str = "[1, 57; 3, 43]";
    Matrix<int> charMatrix(str.c_str());
    
    //Loader
    FileLoader<string> loadFile;
    loadFile.filePath = "ReadMatrix.txt";
    loadFile.load();
    loadFile.print();

    ConsoleLoader<string> consol;
    consol.load();
    consol.print();


    //quickSort
    DynamicArray<int> vector = { 53,45,1,48,4,7,3 };
    cout << "Vector: " << endl;
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << endl;
    }
    QuickSort<int> qSort;
    qSort.sortAndGet(vector);

    UsualSort<string> sorter;

    cout << "Sort: " << endl;
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i] << endl;
    }

    //Iterator
    Container<std::string> dataTable;
    dataTable.readFromLoader(loadFile);
    dataTable.getFirstItem();
    dataTable.goNextItem(3);
    dataTable.printItemList();
    dataTable.addItem("50");
    dataTable.deleteItem(0);
    dataTable.deleteItem(3);
    dataTable.deleteItem(4);
    dataTable.addItem("10");
    dataTable.addItem("17");
    dataTable.getSorted(sorter);
    dataTable.printItemList();
  
    //Templates, SmartPtrs, Functors

    FileLoader<string> loadString;
    loadString.filePath = "StringArray.txt";
    DynamicArray<string> stringArray = loadString.load();

    Container<Matrix<int>> matrices;
 
    for (auto s: stringArray)
    {
        Matrix<int> matrix(s.c_str());
        matrices.addItem(matrix);
    }

    loadString.filePath = "MathFile.txt";
    DynamicArray<string> mathOperators = loadString.load();

    matrices.calculate(mathOperators);
   
    
    delete[] dataSrc;
    dataSrc = nullptr;
}

