#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    int x;         // Ключ
    int data;      // Дополнительные данные
    Node* left;    // Левый сын
    Node* right;   // Правый сын
    Node* parent;  // Родитель

    // Конструктор для удобства
    Node(int key, int value, Node* p = nullptr)
        : x(key), data(value), left(nullptr), right(nullptr), parent(p) {}
};

Node* find(Node* root, int x) {
    Node* current = root;
    while (current != nullptr) {
        if (x == current->x) {
            return current; // Найден ключ
        } else if (x < current->x) {
            current = current->left; // Переход влево
        } else {
            current = current->right; // Переход вправо
        }
    }
    return nullptr; // Ключ не найден
}

void add(Node*& root, int x, int data) {
    Node* parent = nullptr;
    Node* current = root;

    // Находим место для вставки
    while (current != nullptr) {
        parent = current;
        if (x < current->x) {
            current = current->left;
        } else if (x > current->x) {
            current = current->right;
        } else {
            // Если ключ уже существует, просто обновляем данные
            current->data = data;
            return;
        }
    }

    // Создаем новую вершину
    Node* newNode = new Node(x, data, parent);

    // Подвешиваем новую вершину к родителю
    if (parent == nullptr) {
        root = newNode; // Дерево было пустым
    } else if (x < parent->x) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}


Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void del(Node*& root, int x) {
    // Находим удаляемую вершину
    Node* node = find(root, x);
    if (node == nullptr) return; // Ключ не найден

    // Случай 1: У вершины нет детей или есть только один ребенок
    if (node->left == nullptr || node->right == nullptr) {
        Node* child = (node->left != nullptr) ? node->left : node->right;

        if (node->parent == nullptr) {
            root = child; // Удаляем корень
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }

        if (child != nullptr) {
            child->parent = node->parent; // Обновляем родителя ребенка
        }

        delete node;
    } else {
        // Случай 2: У вершины два ребенка
        Node* nextNode = findMin(node->right); // Находим следующую вершину

        // Меняем ключи и данные
        node->x = nextNode->x;
        node->data = nextNode->data;

        // Удаляем nextNode (у неё нет левого ребенка)
        if (nextNode->parent->left == nextNode) {
            nextNode->parent->left = nextNode->right;
        } else {
            nextNode->parent->right = nextNode->right;
        }

        if (nextNode->right != nullptr) {
            nextNode->right->parent = nextNode->parent; // Обновляем родителя правого ребенка
        }

        delete nextNode;
    }
}
Node* lowerBound(Node* root, int x) {
    Node* current = root;
    Node* result = nullptr;

    while (current != nullptr) {
        if (x <= current->x) {
            result = current; // Запоминаем текущий как потенциальный ответ
            current = current->left; // Продолжаем искать меньший ключ
        } else {
            current = current->right; // Ищем больший ключ
        }
    }

    return result; // Возвращаем результат
}

Node* next(Node* node) {
    if (node->right != nullptr) {
        // Если есть правый сын, идем в него и до упора влево
        node = node->right;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Если правого сына нет, идем вверх, пока не найдем больший ключ
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

void inOrderTraversal(Node* root) {
    if (root == nullptr) return;

    inOrderTraversal(root->left);   // Обходим левое поддерево
    std::cout << root->x << " ";    // Посещаем текущую вершину
    inOrderTraversal(root->right);  // Обходим правое поддерево
}


int main() {
    Node* root = nullptr;

    // Добавляем элементы
    add(root, 8, 80);
    add(root, 3, 30);
    add(root, 10, 100);
    add(root, 1, 10);
    add(root, 6, 60);
    add(root, 14, 140);
    add(root, 4, 40);
    add(root, 7, 70);

    // Симметричный обход
    std::cout << "In-order traversal: ";
    inOrderTraversal(root);
    std::cout << std::endl;

    // Поиск
    Node* found = find(root, 6);
    if (found) std::cout << "Found: " << found->x << std::endl;

    // LowerBound
    Node* lb = lowerBound(root, 5);
    if (lb) std::cout << "LowerBound(5): " << lb->x << std::endl;

    // Удаление
    del(root, 6);
    std::cout << "After deleting 6: ";
    inOrderTraversal(root);
    std::cout << std::endl;

    return 0;
}