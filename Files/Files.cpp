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
	fstream file; // �������� ������ �����/������
	#pragma region Write
	file.open("output.txt", ios::out); // ��������/�������� ����� � ������ ������
	if (file.is_open()) 
	{
		file << "� ���� �������� ����������" << endl;
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
		cout << "������ ��� �������� ����� " << file.rdstate() << endl;
	}
	#pragma endregion

	system("pause");
	
	#pragma region Read

	string read;
	file.open("output.txt", ios::in);  // ��������/�������� ����� � ������ ������
	if (file.is_open())
	{
		getline(file,read); // ������ � ����������, �� ��-�������
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
		cout << "������ ��� �������� �����" << endl;
	}
	#pragma endregion

	system("pause");

	#pragma region InputStrings

	string input;
	file.open("output.txt", ios::app | ios::ate); // ��������� ���� � ������ �������� � �������� ��������� � ����� �����
	if (file.is_open()) 
	{
		cout << "�������� ����? 1 - ��, 0 - ���" << endl;
		cin >> input;
		if (input == "1")
		{
			file.close();
			file.open("output.txt", ios::out);
		}
		do
		{
			cout << "��� ��������� ����� ������� 0" << endl;
			cin >> input;
			if (input == "0") {
				break;
			}
			file << input << endl; // ��������� � ����
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
		cout << "������ ��� �������� �����" << endl;
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
				cout << "������ ��� �������������� � INT: "  << e.what() << endl;
			}
			catch (...)
			{
				cout << "����������� ������" << endl;
			}
		}
		cout << "�����, ����������� � �����:" << endl;
		for (int k = 0; k < arr.size(); k++) 
		{
			cout << arr[k] << " ";
		}
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "������ ��� �������� �����" << endl;
	}
	#pragma endregion

	#pragma region Seek
	file.open("output.txt", ios::in);
	int a = 0;
	if (file.is_open()) 
	{
		string output;
		cout << "\n������� ����� �������, � �������� ����� ����� ������" << endl;
		cin >> a;
		if (!cin) {
			cout << "������ �������� �����" << endl;
			return 0;
		}
		file.seekg(a);
		getline(file, output);
		cout << (output == "" ? "������ �����." : "����������� ������: ") << output;
		file.close();
	}
	else {
		cout << "Error: " << file.rdstate() << endl;
		cout << "������ ��� �������� �����" << endl;
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
		cout << "������ ��� �������� �����" << endl;
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
		GENERIC_READ,// ����� ��� ������
		FILE_SHARE_READ,// ������ ��� ������ ��������� ��� ������ ����� ������������
		NULL, // ������������
		CREATE_ALWAYS, // ������ �������� ������ �����
		FILE_ATTRIBUTE_READONLY, // ���. ��������
		NULL);

}
