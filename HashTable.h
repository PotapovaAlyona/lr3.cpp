#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <cstring>

struct ChainNode {
    char* key;
    ChainNode* next;

    explicit ChainNode(const char* k) {
        key = new char[std::strlen(k) + 1];
        std::strcpy(key, k);
        next = nullptr;
    }

    ~ChainNode() {
        delete[] key;
    }

    ChainNode(const ChainNode&) = delete;
    ChainNode& operator=(const ChainNode&) = delete;
};

class ChainHashTable {
private:
    ChainNode** table;
    int tableSize;
    int elementCount;
    char tableName[20];

    int hashFunction(const char* key) const;

public:
    ChainHashTable();
    explicit ChainHashTable(int size);
    ~ChainHashTable();
    ChainHashTable(const ChainHashTable&) = delete;
    ChainHashTable& operator=(const ChainHashTable&) = delete;

    void setName(const char* name);
    const char* getName() const;

    void insert(const char* key);
    bool contains(const char* key) const;
    bool remove(const char* key);
    void print() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

class OpenHashTable {
private:
    char** table;
    int tableSize;
    int elementCount;
    char tableName[20];

    int hashFunction(const char* key) const;

public:
    OpenHashTable();
    explicit OpenHashTable(int size);
    ~OpenHashTable();
    OpenHashTable(const OpenHashTable&) = delete;
    OpenHashTable& operator=(const OpenHashTable&) = delete;

    void setName(const char* name);
    const char* getName() const;

    void insert(const char* key);
    bool contains(const char* key) const;
    bool remove(const char* key);
    void print() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // HASHTABLE_H
