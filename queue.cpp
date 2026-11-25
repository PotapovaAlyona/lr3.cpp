#include "queue.h"

Queue::Queue() : front(nullptr), rear(nullptr) {
    name[0] = '\0';
}

Queue::~Queue() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

void Queue::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* Queue::getName() const {
    return name;
}

void Queue::create() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

void Queue::enqueue(const std::string& data) {
    Node* newNode = new Node(data);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

std::string Queue::dequeue() {
    if (front == nullptr) {
        throw std::runtime_error("Извлечение из пустой очереди");
    }
    Node* temp = front;
    std::string data = temp->key;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    return data;
}

std::string Queue::peek() const {
    if (front == nullptr) {
        throw std::runtime_error("Очередь пуста");
    }
    return front->key;
}

void Queue::print() const {
    std::cout << "Очередь " << name << ": ";
    Node* current = front;
    while (current != nullptr) {
        std::cout << current->key << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void Queue::save(std::ofstream& file) const {
    int count = 0;
    for (Node* c = front; c != nullptr; c = c->next) count++;
    file << name << " " << count << " ";
    for (Node* c = front; c != nullptr; c = c->next) file << c->key << " ";
    file << "\n";
}

void Queue::load(std::ifstream& file) {
    create();
    int count = 0;
    if (!(file >> name >> count)) return;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) enqueue(val);
    }
}
