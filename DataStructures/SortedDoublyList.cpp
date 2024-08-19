#include <iostream>
#include <cmath>
using namespace std;

// Двусвязный список
struct Node {
    int value;// Значение int
    Node* next;// Ссылка на след. элемент
    Node* prev;// Ссылка на предыдущий элемент
};

// Вставка элемента в начало списка
void InsertFirst(Node*& head, int val) {
    Node* newNode = new Node(); 
    newNode->value = val;
    newNode->next = head;// Устанавливаем след. элементом имеющийся список
    newNode->prev = nullptr;// Предыдущий элемент пуст
    if (head != nullptr) {
        head->prev = newNode;// Если список не пуст устанавливаем пред. элемент новым 
    }
    head = newNode; 
}

// Вставка элемента в конец списка
void InsertLast(Node*& head, int val) {
    Node* newNode = new Node();
    newNode->value = val;
    newNode->next = nullptr;
    if (head == nullptr) {
        newNode->prev = nullptr;
        head = newNode;// Новый элемент становится головой списка если он пуст
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next; // Находим последний элемент списка
        }
        current->next = newNode;// Старый элемент = новый
        newNode->prev = current;// Предыдущий = текущий
    }
}
// Вставка элемента с сортировкой
void Insert(Node*& head, int value) {
    if (head == nullptr || head->value >= value) {
        // Если список пуст или новое значение меньше или равно головному элементу,
        // используем метод InsertFirst для вставки в начало.
        InsertFirst(head, value);
    }
    else {
        Node* current = head;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        if (current->next == nullptr) {
            // Если достигли конца списка, используем метод InsertLast для вставки в конец.
            InsertLast(head, value);
        }
        else {
            // В противном случае, вставляем новый элемент между текущим и следующим элементом.
            Node* newNode = new Node();
            newNode->value = value;
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
    }
}


// Вывод списка
void PrintList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl; //Проверка пуст ли список
        return;
    }

    while (head != nullptr) {
        cout << head->value << endl;//Выводим значение текущего элемента
        head = head->next;//Переходим к следующему элементу
    }
}

// Вывод списка в обратном порядке
void PrintListReverse(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;//Проверка пуст ли список
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next; // Находим последний элемент списка
    }

    while (current != nullptr) {
        cout << current->value << endl;// Выводим значение текущего элемента
        current = current->prev;// Переходим к предыдущему элементу
    }
}

// Поиск элемента в списке
int Search(Node* head, int value) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return 0;
    }
    int count = 0;
    while (head != nullptr) {
        if (head->value == value) {
            count++;
        }
        head = head->next;
    }
    cout << "Количество значений для " << value << ": " << count << endl;// Выводим количество найденных значений
    return count;
}

// Удаление элементов
void Delete(Node*& head, int value) {
    Node* current = head;
    while (current != nullptr) { // Обход всего списка
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            Node* temp = current;
            current = current->next;
            delete temp; // Удаление ссылки
        }
        else {
            current = current->next;
        }
    }
}

// Очистка списка
void Clear(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* list = nullptr;

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