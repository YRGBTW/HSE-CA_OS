#include <iostream>
#include <windows.h>
#include <excpt.h>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;
float D = 1.0f, E = 0.0f, F;

//������� ��� �������� ������� �� ����
void DZ_FLT_Flag(float a, float b)
{
	if (b == 0.0f)
	{
		RaiseException(EXCEPTION_FLT_DIVIDE_BY_ZERO, 0, 0, nullptr);//����� ����������
	}
}
//������� �� ���� � ��������� � ������� ���������� ������� VS
void zero_flt_trycatch()
{
	try
	{
		throw runtime_error ("������� �� ����");
	}
	catch (exception e)
	{
		cout << "���������� ���������� - " << e.what() << endl; //����� ����������
	}
}
//������� �� ���� � ��������� � ������� SEH
void zero_flt_tryexcept()
{
	__try
	{
		DZ_FLT_Flag(F, E);
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "���������� ���������� - " << GetExceptionCode() << endl;
	}
}
//������
int SEHFilter_flt(DWORD exception)
{
	cout << "Exception caught." << endl;
	switch (exception)
	{
		cout << "�������� ����������. ������." << endl;
		switch (exception)//������� �� ���� ����������
		{
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: // ���� ������� �� 0
			cout << "������� �� ����." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_FLT_OVERFLOW: // ���� ������������
			cout << "������������." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_FLT_DENORMAL_OPERAND: // ���� ��������������
			cout << "����������������� �����." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		default:// � ����������� ������
			cout << "����������� ������." << endl;
			return EXCEPTION_CONTINUE_SEARCH;
		}
	}
}

//������� �� ���� � ��������� � ������� SEH � �������
void zero_flt_filter()
{
	__try
	{
		DZ_FLT_Flag(F, E);
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "���������� ���������� - ������� �� ���� � ������� �������" << endl; // ����� ����������
	};
}

//�������� �� ������������
void OF_FLT_Flag(float a, float b)
{
	if (a == FLT_MAX && b > 0 || b == FLT_MAX && a > 0)//�������
	{
		RaiseException(EXCEPTION_FLT_OVERFLOW, 0, 0, nullptr);//����� ����������
	}
}

//����� ���������� ������������ � ��������� � ������� ���������� ������� VS
void main_overflow_flt_trycatch()
{
	try
	{
		throw overflow_error("������������ float"); //����� ���������� � ���������� �����
	}
	catch (overflow_error& e)
	{
		cout << "���������� ���������� - " << e.what() << endl;  //���������
	}
}
//����� ������� ������������ � ��������� � ������� SEH
void main_overflow_flt_tryexcepetion()
{
	__try
	{
		OF_FLT_Flag(FLT_MAX, 1.0f);//����� ���������� � ���������� ������ � ������� �������
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_OVERFLOW ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)//���������, ��� ������� ���� ���������� ������������� ���������� ���� - ����������� ������ ���������
	{
		cout << "���������� ���������� - " << GetExceptionCode() << endl;
	}
}
//����� ������� ������������ � ��������� � ������� SEH � �������
void main_overflow_flt_filter()
{
	__try
	{
		OF_FLT_Flag(FLT_MAX, 1.0f);//����� ���������� � ���������� ������ � ������� �������
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "���������� ���������� - ������������ � ������� �������" << endl;
	};//��������� � ������� �������
}

void Denormal_flag(float a)
{
	if (fpclassify(a) == FP_SUBNORMAL) { // ��������, �������� �� ����� �����������������
		RaiseException(EXCEPTION_FLT_DENORMAL_OPERAND, 0, 0, nullptr); //����� ����������
	}
}

//����������������� ����� � ��������� � ������� ���������� ������� VS
void denormalized_trycatch()
{
	try
	{
		throw exception("����������������� �����");//����� ���������� � ���������� �����
	}
	catch (exception& e)
	{
		cout << "���������� ���������� - " << e.what() << endl; //����� ����������
	}
}
//������������� SEH
void denormalized_tryexcepetion()
{
	__try
	{
		Denormal_flag(1.0e-40f);//����� ���������� � ���������� ������ � ������� �������
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_DENORMAL_OPERAND ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "���������� ���������� - " << GetExceptionCode() << endl;
	}
}
//������������� SEH � ������� 
void denormalized_filter()
{
	__try
	{
		Denormal_flag(1.0e-40f);//����� ���������� � ���������� ������ � ������� �������
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "���������� ���������� - ����������������� ����� � ������� �������" << endl; //����� ����������
	};
}

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//
//	zero_flt_trycatch();
//	zero_flt_tryexcept();
//	zero_flt_filter();
//
//	system("pause");
//
//	main_overflow_flt_trycatch();
//	main_overflow_flt_tryexcepetion();
//	main_overflow_flt_filter();
//
//	system("pause");
//
//	denormalized_trycatch();
//	denormalized_tryexcepetion();
//	denormalized_filter();
//
//	system("pause");
//
//}