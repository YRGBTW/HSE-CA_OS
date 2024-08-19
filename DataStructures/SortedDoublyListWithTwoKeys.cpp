#include <iostream>
#include <cmath>
using namespace std;

// Двусвязный список с двумя полями
struct Elem {
    int number;// Значение int - номер студента
    int rating;// Значение int - рейтинг студента
    Elem* next;// Ссылка на след. элемент
    Elem* prev;// Ссылка на предыдущий элемент
};

// Вставка элемента в начало списка с сортировкой по number и rating
void InsertAtHead(Elem*& head, int number, int rating) {
    Elem* newNode = new Elem();
    newNode->number = number;
    newNode->rating = rating;

    if (head == nullptr) {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode; // Новый элемент становится головой списка, если он пуст
    }
    else {
        Elem* current = head;
        Elem* prev = nullptr;

        while (current != nullptr && (current->number < number || (current->number == number && current->rating < rating))) {
            prev = current;
            current = current->next; // Идем по списку, пока не найдем место для вставки нового элемента
        }

        newNode->next = current;
        newNode->prev = prev;

        if (prev != nullptr) {
            prev->next = newNode;
        }
        else {
            head = newNode;
        }

        if (current != nullptr) {
            current->prev = newNode;
        }
    }
}

// Вставка элемента в конец списка с сортировкой по number и rating
void InsertAtEnd(Elem*& head, int number, int rating) {
    Elem* newNode = new Elem();
    newNode->number = number;
    newNode->rating = rating;

    if (head == nullptr) {
        newNode->prev = nullptr;
        newNode->next = nullptr;
        head = newNode; // Новый элемент становится головой списка, если он пуст
    }
    else {
        Elem* current = head;
        Elem* prev = nullptr;

        while (current != nullptr && (current->number < number || (current->number == number && current->rating < rating))) {
            prev = current;
            current = current->next; // Идем по списку, пока не найдем место для вставки нового элемента
        }

        newNode->next = current;
        newNode->prev = prev;

        if (prev != nullptr) {
            prev->next = newNode;
        }
        else {
            head = newNode;
        }

        if (current != nullptr) {
            current->prev = newNode;
        }
    }
}

// Вставка элемента с сортировкой по number и rating
void Insert(Elem*& head, int number, int rating) {
    Elem* newNode = new Elem();
    newNode->number = number;
    newNode->rating = rating;

    if (head == nullptr) {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        return;
    }

    Elem* current = head;
    Elem* prev = nullptr;

    while (current != nullptr && (current->number < number || (current->number == number && current->rating < rating))) {
        prev = current;
        current = current->next;
    }

    newNode->next = current;
    newNode->prev = prev;

    if (prev != nullptr) {
        prev->next = newNode;
    }
    else {
        head = newNode;
    }

    if (current != nullptr) {
        current->prev = newNode;
    }
}


// Вывод списка
void PrintList(Elem* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl; //Проверка пуст ли список
        return;
    }

    while (head != nullptr) {
        cout << head->number << " - " << head->rating << endl;//Выводим значение текущего элемента
        head = head->next;//Переходим к следующему элементу
    }
}

// Вывод списка в обратном порядке
void PrintListReverse(Elem* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;//Проверка пуст ли список
        return;
    }

    Elem* current = head;
    while (current->next != nullptr) {
        current = current->next; // Находим последний элемент списка
    }

    while (current != nullptr) {
        cout << current->number <<" - " << current->rating << endl;// Выводим значение текущего элемента
        current = current->prev;// Переходим к предыдущему элементу
    }
}

// Поиск элемента в списке
int Search(Elem* head, int value, int rating) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return 0;
    }
    int count = 0;
    while (head != nullptr) {
        if (head->number == value && head->rating == rating) {
            count++;
        }
        head = head->next;
    }
    cout << "Количество значений для " << value << "-" << rating << ": " << count << endl;// Выводим количество найденных значений
    return count;
}

// Удаление элементов
void Delete(Elem*& head, int value, int rating) {
    Elem* current = head;
    while (current != nullptr) { // Обход всего списка
        if (current->number == value && current->rating == rating) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            Elem* temp = current;
            current = current->next;
            delete temp; // Удаление ссылки
        }
        else {
            current = current->next;
        }
    }
}

// Очистка списка
void Clear(Elem*& head) {
    while (head != nullptr) {
        Elem* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Elem* list = nullptr; // Изначально список пуст

    Insert(list,1,92);
    Insert(list,2,43);
    Insert(list,4,12);
    Insert(list,8,1);
    Insert(list,10,10);

    cout << "Список: " << endl;
    PrintList(list);

    cout << "Обратный список: " << endl;
    PrintListReverse(list);

    int value = 10;
    int rating = 10;
    Search(list, value, 10);

    Delete(list, value, rating);
    cout << "Список после удаления элементов: " << endl;
    PrintList(list);

    Clear(list); // Очистка списка
}