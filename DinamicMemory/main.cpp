#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T** arr, const int rows);

void FillRand(int arr[], const int n,int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n,int minRand = 0, int maxRand = 100);
void FillRand(char arr[], const int n);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);
template<typename T>void Print(T arr[], const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);
template<typename T>T* push_back(T arr[], int& n, T value);
template<typename T>T* push_front(T arr[], int& n, T value);
template<typename T>T* pop_back(T arr[], int& n);
template<typename T>T** push_row_back(T** arr,  int& rows, const int cols);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);
template<typename T>void push_col_back(T** arr,const int rows, int& cols);

template<typename T> 
T** pop_row_front(T** arr, int& rows, const int cols);
template<typename T> 
T** erase_row(T** arr, int& rows, const int cols, const int index);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	typedef double DataType;
	DataType* arr = new DataType[n];

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << &n << endl;
	arr = push_back(arr, n, value);
	Print(arr, n);
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);
    arr = pop_back(arr, n);
	Print(arr, n);
	delete[] arr;
#endif // DYNAMIC_MEMORY_1
#ifdef DYNAMIC_MEMORY_2
	typedef double DataType;
	int rows;
	int cols;
	int index;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строк: "; cin >> cols;	
	DataType** arr = Allocate<DataType>(rows, cols);
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100,1000);
	Print(arr, rows, cols);
	arr=pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	push_col_back(arr,rows,cols);
	Print(arr, rows, cols);
	arr = pop_row_front(arr, rows, cols);
	Print(arr, rows, cols);
	cout << "Введите индекс аннигилирования строки "; cin >> index;
	arr = erase_row(arr, rows, cols, index);
	Print(arr, rows, cols);
	Clear(arr, rows);
#endif
}
template<typename T>
T** Allocate(const int rows, const int cols)
{
	//1) создаем массив указателей
	T** arr = new T* [rows];
	//2) выделяем память под строки
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols] {};
	}
	return arr;
}
template<typename T>void Clear(T** arr, const int rows)
{
	//3)Сначала удаляем строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//4) удаляем массив указателей
	delete[] arr;
}
void FillRand(int arr[], const int n,int minRand,int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		//обращение к элементам через арифметику указателей
		//и оператор разыменования:
		*(arr + i) = rand() % (maxRand - minRand) + minRand;

	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		//обращение к элементам через арифметику указателей
		//и оператор разыменования:
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		*(arr + i) /= 100;
	}
}void FillRand(char arr[], const int n)
{
	
	for (int i = 0; i < n; i++)
	{
		//обращение к элементам через арифметику указателей
		//и оператор разыменования:
		*(arr + i) = rand();
		
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}

	}
}void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 10000;
			arr[i][j] /= 100;
		}

	}
}
template<typename T>
void Print(T arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		//обращение к элементам через оператор индексирования -[];
		cout << arr[i] << tab;

	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << endl;
}
template<typename T>T* push_back(T arr[], int& n, T value)
{
	//1)Создаем буферный массив нужного размера
	T* buffer = new T[n + 1];
	//2)Копируем значемя из исходного массива в буферный
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) Удаляем исходный массив
	delete[] arr;
	//4) Подменяем адрес исходного массива адресом нового массива
	arr = buffer;
	//5 Только после этого в конце массива появляется свободное место
	//куда можно добавить значение
	arr[n] = value;
	n++;
	//Print(arr, n);
	return arr;
}
template<typename T>
T* push_front(T arr[], int& n, T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}
template<typename T>
T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template<typename T>
T** push_row_back(T** arr,  int& rows, const int cols)
{
	return push_back(arr, rows, new T[cols]{});
	////1) создаем буферный массив указателей нужного размера
	//T** buffer = new T* [rows+1];

	////Копируем строки из исходного массивав массив указателей
	//for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	////удаляем исходный массив указателей
	//delete[] arr;
	////создаем строку и добавляем ее в массив
	//buffer[rows] = new T[cols] {};
	////После добавления строки в массив колличество его строк увеличивается
	//rows++;
	//return buffer;
}
template<typename T>
T** pop_row_back(T** arr, int& rows, const int cols)
{

	delete[] arr[rows-1];
	return pop_back(arr,rows);
	/*T** buffer = new T* [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	return buffer;*/
}
template<typename T>
void push_col_back(T** arr, const int rows, int& cols)
{
	
	
		for (int i = 0; i < rows; i++)
		{
			arr[i] = push_back(arr[i], cols, T());
			cols--;
		}
		cols++;
	//	//создаем буферную строку
	//	T* buffer = new T[cols + 1] {};
	//	//копируем значения из  исходной строки в буферную
	//	for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
	//	//удаляем исходную строку
	//	delete[] arr[i];
	//	//подменяем адрес строки в массиве указателей
	//	arr[i] = buffer;	
	//}
	//	cols++;
}
template<typename T> T** pop_row_front(T** arr, int& rows, const int cols)
{
	T** buffer = new T * [--rows] {};
	for (int i = 0; i < rows; i++) buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}
template<typename T> T** erase_row(T** arr, int& rows, const int cols, const int index)
{
	T** buffer = new T*[--rows] {};
	for (int i = 0, temp = 0; i < rows; i++)
	{
		if (i == index)temp++;
		buffer[i] = arr[i + temp];
	}
	delete[] arr;
	return buffer;
}
