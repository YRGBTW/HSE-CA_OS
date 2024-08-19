#include <iostream>
using namespace std;

// Структура для представления узла дерева
struct Node {
    int value;
    Node* left;
    Node* right;
};

// Функция для очистки дерева
void ClearTree(Node* root) {
    if (root == nullptr)
        return;
    ClearTree(root->left); // Рекурсивно очищаем левое поддерево
    ClearTree(root->right); // Рекурсивно очищаем правое поддерево
    delete root; // Удаляем ссылку
}

// Функция для вставки элемента в дерево
void InsertNode(Node*& root, int value) {
    if (root == nullptr) { // При пустом дереве вставка в 1 элемент
        root = new Node();
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        if (value < root->value) {
            InsertNode(root->left, value); // Рекурсивно вставляем в левое поддерево
        }
        else {
            InsertNode(root->right, value); // Рекурсивно вставляем в правое поддерево
        }
    }
}

// Функция для поиска элемента в дереве
bool SearchValue(Node* root, int value) {
    while (root != nullptr) {
        if (value == root->value)
            return true;
        else if (value < root->value)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}


// Функция для удаления элемента из дерева
void DeleteNode(Node* root, int value) {
    Node* parent = nullptr;  // Указатель на родительский узел (начинаем с корня, у которого нет родителя)
    Node* current = root;   // Указатель на текущий узел, начинаем с корня дерева

    while (current != nullptr) {  // Проходим по дереву, пока не достигнем конца (листа)
        if (value == current->value) {
            // Нашли узел, который нужно удалить
            if (current->left == nullptr && current->right == nullptr) {
                // Удаляем узел, если у него нет потомков
                if (parent) {
                    // Если у текущего узла есть родитель, обнуляем ссылку на текущий узел в его родителе
                    if (parent->left == current) {
                        parent->left = nullptr;
                    }
                    else {
                        parent->right = nullptr;
                    }
                }
                delete current;  // Удаляем текущий узел
            }
            else if (current->left == nullptr) {
                // Удаляем узел, если у него есть только правый потомок
                Node* temp = current;
                current = current->right;
                if (parent) {
                    if (parent->left == temp) {
                        parent->left = current;
                    }
                    else {
                        parent->right = current;
                    }
                }
                delete temp;  // Удаляем текущий узел
            }
            else if (current->right == nullptr) {
                // Удаляем узел, если у него есть только левый потомок
                Node* temp = current;
                current = current->left;
                if (parent) {
                    if (parent->left == temp) {
                        parent->left = current;
                    }
                    else {
                        parent->right = current;
                    }
                }
                delete temp;  // Удаляем текущий узел
            }
            else {
                // Удаляем узел, если у него есть оба потомка
                Node* minRight = current->right;
                while (minRight->left != nullptr)
                    minRight = minRight->left;
                current->value = minRight->value;
                value = minRight->value;  // Обновляем значение для последующего удаления
                parent = current;
                current = current->right;
            }
        }
        else if (value < current->value) {
            parent = current;
            current = current->left;  // Переход в левое поддерево
        }
        else {
            parent = current;
            current = current->right;  // Переход в правое поддерево
        }
    }
}





// Функция для вывода дерева в порядке возрастания значений
void PrintTreeInOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    PrintTreeInOrder(node->left); // Рекурсивно выводим левое поддерево
    cout << node->value << " "; // Выводим значение текущего узла
    PrintTreeInOrder(node->right); // Рекурсивно выводим правое поддерево
}

// Функция для вывода дерева в порядке убывания значений
void PrintTreeInReverseOrder(Node* node) {
    if (node == nullptr)
        return;
    PrintTreeInReverseOrder(node->right); // Рекурсивно выводим правое поддерево
    cout << node->value << " "; // Выводим значение текущего узла
    PrintTreeInReverseOrder(node->left); // Рекурсивно выводим левое поддерево
}
int main() {
    Node* root = nullptr; // Создаем пустое дерево

    // Добавляем элементы в дерево
    InsertNode(root, 100);
    InsertNode(root, 99);
    InsertNode(root, 240);
    InsertNode(root, 72);
    InsertNode(root, 999);
    InsertNode(root, 55);

    // Выводим элементы дерева в порядке возрастания
    cout << "Вывод элементов дерева в порядке возрастания:" << endl;
    PrintTreeInOrder(root);
    cout << endl;

    // Поиск элемента в дереве
    int searchValue = 99;
    cout << "Поиск элемента " << searchValue << ":" << endl;
    if (SearchValue(root, searchValue)) {
        cout << "Элемент " << searchValue << " найден в дереве" << endl;
    }
    else {
        cout << "Элемент " << searchValue << " не найден в дереве" << endl;
    }

    // Удаление элемента из дерева
    int valueToDelete = 99;
    cout << "Удаление элемента " << valueToDelete << ":" << endl;
    DeleteNode(root, valueToDelete);
    cout << "Элемент " << valueToDelete << " удален" << endl;

    // Выводим элементы дерева после удаления
    cout << "Вывод элементов дерева после удаления:" << endl;
    PrintTreeInOrder(root);

    // Очищаем дерево
    ClearTree(root);
    cout << "\nДерево очищено" << endl;

    return 0;
}

