#include <iostream>
#include <windows.h>
#include <excpt.h>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;
float D = 1.0f, E = 0.0f, F;

//Функция для проверки деления на ноль
void DZ_FLT_Flag(float a, float b)
{
	if (b == 0.0f)
	{
		RaiseException(EXCEPTION_FLT_DIVIDE_BY_ZERO, 0, 0, nullptr);//Вызов исключения
	}
}
//Деление на ноль и обработка с помощью встроенных средств VS
void zero_flt_trycatch()
{
	try
	{
		throw runtime_error ("Деление на ноль");
	}
	catch (exception e)
	{
		cout << "Обработано исключение - " << e.what() << endl; //Вывод информации
	}
}
//Деление на ноль и обработка с помощью SEH
void zero_flt_tryexcept()
{
	__try
	{
		DZ_FLT_Flag(F, E);
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Обработано исключение - " << GetExceptionCode() << endl;
	}
}
//Фильтр
int SEHFilter_flt(DWORD exception)
{
	cout << "Exception caught." << endl;
	switch (exception)
	{
		cout << "Возникло исключение. Фильтр." << endl;
		switch (exception)//Переход по типу исключения
		{
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: // Если деление на 0
			cout << "Деление на ноль." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_FLT_OVERFLOW: // Если переполнение
			cout << "Переполнение." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		case EXCEPTION_FLT_DENORMAL_OPERAND: // Если денормализация
			cout << "Ненормализованное число." << endl;
			return EXCEPTION_EXECUTE_HANDLER;
		default:// В неизвестном случае
			cout << "Неизвестная ошибка." << endl;
			return EXCEPTION_CONTINUE_SEARCH;
		}
	}
}

//Деление на ноль и обработка с помощью SEH и фильтра
void zero_flt_filter()
{
	__try
	{
		DZ_FLT_Flag(F, E);
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "Обработано исключение - деление на ноль с помощью фильтра" << endl; // Вывод информации
	};
}

//Проверка на переполнение
void OF_FLT_Flag(float a, float b)
{
	if (a == FLT_MAX && b > 0 || b == FLT_MAX && a > 0)//условие
	{
		RaiseException(EXCEPTION_FLT_OVERFLOW, 0, 0, nullptr);//Вызов исключения
	}
}

//Вызов исключения переполнения и обработка с помощью встроенных средств VS
void main_overflow_flt_trycatch()
{
	try
	{
		throw overflow_error("Переполнение float"); //Вызов исключения в защищенном блоке
	}
	catch (overflow_error& e)
	{
		cout << "Обработано исключение - " << e.what() << endl;  //Обработка
	}
}
//Вызов функции переполнения и обработка с помощью SEH
void main_overflow_flt_tryexcepetion()
{
	__try
	{
		OF_FLT_Flag(FLT_MAX, 1.0f);//Вызов исключения в защищенном блокет с помощью функции
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_OVERFLOW ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)//Обработка, при которой если исключение соответствует ожидаемому типу - продолжится работа программы
	{
		cout << "Обработано исключение - " << GetExceptionCode() << endl;
	}
}
//Вызов функции переполнения и обработка с помощью SEH и фильтра
void main_overflow_flt_filter()
{
	__try
	{
		OF_FLT_Flag(FLT_MAX, 1.0f);//Вызов исключения в защищенном блокет с помощью функции
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "Обработано исключение - переполнение с помощью фильтра" << endl;
	};//Обработка с помощью фильтра
}

void Denormal_flag(float a)
{
	if (fpclassify(a) == FP_SUBNORMAL) { // проверка, является ли число ненормализованным
		RaiseException(EXCEPTION_FLT_DENORMAL_OPERAND, 0, 0, nullptr); //вызов исключения
	}
}

//Ненормализованное число и обработка с помощью встроенных средств VS
void denormalized_trycatch()
{
	try
	{
		throw exception("Денормализованное число");//Вызов исключения в защищенном блоке
	}
	catch (exception& e)
	{
		cout << "Обработано исключение - " << e.what() << endl; //Вывод информации
	}
}
//Использование SEH
void denormalized_tryexcepetion()
{
	__try
	{
		Denormal_flag(1.0e-40f);//Вызов исключения в защищенном блокет с помощью функции
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_DENORMAL_OPERAND ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Обработано исключение - " << GetExceptionCode() << endl;
	}
}
//Использование SEH и фильтра 
void denormalized_filter()
{
	__try
	{
		Denormal_flag(1.0e-40f);//Вызов исключения в защищенном блокет с помощью функции
	}
	__except (SEHFilter_flt(GetExceptionCode())) 
	{
		cout << "Обработано исключение - ненормализованное число с помощью фильтра" << endl; //Вывод информации
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