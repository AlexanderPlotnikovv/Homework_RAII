#include <iostream>
#include <exception>

class Exception : public std::exception
{
public:
	const char* what() { return "Error in array"; }
};

struct SmartArray
{
	int* arr;
	int capacity;
	int size;
	SmartArray(int sizef)
	{
		capacity = sizef;
		arr = new int[capacity];
		size = 0;
	}
	SmartArray()
	{
		arr = new int[1];
		capacity = 1;
		size = 0;
	}
	SmartArray(const SmartArray& array)
	{
		capacity = array.capacity;
		size = array.size;
		arr = new int[capacity];
		for (int i = 0; i < capacity; i++)
		{
			arr[i] = array.arr[i];
		}

	}
	int get_element(int i)
	{
		if (i >= size)
		{
			return -1;
		}
		else
		{
			return arr[i];
		}
	}
	
	void add_element(int a)
	{
		if (size < capacity)
		{
			arr[size] = a;
			size++;
		}
		else
		{
			int* arr1 = new int[size + 1];
			for (int i = 0; i < size + 1; i++)
			{
				arr1[i] = arr[i];
			}
			arr1[size] = a;
			size++;
			delete[]arr;
			arr = arr1;
			for (int i = 0; i != size; ++i)
			{
				arr[i] = arr1[i];
			}
			capacity++;
		}
	}
	friend std::istream& operator>> (std::istream& cin, SmartArray& array)
	{
		for (int i = 0; i < array.capacity; i++)
		{
			cin >> array.arr[i];
			array.size++;
		}
		return cin;
	}
	friend std::ostream& operator<< (std::ostream& cout, const SmartArray& array)
	{
		for (int i = 0; i < array.size; i++)
		{
			cout << array.arr[i] << " ";
		}
		return cout;
	}
	SmartArray& operator=(const SmartArray& array)
	{
		if (&array == this)
		{
			return *this;
		}
		else
		{
			capacity = array.capacity;
			size = array.size;
			for (int i = 0; i < size; i++)
			{
				arr[i] = array.arr[i];
			}
			return *this;
		}
	}
	~SmartArray()
	{
		delete[]arr;
	}
};

int main()
{
	int size;
	std::cout << "Enter size of array: ";
	std::cin >> size;
	try
	{
		SmartArray arr(size);
		std::cout << "Fill array. Warning! Program works correctly only if you fill array through std::cin: ";
		std::cin >> arr;
		std::cout << "Your array: " << arr << std::endl;
		std::cout << "Element with index 2: " << arr.get_element(2);
		std::cout << std::endl;
		std::cout << "Now we add element: 15" << std::endl;
		arr.add_element(15);
		std::cout << "Array now: ";
		std::cout << arr << std::endl;
		SmartArray array = arr;
		std::cout << "Output new array, filled through copying: ";
		std::cout << array << std::endl;
	}
	catch (Exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	return 0;
}