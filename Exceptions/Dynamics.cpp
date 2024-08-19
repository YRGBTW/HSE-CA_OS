#include <iostream>
#include <windows.h>
#include <excpt.h>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

int* arr = new int[3];

// ������
int dynamic_filter(DWORD exception)
{
	cout << "�������� ����������. ������." << endl;
	switch (exception)
	{
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: //����� �� ������� �������
		cout << "����� �� ������� �������." << endl;
		return EXCEPTION_EXECUTE_HANDLER;
	case 3765269347: // �������� ������
		cout << "�������� ������." << endl;
		return EXCEPTION_EXECUTE_HANDLER;
	default:
		cout << "����������� ������." << endl;
		return EXCEPTION_CONTINUE_SEARCH;
	}
}


//������������� ������������ �����������
void bad_alloc_trycatch()
{
	try
	{
		int bigSize = 1000000000000000000;
		int* newArray = new int [bigSize];
	}
	catch (bad_alloc& e)
	{
		cout << "���������� ���������� - " << e.what() << endl;
	}
}
//������������� SEH
void bad_alloc_tryexcepetion()
{
	__try
	{
		int bigSize = 1000000000000000000;
		int* newArray = new int[bigSize];
	}
	__except (GetExceptionCode() == 3765269347 ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "���������� ���������� - " << GetExceptionCode() << endl;
	}
}
//������������� SEH � �������
void bad_alloc_filter()
{
	__try
	{
		int bigSize = 1000000000000000000;
		int* newArray = new int[bigSize];
	}
	__except (dynamic_filter(GetExceptionCode())) 
	{
		cout << "���������� ���������� - �������� ������ � ������� �������" << endl; //����� ����������
	};
}

//������� ��� �������� ������ �� ������� �������
void outofrange_arr_flag(int* arr, int value)
{
	if (sizeof(arr)<value || value < 0)
	{
		RaiseException(EXCEPTION_ARRAY_BOUNDS_EXCEEDED, 0,0, nullptr);//����� ����������
	}
}

//������������� ������������ �����������
void main_outofrange_trycatch()
{
	try
	{
		throw out_of_range("����� �� ������� �������");
	}
	catch (out_of_range& e)
	{
		cout << "���������� ���������� - " << e.what() << endl;
	}
}
//������������� SEH
void main_outofrange_tryexcepetion()
{
	__try
	{
		outofrange_arr_flag(arr,-1);
	}
	__except (GetExceptionCode() == EXCEPTION_ARRAY_BOUNDS_EXCEEDED ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "���������� ���������� - " << GetExceptionCode() << endl;
	}
}
//������������� SEH � �������
void main_outofrange_filter()
{
	__try
	{
		outofrange_arr_flag(arr, -1);
	}
	__except (dynamic_filter(GetExceptionCode())) 
	{
		cout << "���������� ���������� - ����� �� ������� ������� � ������� �������" << endl;
	};
}



int main()
{
	setlocale(LC_ALL, "Russian");

	bad_alloc_trycatch();
	bad_alloc_tryexcepetion();
	bad_alloc_filter();
	system("pause");

	main_outofrange_trycatch();
	main_outofrange_tryexcepetion();
	main_outofrange_filter();

}
