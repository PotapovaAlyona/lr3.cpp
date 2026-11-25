#include "stack.h"

Stack::Stack() : top(nullptr) {
    name[0] = '\0';
}

Stack::~Stack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* Stack::getName() const {
    return name;
}

void Stack::create() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(const std::string& data) {
    Node* newNode = new Node(data);
    newNode->next = top;
    top = newNode;
}

std::string Stack::pop() {
    if (top == nullptr) {
        throw std::runtime_error("Извлечение из пустого стека");
    }
    Node* temp = top;
    std::string data = temp->key;
    top = top->next;
    delete temp;
    return data;
}

std::string Stack::peek() const {
    if (top == nullptr) {
        throw std::runtime_error("Стек пустой");
    }
    return top->key;
}

void Stack::print() const {
    std::cout << "Стек " << name << " (сверху вниз): ";
    Node* current = top;
    while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void Stack::save(std::ofstream& file) const {
    int count = 0;
    for (Node* c = top; c != nullptr; c = c->next) count++;
    file << name << " " << count << " ";
    for (Node* c = top; c != nullptr; c = c->next) file << c->key << " ";
    file << "\n";
}

void Stack::load(std::ifstream& file) {
    create();
    int count = 0;
    if (!(file >> name >> count)) return;
    auto* temp = new std::string[count > 0 ? count : 1];
    for (int i = 0; i < count; ++i) {
        file >> temp[i];
    }
    for (int i = count - 1; i >= 0; --i) {
        push(temp[i]);
    }
    delete[] temp;
}
