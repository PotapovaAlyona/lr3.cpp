#include "ForwardList.h"

ForwardList::ForwardList() : head(nullptr) {
    name[0] = '\0';
}

ForwardList::~ForwardList() {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

void ForwardList::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* ForwardList::getName() const {
    return name;
}

void ForwardList::create(const std::string& keyBegin) {
    while (head != nullptr) deleteHead();
    head = new Node(keyBegin);
}

void ForwardList::addNode(Node* targetNode, const std::string& key) {
    if (targetNode == nullptr) return;
    Node* newNode = new Node(key);
    newNode->next = targetNode->next;
    targetNode->next = newNode;
}

void ForwardList::addToEnd(const std::string& key) {
    Node* newNode = new Node(key);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

void ForwardList::addToBeginning(const std::string& key) {
    Node* newNode = new Node(key);
    newNode->next = head;
    head = newNode;
}

void ForwardList::addBeforeNode(Node* targetNode, const std::string& key) {
    if (targetNode == nullptr || head == nullptr) return;
    if (head == targetNode) {
        addToBeginning(key);
        return;
    }
    Node* prev = head;
    while (prev->next != nullptr && prev->next != targetNode) {
        prev = prev->next;
    }
    if (prev->next == targetNode) {
        Node* newNode = new Node(key);
        newNode->next = targetNode;
        prev->next = newNode;
    }
}

void ForwardList::deleteAfterNode(Node* targetNode) {
    if (targetNode == nullptr || targetNode->next == nullptr) return;
    Node* toDelete = targetNode->next;
    targetNode->next = toDelete->next;
    delete toDelete;
}

void ForwardList::deleteHead() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

void ForwardList::deleteTail() {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

void ForwardList::deleteBeforeNode(Node* targetNode) {
    if (targetNode == nullptr || head == nullptr || head == targetNode) return;
    if (head->next == targetNode) {
        deleteHead();
        return;
    }
    Node* prev = head;
    while (prev->next != nullptr && prev->next->next != targetNode) {
        prev = prev->next;
    }
    if (prev->next != nullptr && prev->next->next == targetNode) {
        Node* toDelete = prev->next;
        prev->next = targetNode;
        delete toDelete;
    }
}

bool ForwardList::deleteByValue(const std::string& value) {
    if (head == nullptr) return false;
    if (head->key == value) {
        deleteHead();
        return true;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->key != value) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        return true;
    }
    return false;
}

Node* ForwardList::findNodeByValue(const std::string& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->key == value) return current;
        current = current->next;
    }
    return nullptr;
}

void ForwardList::print() const {
    std::cout << "Односвязный список " << name << ": ";
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->key << " -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

Node* ForwardList::getFirst() const {
    return head;
}

void ForwardList::save(std::ofstream& file) const {
    int count = 0;
    for (Node* c = head; c != nullptr; c = c->next) count++;
    file << name << " " << count << " ";
    for (Node* c = head; c != nullptr; c = c->next) file << c->key << " ";
    file << "\n";
}

void ForwardList::load(std::ifstream& file) {
    while (head != nullptr) deleteHead();
    int count = 0;
    if (!(file >> name >> count)) return;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) addToEnd(val);
    }
}
