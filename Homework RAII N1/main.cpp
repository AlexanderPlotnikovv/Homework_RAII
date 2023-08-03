#include <iostream>
#include <optional>
#include <exception>

class Exception : public std::exception
{
public:
	const char* what() { return "Error in array"; }
};

struct SmartArray
{
	int* arr;
	int size;
	SmartArray(int sizef)
	{
		arr = new int[sizef];
		size = sizef;
		for (int i = 0; i < size; i++)
		{
			arr[i] = -1;
		}
	}
	SmartArray()
	{
		arr = new int[1];
		size = 1;
		arr[0] = -1;
	}
	SmartArray(const SmartArray& array)
	{
		size = array.size;
		arr = new int[size];
		for (int i = 0; i < size; i++)
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
		int k = 0;
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == -1)
			{
				k = 1;
				arr[i] = a;
				break;
			}
		}
		if (k == 1) {}
		else
		{
			int* arr1 = new int[size + 1];
			for (int i = 0; i < size + 1; i++)
			{
				arr1[i] = arr[i];
			}
			arr = new int[size + 1];
			for (int i = 0; i < size + 1; i++)
			{
				arr[i] = arr1[i];
			}
			size++;
			arr[size - 1] = a;
			delete[]arr1;
		}
	}
	friend std::istream& operator>> (std::istream& cin, const SmartArray& array)
	{
		for (int i = 0; i < array.size; i++)
		{
			cin >> array.arr[i];
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
	~SmartArray()
	{
		delete[]arr;
	}
};

int main()
{
	int size;
	std::cin >> size;
	try
	{
		SmartArray arr(size);
		std::cin >> arr;
		std::cout << arr << std::endl;
		std::cout << arr.get_element(2);
		std::cout << std::endl;
		arr.add_element(15);
		std::cout << arr << std::endl;
		SmartArray array = arr;
		std::cout << array << std::endl;
	}
	catch (Exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	return 0;
}