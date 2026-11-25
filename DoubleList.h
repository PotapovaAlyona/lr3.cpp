#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

struct DNode {
    std::string key;
    DNode* next;
    DNode* prev;
    explicit DNode(const std::string& k) : key(k), next(nullptr), prev(nullptr) {}
};

class DoubleList {
private:
    DNode* head;
    DNode* tail;
    char name[20];

public:
    DoubleList();
    ~DoubleList();

    void setName(const char* n);
    const char* getName() const;

    void create(const std::string& keyBegin);
    void addToEnd(const std::string& key);
    void addToBeginning(const std::string& key);
    void addBeforeNode(DNode* targetNode, const std::string& key);
    void addAfterNode(DNode* targetNode, const std::string& key);

    void deleteHead();
    void deleteTail();
    void deleteBeforeNode(DNode* targetNode);
    void deleteAfterNode(DNode* targetNode);
    bool deleteByValue(const std::string& value);

    DNode* findNodeByValue(const std::string& value) const;
    void print() const;
    DNode* getFirst() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // DOUBLELIST_H
