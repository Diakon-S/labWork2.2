#define NOMINMAX
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;
using namespace chrono;

template<typename Func>
double measure(Func&& func, int iterations = 1000) {
    for (int i = 0; i < 5; ++i) func();
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, micro>(end - start).count() / iterations;
}

void clearStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) break;
        cout << "Ошибка: введите целое число.\n";
        clearStream();
    }
    clearStream();
    return value;
}

//ИДЗ

struct Product {
    string name;
    int price;
    double rating;
};

struct ProductNode {
    Product data;
    ProductNode* prev;
    ProductNode* next;
};

void printProduct(const Product& p) {
    cout << "[" << p.name << ", " << p.price << " руб, рейтинг " << p.rating << "]";
}

void printProductList(ProductNode* head, int size) {
    if (!head || size == 0) {
        cout << "Список товаров пуст.\n";
        return;
    }
    cout << "Список товаров (размер " << size << "):\n";
    ProductNode* cur = head;
    int idx = 0;
    while (cur) {
        cout << "(" << idx++ << ") ";
        printProduct(cur->data);
        cout << endl;
        cur = cur->next;
    }
}

int duplicates(ProductNode*& head, int& size) {
    if (!head || size < 2) return 0;

    int removedCount = 0;
    ProductNode* current = head;
    while (current) {
        ProductNode* runner = current->next;
        while (runner) {
            if (runner->data.name == current->data.name && runner->data.price == current->data.price) {
                ProductNode* toDelete = runner;
                if (toDelete->prev) {
                    toDelete->prev->next = toDelete->next;
                }
                if (toDelete->next) {
                    toDelete->next->prev = toDelete->prev;
                }
                runner = runner->next;
                delete toDelete;
                --size;
                ++removedCount;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return removedCount;
}

void deleteProductList(ProductNode*& head) {
    while (head) {
        ProductNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void idsMenu() {
    ProductNode* head = nullptr;
    ProductNode* tail = nullptr;
    int size = 0;

    auto addProduct = [&](const string& name, int price, double rating) {
        ProductNode* node = new ProductNode{ {name, price, rating}, tail, nullptr };
        if (!head) head = node;
        else tail->next = node;
        tail = node;
        ++size;
        };

    addProduct("Ноутбук", 50000.0, 4.5);
    addProduct("Мышка", 1500.0, 4.2);
    addProduct("Ноутбук", 50000.0, 4.0);  
    addProduct("Клавиатура", 3000.0, 4.7);
    addProduct("Мышка", 1500.0, 4.8);  
    addProduct("Монитор", 12000.0, 4.9);

    cout << "Исходный список:\n";
    printProductList(head, size);

    int removed = duplicates(head, size);
    cout << "\nУдалено дубликатов: " << removed << "\n";
    cout << "Список после удаления дубликатов:\n";
    printProductList(head, size);

    deleteProductList(head);
}

//Динамический массив

int* createRandomArr(int length) {
    if (length <= 0) {
        return nullptr;
    }

    int* arr = new int[length];
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 100;
    }
        
    return arr;
}

int* createHandArr(int& length, int flag = -1) {
    int input;
    int arrSize = 1;
    length = 0;
    int* arr = new int[arrSize];

    cout << "Вводите значения от 0 до 99, закончите ввод значением " << flag << "\n";

    while (true) {
        if (!(cin >> input)) {
            cout << "Ошибка ввода.\n";
            cin.clear();                                          
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            break;
        }

        if (input == flag) break;

        if (input < 0 || input > 99) {
            cout << "Элемент не удовлетворяет условию!\n";
            break; 
        }

        if (length == arrSize) {
            arrSize *= 2;
            int* newArr = new int[arrSize];
            for (int i = 0; i < length; ++i)
                newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
        }

        arr[length++] = input;
    }

    if (length > 0) {
        int* finalArr = new int[length];
        for (int i = 0; i < length; ++i)
            finalArr[i] = arr[i];
        delete[] arr;
        return finalArr;
    }

    else {
        delete[] arr;
        return nullptr;
    }
}

void swapArr(int* arr, int firstIndex, int secondIndex, int length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return;
    }

    if (firstIndex < 0 || firstIndex >= length || secondIndex < 0 || secondIndex >= length) {
        cout << "Такого(их) элемента(ов) не существует";
        return;
    }

    swap(arr[firstIndex], arr[secondIndex]);
    return;
}

int* delArrIndex(int* arr, int index, int& length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return arr;
    }

    if (index < 0 || index >= length) {
        cout << "Такого элемента не существует";
        return arr;
    }

    int* newArr = new int[length - 1];
    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }
    for (int i = index; i < length - 1; i++) {
        newArr[i] = arr[i + 1];
    }
    delete[] arr;
    --length;
    return newArr;
}

int* delArrValue(int* arr, int value, int& length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return arr;
    }

    int index = -1;
    for (int i = 0; i < length; i++) {
        if (arr[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Такого элемента в массиве нет" << endl;
        return arr;
    }

    return delArrIndex(arr, index, length);
}

void showArrIndex(int* arr, int index, int length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return;
    }

    if (index < 0 || index >= length) {
        cout << "Такого элемента не существует";
        return;
    }

    cout << "Элемент с индексом " << index << ": " << arr[index] << endl;
}

void showArrValue(int* arr, int value, int length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return;
    }

    int index = -1;
    for (int i = 0; i < length; i++) {
        if (arr[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Такого элемента в массиве нет" << endl;
        return;
    }

    cout << "Число " << value << " найдено по индексу: " << index << endl;
}

int* insertArr(int* arr, int index, int value, int& length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return arr;
    }

    if (index < 0 || index > length) {
        cout << "Индекс вне допустимых границ";
        return arr;
    }

    int* newArr = new int[length + 1];

    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }

    newArr[index] = value;

    for (int i = index; i < length; i++) {
        newArr[i + 1] = arr[i];
    }

    delete[] arr;
    ++length;
    return newArr;
}

void printArr(int* arr, int length) {
    if (arr == nullptr) {
        cout << "Массив пуст\n";
        return;
    }

    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void arrMenu() {
    int* arr = nullptr;
    int length = 0;

    while (true) {
        system("cls");
        cout << "1. Создать массив (случайно)\n";
        cout << "2. Создать массив (вручную)\n";
        cout << "3. Измерить скорость создания (случайного)\n";
        cout << "4. Вставка элемента\n";
        cout << "5. Удаление по индексу\n";
        cout << "6. Удаление по значению\n";
        cout << "7. Обмен двух элементов\n";
        cout << "8. Получить элемент по индексу\n";
        cout << "9. Получить элемент по значению\n";
        cout << "10. Вывести массив\n";
        cout << "11. Измерить скорость операций\n";
        cout << "0. Вернуться в главное меню\n";
        int choice = readInt("Выберите действие: ");

        switch (choice) {
        case 1: {
            system("cls");
            int n = readInt("Введите размер массива: ");
            arr = createRandomArr(n);
            length = n;
            cout << "Массив создан." << endl;
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            system("cls");
            arr = createHandArr(length);
            cout << "Массив создан." << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            int n = readInt("Введите размер массива: ");
            double avgTime = measure([n]() {
                int* arr = createRandomArr(n);
                delete[] arr;
                }, 100);

            cout << "Среднее время создания массива из " << n << " элементов: " << avgTime << " мкс\n";
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int index = readInt("Индекс вставки: ");
            int value = readInt("Значение (0-99): ");
            arr = insertArr(arr, index, value, length);
            printArr(arr, length);
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int index = readInt("Индекс удаления: ");
            arr = delArrIndex(arr, index, length);
            printArr(arr, length);
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int value = readInt("Значение для удаления: ");
            arr = delArrValue(arr, value, length);
            printArr(arr, length);
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int i1 = readInt("Первый индекс: ");
            int i2 = readInt("Второй индекс: ");
            swapArr(arr, i1, i2, length);
            printArr(arr, length);
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int index = readInt("Индекс: ");
            showArrIndex(arr, index, length);
            system("pause");
            system("cls");
            break;
        }
        case 9: {
            system("cls");
            if (!arr || length == 0) { cout << "Массив пуст.\n"; break; }
            printArr(arr, length);
            int value = readInt("Значение: ");
            showArrValue(arr, value, length);
            system("pause");
            system("cls");
            break;
        }
        case 10: {
            system("cls");
            printArr(arr, length);
            system("pause");
            system("cls");
            break;
        }
        case 11: {
            system("cls");
            if (!arr || length == 0) {
                cout << "Сначала создайте непустой массив.\n";
                break;
            }
            cout << "Выберите операцию для замера:\n";
            cout << "1. Вставка в середину\n";
            cout << "2. Удаление по индексу (середина)\n";
            cout << "3. Получение по индексу (середина)\n";
            int op = readInt("Операция: ");
            int repeat = readInt("Число повторений: ");
            double t;
            int mid = length / 2;
            switch (op) {
            case 1:
                t = measure([&]() {
                    arr = insertArr(arr, mid, 67, length);
                    arr = delArrIndex(arr, mid, length);
                    }, repeat);
                cout << "Среднее время вставки: " << t << " мкс\n";
                break;
            case 2:
                t = measure([&]() {
                    int val = arr[mid];
                    arr = delArrIndex(arr, mid, length);
                    arr = insertArr(arr, mid, val, length);
                    }, repeat);
                cout << "Среднее время удаления по индексу: " << t << " мкс\n";
                break;
            case 3:
                t = measure([&]() {
                    volatile int x = arr[mid];
                    }, repeat);
                cout << "Среднее время доступа по индексу: " << t << " мкс\n";
                break;
            default:
                cout << "Неверный выбор.\n";
            }
            system("pause");
            system("cls");
            break;
        }
        case 0: {
            system("cls");
            delete[] arr;
            arr = nullptr;
            length = 0;
            system("pause");
            system("cls");
            return;
        }
        default: {
            system("cls");
            cout << "Неверный выбор. Попробуйте снова.\n";
            system("pause");
            system("cls");
        }
        }
    }
}

//Двусвязный список

struct Node {
    int value;
    Node* prev;
    Node* next;
};

Node* createRandomList(int n) {
    if (n <= 0) {
        return nullptr;
    }

    Node* head = new Node{ rand() % 100, nullptr, nullptr };
    Node* tail = head;

    for (int i = 1; i < n; i++) {
        Node* newNode = new Node{ rand() % 100, tail, nullptr };
        tail->next = newNode;
        tail = newNode;
    }   
    return head;
}

Node* createHandList(int& size, int flag = -1) {
    size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    cout << "Вводите значения от 0 до 99, закончите ввод значением " << flag << endl;

    while (true) {
        int input;

        if (!(cin >> input)) {
            cout << "Ошибка ввода.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        if (input == flag) break;

        if (input < 0 || input > 99) {
            cout << "Элемент не удовлетворяет условию!\n";
            break;
        }

        Node* newNode = new Node{ input, tail, nullptr };
        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
        ++size;
    }
    return head;
}

void swapList(Node* head, int size, int firstIndex, int secondIndex) {
    if (head == nullptr || size <= 0) {
        cout << "Список пуст.\n";
        return;
    }
    if (firstIndex < 0 || firstIndex >= size || secondIndex < 0 || secondIndex >= size) {
        cout << "Индекс вне границ списка.\n";
        return;
    }
    if (firstIndex == secondIndex) return;

    Node* firstNode = head;
    for (int i = 0; i < firstIndex; i++) {
        firstNode = firstNode->next;
    }

    Node* secondNode = head;
    for (int i = 0; i < secondIndex; i++) {
        secondNode = secondNode->next;
    }

    swap(firstNode->value, secondNode->value);
}

Node* delListIndex(Node*& head, int& size, int index) {
    if (head == nullptr || size <= 0) {
        cout << "Список пуст.\n";
        return head;
    }
    if (index < 0 || index >= size) {
        cout << "Индекс вне границ списка.\n";
        return head;
    }

    Node* delNode = head;
    for (int i = 0; i < index; i++) {
        delNode = delNode->next;
    }

    if (delNode->prev != nullptr) {
        delNode->prev->next = delNode->next;
    }
    else {
        head = delNode->next;
    }

    if (delNode->next != nullptr) {
        delNode->next->prev = delNode->prev;
    }

    delete delNode;
    --size;
    return head;
}

Node* delListValue(Node*& head, int& size, int value) {
    if (head == nullptr || size <= 0) {
        cout << "Список пуст.\n";
        return head;
    }

    Node* delNode = head;
    int index = 0;
    while (delNode != nullptr && delNode->value != value) {
        delNode = delNode->next;
        ++index;
    }
    if (delNode == nullptr) {
        cout << "Значение не найдено.\n";
        return head;
    }
    return delListIndex(head, size, index);
}

void showListIndex(Node* head, int size, int index) {
    if (head == nullptr || size <= 0) {
        cout << "Cписок пуст.\n";
        return;
    }
    if (index < 0 || index >= size) {
        cout << "Индекс вне границ списка.\n";
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    cout << "Элемент с индексом " << index << ": " << current->value << endl;
}

void showListValue(Node* head, int size, int value) {
    if (head == nullptr || size <= 0) {
        cout << "Cписок пуст.\n";
        return;
    }

    Node* current = head;
    for (int i = 0; i < size; i++) {
        if (current->value == value) {
            cout << "Число " << value << " найдено по индексу: " << i << endl;
            return;
        }
        current = current->next;
    }

    cout << "Такого числа нет в списке" << endl;
}

Node* insertList(Node*& head, int& size, int index, int value) {
    if (head == nullptr && size == 0) {
        if (index != 0) {
            cout << "Список пуст, вставка возможна только на позицию 0" << endl;
            return head;
        }
        head = new Node{ value, nullptr, nullptr };
        size = 1;
        return head;
    }

    if (index < 0 || index > size) {
        cout << "Индекс вне границ списка.\n";
        return head;
    }

    if (index == 0) {
        Node* newNode = new Node{ value, nullptr, head };
        head->prev = newNode;
        head = newNode;
        ++size;
        return head;
    }

    if (index == size) {
        Node* tail = head;
        while (tail->next != nullptr) { tail = tail->next; }
        Node* newNode = new Node{ value, tail, nullptr };
        tail->next = newNode;
        tail = newNode;
        ++size;
        return head;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    Node* newNode = new Node{ value, current->prev, current };
    if (current->prev != nullptr) {
        current->prev->next = newNode;
    }
    current->prev = newNode;
    ++size;
    return head;
}

void printList(Node* head, int size) {
    if (head == nullptr || size <= 0) {
        cout << "Cписок пуст.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) cout << " ";
        current = current->next;
    }
    cout << endl;
}

void listMenu() {
    Node* head = nullptr;
    int size = 0;
    
    while (true) {
        system("cls");
        cout << "1. Создать список (случайно)\n";
        cout << "2. Создать список (вручную)\n";
        cout << "3. Измерить скорость создания (случайного)\n";
        cout << "4. Вставка элемента\n";
        cout << "5. Удаление по индексу\n";
        cout << "6. Удаление по значению\n";
        cout << "7. Обмен двух элементов\n";
        cout << "8. Получить элемент по индексу\n";
        cout << "9. Получить элемент по значению\n";
        cout << "10. Вывести список\n";
        cout << "11. Измерить скорость операций\n";
        cout << "0. Вернуться в главное меню\n";
        int choice = readInt("Выберите действие: ");

        switch (choice) {
        case 1: {
            system("cls");
            int n = readInt("Введите размер списка: ");
            if (head) {
                while (head) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                size = 0;
            }
            
            head = createRandomList(n);
            size = n;
            cout << "Список создан." << endl;
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            system("cls");
            if (head) {
                while (head) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                size = 0;
            }

            head = createHandList(size);
            cout << "Список создан." << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            int n = readInt("Введите размер для замера: ");
            auto time = measure([&]() {
                Node* h = createRandomList(n);
                int s = n;
                while (h) { Node* t = h; h = h->next; delete t; }
                }, 50);
            cout << "Среднее время создания списка из " << n << " элементов: " << time << " мкс\n";
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            system("cls");
            if (!head) { cout << "Список не создан.\n"; break; }
            printList(head, size);
            int index = readInt("Индекс вставки: ");
            int value = readInt("Значение (0-99): ");
            head = insertList(head, size, index, value);
            printList(head, size);
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            system("cls");
            if (!head || size == 0) { cout << "Список пуст.\n"; break; }
            printList(head, size);
            int index = readInt("Индекс удаления: ");
            head = delListIndex(head, size, index);
            printList(head, size);
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            system("cls");
            if (!head || size == 0) { cout << "Список пуст.\n"; break; }
            printList(head, size);
            int value = readInt("Значение для удаления: ");
            head = delListValue(head, size, value);
            printList(head, size);
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            system("cls");
            if (!head || size == 0) { cout << "Список пуст.\n"; break; }
            printList(head, size);
            int i1 = readInt("Первый индекс: ");
            int i2 = readInt("Второй индекс: ");
            swapList(head, size, i1, i2);
            printList(head, size);
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            system("cls");
            if (!head || size == 0) { cout << "Список пуст.\n"; break; }
            printList(head, size);
            int index = readInt("Индекс: ");
            showListIndex(head, size, index);
            system("pause");
            system("cls");
            break;
        }
        case 9: {
            system("cls");
            if (!head || size == 0) { cout << "Список пуст.\n"; break; }
            printList(head, size);
            int value = readInt("Значение: ");
            showListValue(head, size, value);
            system("pause");
            system("cls");
            break;
        }
        case 10: {
            system("cls");
            printList(head, size);
            system("pause");
            system("cls");
            break;
        }
        case 11: {
            system("cls");
            if (!head || size == 0) {
                cout << "Сначала создайте непустой список.\n";
                break;
            }
            cout << "Выберите операцию для замера:\n";
            cout << "1. Вставка в середину\n";
            cout << "2. Удаление по индексу (середина)\n";
            cout << "3. Получение по индексу (середина)\n";
            int op = readInt("Операция: ");
            int repeat = readInt("Число повторений: ");
            double t;
            int mid = size / 2;
            switch (op) {
            case 1:
                t = measure([&]() {
                    Node* h = insertList(head, size, mid, 777);
                    h = delListIndex(head, size, mid);
                    }, repeat);
                cout << "Среднее время вставки: " << t << " мкс\n";
                break;
            case 2:
                t = measure([&]() {
                    int val = 0;
                    {
                        Node* cur = head;
                        for (int i = 0; i < mid; ++i) cur = cur->next;
                        val = cur->value;
                    }
                    head = delListIndex(head, size, mid);
                    head = insertList(head, size, mid, val);
                    }, repeat);
                cout << "Среднее время удаления по индексу: " << t << " мкс\n";
                break;
            case 3:
                t = measure([&]() {
                    Node* cur = head;
                    for (int i = 0; i < mid; ++i) cur = cur->next;
                    volatile int x = cur->value;
                    }, repeat);
                cout << "Среднее время доступа по индексу: " << t << " мкс\n";
                break;
            default:
                cout << "Неверный выбор.\n";
            }
            system("pause");
            system("cls");
            break;
        }
        case 0: {
            system("cls");
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            system("pause");
            system("cls");
            return;
        }
        default: {
            system("cls");
            cout << "Неверный выбор. Попробуйте снова.\n";
            system("pause");
            system("cls");
        }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));

    while (true) {
        cout << "1) Работа с двусвязным списком\n";
        cout << "2) Работа с динамическим массивом\n";
        cout << "3) ИДЗ\n";
        cout << "0) Выход из программы\n";
        int choice = readInt("Ваш выбор: ");
        switch (choice) {
        case 1: listMenu(); break;
        case 2: arrMenu(); break;
        case 3: {
            system("cls");
            idsMenu(); 
            system("pause");
            system("cls");
            break;
        }
        case 0: return 0;
        default: cout << "Неверный выбор.\n";
        }
    }
}
