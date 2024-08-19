#include <iostream>
#include <cmath>
using namespace std;

// Структура элемента
struct Elem {
	int value; // Значение int
	Elem* next; // Ссылка на следующий обьект типа Elem
};

// Вставка элемента в начало списка
void InsertAtHead(Elem*& head, int val) {
		Elem* newNode = head; // Сохранение списка в переменную
		head = new Elem(); // Создание нового элемента на первом месте
		head->value = val; // Присваивание новому элементу добавляемое значение
		head->next = newNode; // Присваивание след. элемента (списка) для нового значения
}

// Вставка элемента в конец списка
void InsertAtEnd(Elem*& head, int val) {
	if (head != nullptr) {
		InsertAtEnd(head->next, val); // Рекурсивно обходим, пока не дойдем до конца списка
	}
	else {
		head = new Elem(); // Если конец списка, создаем новый элемент
		head->value = val; // Присваиваем добавялемый элемент
	}
}
// Вставка элементов с сортировкой по возрастанию
void Insert(Elem*& head, int value) {
	if (head->value == 0 && head->next == nullptr) { // Если список пуст, сразу устанавливаем значение, чтобы избежать лишнего 0
		head->value = value;
	}
	else {
		if (head->value < value) {
			InsertAtEnd(head, value); // Если тек. значение менее добавялемого, добавляем в конец
		}
		else {
			InsertAtHead(head, value); // Если тек. значение менее добавялемого, добавляем в начало
		}
	}
}

// Вывод списка в обратном порядке (рекурсивно)
void PrintListReverse(Elem* head) {
	if (head->value == 0 && head->next == nullptr) {
		cout << "Список пуст" << endl; // Если список пуст, выводим сообщение
	}
	if (head->next != nullptr) {
		PrintListReverse(head->next); // Доходим до конца списка
	}
	cout << head->value << endl; // Выводим значение текущего элемента и выводим список возвращаясь рекурсивно
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
		cout << "Список пуст" << endl; // проверка, пуст ли список
	}
	int count = 0; // счетчик
	while (head != nullptr) {
		if (head->value == value) {
			count++; // Значение совпало - добавялем к количеству
		}
		head = head->next; // Переходим к следующему элементу
	}
	cout << "Количество значений для " << value << "\n" << count << endl; // Выводим количество найденных значений
	return count;
}

// Удаление элементов со значением value из списка
void Delete(Elem*& head, int value) {
	if (head == nullptr) {
		cout << "Список пуст" << endl; // Проверка пуст ли список
		return;
	}
	if (head->value == value) {
		cout << "Элемент " << head->value << " удалён." << endl; // Выводим сообщение об удалении элемента
		Elem* next = head->next; // Сохраняем значение следующего элемента
		delete head; // Удаляем ссылку
		head = next; // Присваиваем оставшийся список текущему элементу
	}
	if (head != nullptr && head->next != nullptr) {
		Delete(head->next, value); // Идем до конца списка рекурсивно
	}
}

// Очистка списка 
void Clear(Elem*& head) {
	while (head != nullptr) {
		Elem* temp = head; 
		head = head->next; // Переходим к следующему элементу
		delete temp; // Освобождаем память
	}
}

int main() {
	Elem* list = new Elem(); // Создаем список

	Insert(list, 10);
	Insert(list, 9);
	Insert(list, 100);
	Insert(list, 9);
	Insert(list, 8);

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
