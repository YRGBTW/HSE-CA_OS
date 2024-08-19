#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>


using namespace std;
struct Person {
	Person(string name, int age) : name{ name }, age{ age } {}
	string name;
	int age;	
};
int main()
{
	setlocale(LC_ALL, "rus");
	fstream file; // создание потока ввода/вывода
	#pragma region Write
	file.open("output.txt", ios::out); // Открытие/создание файла в режиме записи
	if (file.is_open()) 
	{
		file << "В файл записана информация" << endl;
		if (file.fail())
		{
			cout << "Error: " << file.rdstate() << endl;	
			//badbit - stream error
			//failbit - operation failure
			RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
		}
		file.close();
	}
	else {
		cout << "Ошибка при открытии файла " << file.rdstate() << endl;
	}
	#pragma endregion

	system("pause");
	
	#pragma region Read

	string read;
	file.open("output.txt", ios::in);  // Открытие/создание файла в режиме чтения
	if (file.is_open())
	{
		getline(file,read); // запись в переменную, но по-другому
		if (!file)
		{
			cout << "Error: " << file.rdstate() << endl;
			RaiseException(EXCEPTION_READ_FAULT, 0, 0, nullptr);
		}
		cout << read << endl;
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "Ошибка при открытии файла" << endl;
	}
	#pragma endregion

	system("pause");

	#pragma region InputStrings

	string input;
	file.open("output.txt", ios::app | ios::ate); // открываем файл в режиме дозаписи и помещаем указатель в конец файла
	if (file.is_open()) 
	{
		cout << "Очистить файл? 1 - Да, 0 - Нет" << endl;
		cin >> input;
		if (input == "1")
		{
			file.close();
			file.open("output.txt", ios::out);
		}
		do
		{
			cout << "Для окончания ввода введите 0" << endl;
			cin >> input;
			if (input == "0") {
				break;
			}
			file << input << endl; // сохраняем в файл
			if (!file)
			{
				cout << "Error: " << file.rdstate() << endl;
				RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
			}
		} while (input != "0");

		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "Ошибка при открытии файла" << endl;
	}
	#pragma endregion

	system("pause");

	#pragma region ReadStrings
	vector<int> arr;
	int res;
	file.open("output.txt", ios::in);
	if (file.is_open())
	{
		while (getline(file, read)) 
		{
			try 
			{
				res = stoi(read);
				arr.push_back(res);
			}
			catch (invalid_argument e)
			{
				cout << "Ошибка при преобразовании в INT: "  << e.what() << endl;
			}
			catch (...)
			{
				cout << "Неизвестная ошибка" << endl;
			}
		}
		cout << "Числа, находящиеся в файле:" << endl;
		for (int k = 0; k < arr.size(); k++) 
		{
			cout << arr[k] << " ";
		}
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "Ошибка при открытии файла" << endl;
	}
	#pragma endregion

	#pragma region Seek
	file.open("output.txt", ios::in);
	int a = 0;
	if (file.is_open()) 
	{
		string output;
		cout << "\nВведите номер символа, с которого нужно найти строку" << endl;
		cin >> a;
		if (!cin) {
			cout << "Введен неверный номер" << endl;
			return 0;
		}
		file.seekg(a);
		getline(file, output);
		cout << (output == "" ? "Строка пуста." : "Прочитанная строка: ") << output;
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "Ошибка при открытии файла" << endl;
	}
	#pragma endregion

	system("pause");
	#pragma region Struct
	vector <Person> people{ Person("Yaroslav", 20),Person("Segey",15),Person("Vlad",21) };
	file.open("output.txt", ios:: out);
	if (file.is_open())
	{
		for (Person& person : people) {
			file << person.name << " " << person.age << endl;
		}
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "Ошибка при открытии файла" << endl;
	}

	vector <Person> people1;
	file.open("output.txt", ios::in);
	if (file.is_open())
	{
		string name;
		int age;
		while (file >> name >> age) {
			people1.push_back(Person{ name,age });
		}
		for (int j = 0; j < people1.size(); j++) {
			cout << " Name: " << people1[j].name << " Age: " << people1[j].age << endl;
		}
		file.close();
	}
	#pragma endregion

	HANDLE NewFile;
	const wchar_t* filepath = L"NewFile.txt";
	NewFile = CreateFile(
		filepath, 
		GENERIC_READ,// права для чтения
		FILE_SHARE_READ,// доступ для разных процессов для чтения файла одновременно
		NULL, // безопасность
		CREATE_ALWAYS, // всегда создание нового файла
		FILE_ATTRIBUTE_READONLY, // доп. атрибуты
		NULL);

}
