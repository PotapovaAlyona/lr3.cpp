#include "HashTable.h"

// --- ChainHashTable ---

ChainHashTable::ChainHashTable() : tableSize(10), elementCount(0) {
    table = new ChainNode*[tableSize];
    for (int i = 0; i < tableSize; ++i) table[i] = nullptr;
    tableName[0] = '\0';
}

ChainHashTable::ChainHashTable(int size) : elementCount(0) {
    if (size <= 0) size = 10;
    tableSize = size;
    table = new ChainNode*[tableSize];
    for (int i = 0; i < tableSize; ++i) table[i] = nullptr;
    tableName[0] = '\0';
}

ChainHashTable::~ChainHashTable() {
    for (int i = 0; i < tableSize; ++i) {
        ChainNode* curr = table[i];
        while (curr != nullptr) {
            ChainNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    delete[] table;
}

int ChainHashTable::hashFunction(const char* key) const {
    unsigned long hash = 5381;
    int c;
    while ((c = static_cast<unsigned char>(*key++))) {
        hash = ((hash << 5) + hash) + c;
    }
    return static_cast<int>(hash % tableSize);
}

void ChainHashTable::setName(const char* name) {
    std::strncpy(tableName, name, 19);
    tableName[19] = '\0';
}

const char* ChainHashTable::getName() const {
    return tableName;
}

void ChainHashTable::insert(const char* key) {
    if (contains(key)) return;
    int idx = hashFunction(key);
    auto* newNode = new ChainNode(key);
    newNode->next = table[idx];
    table[idx] = newNode;
    elementCount++;
}

bool ChainHashTable::contains(const char* key) const {
    int idx = hashFunction(key);
    ChainNode* curr = table[idx];
    while (curr != nullptr) {
        if (std::strcmp(curr->key, key) == 0) return true;
        curr = curr->next;
    }
    return false;
}

bool ChainHashTable::remove(const char* key) {
    int idx = hashFunction(key);
    ChainNode* curr = table[idx];
    ChainNode* prev = nullptr;
    while (curr != nullptr) {
        if (std::strcmp(curr->key, key) == 0) {
            if (prev == nullptr) table[idx] = curr->next;
            else prev->next = curr->next;
            delete curr;
            elementCount--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void ChainHashTable::print() const {
    std::cout << "Хеш-таблица (цепочки) " << tableName << ":\n";
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr) {
            std::cout << "  [" << i << "]: ";
            for (ChainNode* c = table[i]; c != nullptr; c = c->next) {
                std::cout << c->key << " -> ";
            }
            std::cout << "NULL\n";
        }
    }
}

void ChainHashTable::save(std::ofstream& file) const {
    file << tableName << " " << elementCount << " ";
    for (int i = 0; i < tableSize; ++i) {
        for (ChainNode* c = table[i]; c != nullptr; c = c->next) {
            file << c->key << " ";
        }
    }
    file << "\n";
}

void ChainHashTable::load(std::ifstream& file) {
    int count = 0;
    if (!(file >> tableName >> count)) return;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) insert(val.c_str());
    }
}

// --- OpenHashTable ---

OpenHashTable::OpenHashTable() : tableSize(10), elementCount(0) {
    table = new char*[tableSize];
    for (int i = 0; i < tableSize; ++i) table[i] = nullptr;
    tableName[0] = '\0';
}

OpenHashTable::OpenHashTable(int size) : elementCount(0) {
    if (size <= 0) size = 10;
    tableSize = size;
    table = new char*[tableSize];
    for (int i = 0; i < tableSize; ++i) table[i] = nullptr;
    tableName[0] = '\0';
}

OpenHashTable::~OpenHashTable() {
    for (int i = 0; i < tableSize; ++i) {
        delete[] table[i];
    }
    delete[] table;
}

int OpenHashTable::hashFunction(const char* key) const {
    unsigned long hash = 5381;
    int c;
    while ((c = static_cast<unsigned char>(*key++))) {
        hash = ((hash << 5) + hash) + c;
    }
    return static_cast<int>(hash % tableSize);
}

void OpenHashTable::setName(const char* name) {
    std::strncpy(tableName, name, 19);
    tableName[19] = '\0';
}

const char* OpenHashTable::getName() const {
    return tableName;
}

void OpenHashTable::insert(const char* key) {
    if (elementCount >= tableSize || contains(key)) return;
    int idx = hashFunction(key);
    for (int i = 0; i < tableSize; ++i) {
        int probe = (idx + i) % tableSize;
        if (table[probe] == nullptr) {
            table[probe] = new char[std::strlen(key) + 1];
            std::strcpy(table[probe], key);
            elementCount++;
            return;
        }
    }
}

bool OpenHashTable::contains(const char* key) const {
    int idx = hashFunction(key);
    for (int i = 0; i < tableSize; ++i) {
        int probe = (idx + i) % tableSize;
        if (table[probe] != nullptr && std::strcmp(table[probe], key) == 0) {
            return true;
        }
    }
    return false;
}

bool OpenHashTable::remove(const char* key) {
    int idx = hashFunction(key);
    for (int i = 0; i < tableSize; ++i) {
        int probe = (idx + i) % tableSize;
        if (table[probe] != nullptr && std::strcmp(table[probe], key) == 0) {
            delete[] table[probe];
            table[probe] = nullptr;
            elementCount--;
            return true;
        }
    }
    return false;
}

void OpenHashTable::print() const {
    std::cout << "Хеш-таблица (открытая адресация) " << tableName << ":\n";
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr) {
            std::cout << "  [" << i << "]: " << table[i] << "\n";
        }
    }
}

void OpenHashTable::save(std::ofstream& file) const {
    file << tableName << " " << elementCount << " ";
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr) file << table[i] << " ";
    }
    file << "\n";
}

void OpenHashTable::load(std::ifstream& file) {
    int count = 0;
    if (!(file >> tableName >> count)) return;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) insert(val.c_str());
    }
}
