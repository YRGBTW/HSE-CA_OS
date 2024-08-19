#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;
//Структура для записи/чтения
struct Person {
	Person(string name, int age) : name{ name }, age{ age } {}
	string name;
	int age;
};
//Функция для проверки типа ошибки
void errorChecker(ios_base::iostate state)
{
	switch (state)
	{
	case (ios::badbit):
	{
		cout << "При выполнении операций ввода-вывода обнаружена фатальная ошибка." << endl;
	}
	case (ios::failbit):
	{
		cout << "При выполнении операций ввода-вывода обнаружен нефатальный сбой." << endl;
	}
	case (ios::eofbit):
	{
		cout << "Обнаружен конец файла" << endl;
	}
	default:
		cout << "Не обнаружено никакиих ошибок" << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "russian");

	fstream filestream; //Совмещенный поток, ввод/вывод
	//Открытие файла в режиме записи
	filestream.open("File.txt", ios::out);
	if (filestream.is_open()) //Проверка, открыт ли файл
	{
		filestream << "В файл записана информация" << endl; //Запись в файл
		if (filestream.fail()) //Проверка на наличие ошибок
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate()); //Вывод типа ошибки
			RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
		}
		filestream.close(); //Закрытие файла
	}
	else 
	{
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate()); //Вывод типа ошибки
	}
	//Чтение файла в режиме чтения
	string read;
	filestream.open("File.txt", ios::in);  //Открытие файла в режиме чтения
	if (filestream.is_open())
	{
		getline(filestream, read); //Берем значение из файла
		if (!filestream)
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate());
			RaiseException(EXCEPTION_READ_FAULT, 0, 0, nullptr);
		}
		cout << read << endl;//Выводим
		filestream.close();//Закрываем
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Ввод нескольких строк
	string input;
	filestream.open("File.txt", ios::app); //Открытие файла в режиме дозаписи (указатель автоматически помещается в конец файла)
	if (filestream.is_open())
	{
		cout << "Очистить файл? 1 - Да, 0 - Нет" << endl;
		cin >> input;
		if (input == "1")
		{
			filestream.close();//Если требуется очистка, закрываем файл
			filestream.open("File.txt", ios::out);//И открываем но уже просто в режиме записи, тем самым очищая весь файл
		}
		while(input!="0")
		{
			cout << "Чтобы закончить ввод, введите 0" << endl;//Ввод строк до тех пор пока не встретится 0
			cin >> input;
			if (input == "0") {
				break;
			}
			filestream << input << endl; //Запись в файл
			if (!filestream)
			{
				cout << "Error: " << endl;
				errorChecker(filestream.rdstate());
				RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
			}
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Чтение нескольких строк из файла
	vector<string> arr;//Массив для записи значений
	filestream.open("File.txt", ios::in);//Открытие файла в режиме чтения
	if (filestream.is_open())
	{
		while (getline(filestream, read))//Считываем строки
		{
			arr.push_back(read);//Записываем в массив
		}
		cout << "Числа, находящиеся в файле:" << endl;
		for (int k = 0; k < arr.size(); k++)//Вывод найденных значений
		{
			cout << arr[k] << " ";
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Поиск конкретного значения
	filestream.open("File.txt", ios::in);
	int a = 0;
	if (filestream.is_open())
	{
		string output;
		cout << "\nВведите номер символа, с которого нужно найти строку" << endl;
		cin >> a;
		if (!cin) {
			cout << "Введен неверный номер" << endl;
			return 0;
		}
		filestream.seekg(a);//Функция для побайтового поиска (перемещение указателя на конкретный байт)
		getline(filestream, output);
		cout << (output == "" ? "Строка пуста." : "Прочитанная строка: ") << output;
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Запись/чтение структур
	vector <Person> people 
	{
		Person("Max", 15), 
		Person("Alex",15), 
		Person("Jegor",11) 
	};
	filestream.open("File.txt", ios::out);
	if (filestream.is_open())
	{
		for (Person& person : people) {
			filestream << person.name << " " << person.age << endl; //Запись в файл
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}

	vector <Person> people1;//Массив для записи в него найденных значений
	filestream.open("File.txt", ios::in);//Режим чтения
	if (filestream.is_open())
	{
		string name;
		int age;
		while (filestream >> name >> age) {
			people1.push_back(Person{ name,age }); //Считываем строки и добавляем в массив
		}
		for (int j = 0; j < people1.size(); j++) { //Вывод
			cout << " Name: " << people1[j].name << " Age: " << people1[j].age << endl;
		}
		filestream.close();
	}
	//Создание файла
	HANDLE NewFile;
	const wchar_t* filepath = L"MyFile.txt";
	NewFile = CreateFile(
		filepath, //Путь файла
		GENERIC_READ,//Права для чтения
		FILE_SHARE_READ,//Доступ для разных процессов для чтения файла одновременно
		NULL, //Безопасность
		CREATE_ALWAYS, //Всегда создание нового файла
		FILE_ATTRIBUTE_READONLY, // доп. атрибуты, например доступно только для чтения
		NULL);
}
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;
//Структура для записи/чтения
struct Person {
	Person(string name, int age) : name{ name }, age{ age } {}
	string name;
	int age;
};
//Функция для проверки типа ошибки
void errorChecker(ios_base::iostate state)
{
	switch (state)
	{
	case (ios::badbit):
	{
		cout << "При выполнении операций ввода-вывода обнаружена фатальная ошибка." << endl;
	}
	case (ios::failbit):
	{
		cout << "При выполнении операций ввода-вывода обнаружен нефатальный сбой." << endl;
	}
	case (ios::eofbit):
	{
		cout << "Обнаружен конец файла" << endl;
	}
	default:
		cout << "Не обнаружено никакиих ошибок" << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "russian");

	fstream filestream; //Совмещенный поток, ввод/вывод
	//Открытие файла в режиме записи
	filestream.open("File.txt", ios::out);
	if (filestream.is_open()) //Проверка, открыт ли файл
	{
		filestream << "В файл записана информация" << endl; //Запись в файл
		if (filestream.fail()) //Проверка на наличие ошибок
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate()); //Вывод типа ошибки
			RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
		}
		filestream.close(); //Закрытие файла
	}
	else 
	{
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate()); //Вывод типа ошибки
	}
	//Чтение файла в режиме чтения
	string read;
	filestream.open("File.txt", ios::in);  //Открытие файла в режиме чтения
	if (filestream.is_open())
	{
		getline(filestream, read); //Берем значение из файла
		if (!filestream)
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate());
			RaiseException(EXCEPTION_READ_FAULT, 0, 0, nullptr);
		}
		cout << read << endl;//Выводим
		filestream.close();//Закрываем
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Ввод нескольких строк
	string input;
	filestream.open("File.txt", ios::app); //Открытие файла в режиме дозаписи (указатель автоматически помещается в конец файла)
	if (filestream.is_open())
	{
		cout << "Очистить файл? 1 - Да, 0 - Нет" << endl;
		cin >> input;
		if (input == "1")
		{
			filestream.close();//Если требуется очистка, закрываем файл
			filestream.open("File.txt", ios::out);//И открываем но уже просто в режиме записи, тем самым очищая весь файл
		}
		while(input!="0")
		{
			cout << "Чтобы закончить ввод, введите 0" << endl;//Ввод строк до тех пор пока не встретится 0
			cin >> input;
			if (input == "0") {
				break;
			}
			filestream << input << endl; //Запись в файл
			if (!filestream)
			{
				cout << "Error: " << endl;
				errorChecker(filestream.rdstate());
				RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
			}
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Чтение нескольких строк из файла
	vector<string> arr;//Массив для записи значений
	filestream.open("File.txt", ios::in);//Открытие файла в режиме чтения
	if (filestream.is_open())
	{
		while (getline(filestream, read))//Считываем строки
		{
			arr.push_back(read);//Записываем в массив
		}
		cout << "Числа, находящиеся в файле:" << endl;
		for (int k = 0; k < arr.size(); k++)//Вывод найденных значений
		{
			cout << arr[k] << " ";
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Поиск конкретного значения
	filestream.open("File.txt", ios::in);
	int a = 0;
	if (filestream.is_open())
	{
		string output;
		cout << "\nВведите номер символа, с которого нужно найти строку" << endl;
		cin >> a;
		if (!cin) {
			cout << "Введен неверный номер" << endl;
			return 0;
		}
		filestream.seekg(a);//Функция для побайтового поиска (перемещение указателя на конкретный байт)
		getline(filestream, output);
		cout << (output == "" ? "Строка пуста." : "Прочитанная строка: ") << output;
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//Запись/чтение структур
	vector <Person> people 
	{
		Person("Max", 15), 
		Person("Alex",15), 
		Person("Jegor",11) 
	};
	filestream.open("File.txt", ios::out);
	if (filestream.is_open())
	{
		for (Person& person : people) {
			filestream << person.name << " " << person.age << endl; //Запись в файл
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}

	vector <Person> people1;//Массив для записи в него найденных значений
	filestream.open("File.txt", ios::in);//Режим чтения
	if (filestream.is_open())
	{
		string name;
		int age;
		while (filestream >> name >> age) {
			people1.push_back(Person{ name,age }); //Считываем строки и добавляем в массив
		}
		for (int j = 0; j < people1.size(); j++) { //Вывод
			cout << " Name: " << people1[j].name << " Age: " << people1[j].age << endl;
		}
		filestream.close();
	}
	//Создание файла
	HANDLE NewFile;
	const wchar_t* filepath = L"MyFile.txt";
	NewFile = CreateFile(
		filepath, //Путь файла
		GENERIC_READ,//Права для чтения
		FILE_SHARE_READ,//Доступ для разных процессов для чтения файла одновременно
		NULL, //Безопасность
		CREATE_ALWAYS, //Всегда создание нового файла
		FILE_ATTRIBUTE_READONLY, // доп. атрибуты, например доступно только для чтения
		NULL);
}
