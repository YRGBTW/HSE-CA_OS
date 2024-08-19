#include <iostream>
#include <cmath>
using namespace std;

// Структура элемента
struct Elem {
	int value;
	Elem* next;
};

// Вставка элемента в начало списка
void InsertAtHead(Elem*& head, int val) {
	if (head->value == 0 && head->next == nullptr) { // Если список пуст, сразу устанавливаем значение, чтобы избежать лишнего 0
		head->value = val; 
	}
	else {
		Elem* newNode = head;
		head = new Elem();
		head->value = val;
		head->next = newNode; 
	}
}

// Вставка элемента в конец списка
void InsertAtEnd(Elem*& head, int val) {
	if (head != nullptr) {
		if (head->value == 0 && head->next == nullptr) { // Если список пуст, сразу устанавливаем значение, чтобы избежать лишнего 0
			head->value = val;
			return;
		}
		InsertAtEnd(head->next, val); // Рекурсивно вставляем в конец
	}
	else {
		head = new Elem(); 
		head->value = val; 
	}
}

// Вывод списка в обратном порядке (рекурсивно)
void PrintListReverse(Elem* head) {
	if (head->value == 0 && head->next == nullptr) {
		cout << "Список пуст" << endl; // Если список пуст, выводим сообщение
	}
	if (head->next != nullptr) {
		PrintListReverse(head->next); // Рекурсивно выводим следующий элемент
	}
	cout << head->value << endl; // Выводим значение текущего элемента
}

// Вывод списка
void PrintList(Elem* head) {
	if (head->value == 0 && head->next == nullptr) {
		cout << "Список пуст" << endl; // Если список пуст, выводим сообщение
	}
	while (head != nullptr) {
		cout << head->value << endl; // Выводим значение текущего элемента
		head = head->next; // Переходим к следующему элементу
	}
}

// Поиск элемента в списке
int Search(Elem* head, int value) {
	if (head->value == 0 && head->next == nullptr) {
		cout << "Список пуст" << endl; 
	}
	int count = 0;
	while (head != nullptr) {
		if (head->value == value) {
			count++;
		}
		head = head->next; // Переходим к следующему элементу
	}
	cout << "Количество значений для " << value << "\n" << count << endl; // Выводим количество найденных значений
	return count;
}

// Удаление элементов со значением value из списка
void Delete(Elem*& head, int value) {
	if (head == nullptr) {
		cout << "Список пуст" << endl; 
		return;
	}
	if (head->value == value) {
		cout << "Элемент " << head->value << " удалён." << endl; // Выводим сообщение об удалении элемента
		Elem* next = head->next;
		delete head;
		head = next;
	}
	if (head != nullptr && head->next != nullptr) {
		Delete(head->next, value); // Рекурсивно удаляем элементы
	}
}

// Очистка списка 
void Clear(Elem*& head) {
	while (head != nullptr) {
		Elem* temp = head;
		head = head->next;
		delete temp; // Освобождаем память
	}
}

int main() {
	Elem* list = new Elem(); // Создаем список

	InsertAtHead(list, 10);
	InsertAtHead(list, 15);
	InsertAtHead(list, 10);

	InsertAtEnd(list, 12);
	InsertAtEnd(list, 52);

	cout << "Список: " << endl;
	PrintList(list);

	cout << "Обратный список: " << endl;
	PrintListReverse(list);

	int value = 10;
	Search(list, value);

	Delete(list, value);
	cout << "Список после удаления элементов: " << endl;
	PrintList(list);

	Clear(list); // Очистка списка
}
