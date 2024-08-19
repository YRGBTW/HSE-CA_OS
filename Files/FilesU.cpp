#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;
//��������� ��� ������/������
struct Person {
	Person(string name, int age) : name{ name }, age{ age } {}
	string name;
	int age;
};
//������� ��� �������� ���� ������
void errorChecker(ios_base::iostate state)
{
	switch (state)
	{
	case (ios::badbit):
	{
		cout << "��� ���������� �������� �����-������ ���������� ��������� ������." << endl;
	}
	case (ios::failbit):
	{
		cout << "��� ���������� �������� �����-������ ��������� ����������� ����." << endl;
	}
	case (ios::eofbit):
	{
		cout << "��������� ����� �����" << endl;
	}
	default:
		cout << "�� ���������� �������� ������" << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "russian");

	fstream filestream; //����������� �����, ����/�����
	//�������� ����� � ������ ������
	filestream.open("File.txt", ios::out);
	if (filestream.is_open()) //��������, ������ �� ����
	{
		filestream << "� ���� �������� ����������" << endl; //������ � ����
		if (filestream.fail()) //�������� �� ������� ������
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate()); //����� ���� ������
			RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
		}
		filestream.close(); //�������� �����
	}
	else 
	{
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate()); //����� ���� ������
	}
	//������ ����� � ������ ������
	string read;
	filestream.open("File.txt", ios::in);  //�������� ����� � ������ ������
	if (filestream.is_open())
	{
		getline(filestream, read); //����� �������� �� �����
		if (!filestream)
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate());
			RaiseException(EXCEPTION_READ_FAULT, 0, 0, nullptr);
		}
		cout << read << endl;//�������
		filestream.close();//���������
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//���� ���������� �����
	string input;
	filestream.open("File.txt", ios::app); //�������� ����� � ������ �������� (��������� ������������� ���������� � ����� �����)
	if (filestream.is_open())
	{
		cout << "�������� ����? 1 - ��, 0 - ���" << endl;
		cin >> input;
		if (input == "1")
		{
			filestream.close();//���� ��������� �������, ��������� ����
			filestream.open("File.txt", ios::out);//� ��������� �� ��� ������ � ������ ������, ��� ����� ������ ���� ����
		}
		while(input!="0")
		{
			cout << "����� ��������� ����, ������� 0" << endl;//���� ����� �� ��� ��� ���� �� ���������� 0
			cin >> input;
			if (input == "0") {
				break;
			}
			filestream << input << endl; //������ � ����
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
	//������ ���������� ����� �� �����
	vector<string> arr;//������ ��� ������ ��������
	filestream.open("File.txt", ios::in);//�������� ����� � ������ ������
	if (filestream.is_open())
	{
		while (getline(filestream, read))//��������� ������
		{
			arr.push_back(read);//���������� � ������
		}
		cout << "�����, ����������� � �����:" << endl;
		for (int k = 0; k < arr.size(); k++)//����� ��������� ��������
		{
			cout << arr[k] << " ";
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//����� ����������� ��������
	filestream.open("File.txt", ios::in);
	int a = 0;
	if (filestream.is_open())
	{
		string output;
		cout << "\n������� ����� �������, � �������� ����� ����� ������" << endl;
		cin >> a;
		if (!cin) {
			cout << "������ �������� �����" << endl;
			return 0;
		}
		filestream.seekg(a);//������� ��� ����������� ������ (����������� ��������� �� ���������� ����)
		getline(filestream, output);
		cout << (output == "" ? "������ �����." : "����������� ������: ") << output;
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//������/������ ��������
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
			filestream << person.name << " " << person.age << endl; //������ � ����
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}

	vector <Person> people1;//������ ��� ������ � ���� ��������� ��������
	filestream.open("File.txt", ios::in);//����� ������
	if (filestream.is_open())
	{
		string name;
		int age;
		while (filestream >> name >> age) {
			people1.push_back(Person{ name,age }); //��������� ������ � ��������� � ������
		}
		for (int j = 0; j < people1.size(); j++) { //�����
			cout << " Name: " << people1[j].name << " Age: " << people1[j].age << endl;
		}
		filestream.close();
	}
	//�������� �����
	HANDLE NewFile;
	const wchar_t* filepath = L"MyFile.txt";
	NewFile = CreateFile(
		filepath, //���� �����
		GENERIC_READ,//����� ��� ������
		FILE_SHARE_READ,//������ ��� ������ ��������� ��� ������ ����� ������������
		NULL, //������������
		CREATE_ALWAYS, //������ �������� ������ �����
		FILE_ATTRIBUTE_READONLY, // ���. ��������, �������� �������� ������ ��� ������
		NULL);
}
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;
//��������� ��� ������/������
struct Person {
	Person(string name, int age) : name{ name }, age{ age } {}
	string name;
	int age;
};
//������� ��� �������� ���� ������
void errorChecker(ios_base::iostate state)
{
	switch (state)
	{
	case (ios::badbit):
	{
		cout << "��� ���������� �������� �����-������ ���������� ��������� ������." << endl;
	}
	case (ios::failbit):
	{
		cout << "��� ���������� �������� �����-������ ��������� ����������� ����." << endl;
	}
	case (ios::eofbit):
	{
		cout << "��������� ����� �����" << endl;
	}
	default:
		cout << "�� ���������� �������� ������" << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "russian");

	fstream filestream; //����������� �����, ����/�����
	//�������� ����� � ������ ������
	filestream.open("File.txt", ios::out);
	if (filestream.is_open()) //��������, ������ �� ����
	{
		filestream << "� ���� �������� ����������" << endl; //������ � ����
		if (filestream.fail()) //�������� �� ������� ������
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate()); //����� ���� ������
			RaiseException(EXCEPTION_WRITE_FAULT, 0, 0, nullptr);
		}
		filestream.close(); //�������� �����
	}
	else 
	{
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate()); //����� ���� ������
	}
	//������ ����� � ������ ������
	string read;
	filestream.open("File.txt", ios::in);  //�������� ����� � ������ ������
	if (filestream.is_open())
	{
		getline(filestream, read); //����� �������� �� �����
		if (!filestream)
		{
			cout << "Error: " << endl;
			errorChecker(filestream.rdstate());
			RaiseException(EXCEPTION_READ_FAULT, 0, 0, nullptr);
		}
		cout << read << endl;//�������
		filestream.close();//���������
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//���� ���������� �����
	string input;
	filestream.open("File.txt", ios::app); //�������� ����� � ������ �������� (��������� ������������� ���������� � ����� �����)
	if (filestream.is_open())
	{
		cout << "�������� ����? 1 - ��, 0 - ���" << endl;
		cin >> input;
		if (input == "1")
		{
			filestream.close();//���� ��������� �������, ��������� ����
			filestream.open("File.txt", ios::out);//� ��������� �� ��� ������ � ������ ������, ��� ����� ������ ���� ����
		}
		while(input!="0")
		{
			cout << "����� ��������� ����, ������� 0" << endl;//���� ����� �� ��� ��� ���� �� ���������� 0
			cin >> input;
			if (input == "0") {
				break;
			}
			filestream << input << endl; //������ � ����
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
	//������ ���������� ����� �� �����
	vector<string> arr;//������ ��� ������ ��������
	filestream.open("File.txt", ios::in);//�������� ����� � ������ ������
	if (filestream.is_open())
	{
		while (getline(filestream, read))//��������� ������
		{
			arr.push_back(read);//���������� � ������
		}
		cout << "�����, ����������� � �����:" << endl;
		for (int k = 0; k < arr.size(); k++)//����� ��������� ��������
		{
			cout << arr[k] << " ";
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//����� ����������� ��������
	filestream.open("File.txt", ios::in);
	int a = 0;
	if (filestream.is_open())
	{
		string output;
		cout << "\n������� ����� �������, � �������� ����� ����� ������" << endl;
		cin >> a;
		if (!cin) {
			cout << "������ �������� �����" << endl;
			return 0;
		}
		filestream.seekg(a);//������� ��� ����������� ������ (����������� ��������� �� ���������� ����)
		getline(filestream, output);
		cout << (output == "" ? "������ �����." : "����������� ������: ") << output;
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}
	//������/������ ��������
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
			filestream << person.name << " " << person.age << endl; //������ � ����
		}
		filestream.close();
	}
	else {
		cout << "Error: " << endl;
		errorChecker(filestream.rdstate());
	}

	vector <Person> people1;//������ ��� ������ � ���� ��������� ��������
	filestream.open("File.txt", ios::in);//����� ������
	if (filestream.is_open())
	{
		string name;
		int age;
		while (filestream >> name >> age) {
			people1.push_back(Person{ name,age }); //��������� ������ � ��������� � ������
		}
		for (int j = 0; j < people1.size(); j++) { //�����
			cout << " Name: " << people1[j].name << " Age: " << people1[j].age << endl;
		}
		filestream.close();
	}
	//�������� �����
	HANDLE NewFile;
	const wchar_t* filepath = L"MyFile.txt";
	NewFile = CreateFile(
		filepath, //���� �����
		GENERIC_READ,//����� ��� ������
		FILE_SHARE_READ,//������ ��� ������ ��������� ��� ������ ����� ������������
		NULL, //������������
		CREATE_ALWAYS, //������ �������� ������ �����
		FILE_ATTRIBUTE_READONLY, // ���. ��������, �������� �������� ������ ��� ������
		NULL);
}
