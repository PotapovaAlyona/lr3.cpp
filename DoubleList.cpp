#include "DoubleList.h"

DoubleList::DoubleList() : head(nullptr), tail(nullptr) {
    name[0] = '\0';
}

DoubleList::~DoubleList() {
    while (head != nullptr) {
        DNode* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
}

void DoubleList::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* DoubleList::getName() const {
    return name;
}

void DoubleList::create(const std::string& keyBegin) {
    while (head != nullptr) deleteHead();
    auto* newNode = new DNode(keyBegin);
    head = tail = newNode;
}

void DoubleList::addToEnd(const std::string& key) {
    auto* newNode = new DNode(key);
    if (head == nullptr) {
        head = tail = newNode;
        return;
    }
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

void DoubleList::addToBeginning(const std::string& key) {
    auto* newNode = new DNode(key);
    if (head == nullptr) {
        head = tail = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void DoubleList::addBeforeNode(DNode* targetNode, const std::string& key) {
    if (targetNode == nullptr) return;
    if (targetNode == head) {
        addToBeginning(key);
        return;
    }
    auto* newNode = new DNode(key);
    newNode->prev = targetNode->prev;
    newNode->next = targetNode;
    targetNode->prev->next = newNode;
    targetNode->prev = newNode;
}

void DoubleList::addAfterNode(DNode* targetNode, const std::string& key) {
    if (targetNode == nullptr) return;
    if (targetNode == tail) {
        addToEnd(key);
        return;
    }
    auto* newNode = new DNode(key);
    newNode->next = targetNode->next;
    newNode->prev = targetNode;
    targetNode->next->prev = newNode;
    targetNode->next = newNode;
}

void DoubleList::deleteHead() {
    if (head == nullptr) return;
    DNode* temp = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
}

void DoubleList::deleteTail() {
    if (tail == nullptr) return;
    DNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr;
    delete temp;
}

void DoubleList::deleteBeforeNode(DNode* targetNode) {
    if (targetNode == nullptr || targetNode->prev == nullptr) return;
    DNode* toDelete = targetNode->prev;
    if (toDelete == head) {
        deleteHead();
    } else {
        toDelete->prev->next = targetNode;
        targetNode->prev = toDelete->prev;
        delete toDelete;
    }
}

void DoubleList::deleteAfterNode(DNode* targetNode) {
    if (targetNode == nullptr || targetNode->next == nullptr) return;
    DNode* toDelete = targetNode->next;
    if (toDelete == tail) {
        deleteTail();
    } else {
        toDelete->next->prev = targetNode;
        targetNode->next = toDelete->next;
        delete toDelete;
    }
}

bool DoubleList::deleteByValue(const std::string& value) {
    DNode* target = findNodeByValue(value);
    if (target == nullptr) return false;
    if (target == head) {
        deleteHead();
    } else if (target == tail) {
        deleteTail();
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        delete target;
    }
    return true;
}

DNode* DoubleList::findNodeByValue(const std::string& value) const {
    DNode* current = head;
    while (current != nullptr) {
        if (current->key == value) return current;
        current = current->next;
    }
    return nullptr;
}

void DoubleList::print() const {
    std::cout << "Двусвязный список " << name << ": NULL <-> ";
    DNode* current = head;
    while (current != nullptr) {
        std::cout << current->key << " <-> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

DNode* DoubleList::getFirst() const {
    return head;
}

void DoubleList::save(std::ofstream& file) const {
    int count = 0;
    for (DNode* c = head; c != nullptr; c = c->next) count++;
    file << name << " " << count << " ";
    for (DNode* c = head; c != nullptr; c = c->next) file << c->key << " ";
    file << "\n";
}

void DoubleList::load(std::ifstream& file) {
    while (head != nullptr) deleteHead();
    int count = 0;
    if (!(file >> name >> count)) return;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) addToEnd(val);
    }
}
