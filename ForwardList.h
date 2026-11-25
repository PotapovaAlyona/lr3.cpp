#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>

struct Node {
    std::string key;
    Node* next;
    explicit Node(const std::string& k) : key(k), next(nullptr) {}
};

class ForwardList {
private:
    Node* head;
    char name[20];

public:
    ForwardList();
    ~ForwardList();

    void setName(const char* n);
    const char* getName() const;

    void create(const std::string& keyBegin);
    void addNode(Node* targetNode, const std::string& key);
    void addToEnd(const std::string& key);
    void addToBeginning(const std::string& key);
    void addBeforeNode(Node* targetNode, const std::string& key);

    void deleteAfterNode(Node* targetNode);
    void deleteHead();
    void deleteTail();
    void deleteBeforeNode(Node* targetNode);
    bool deleteByValue(const std::string& value);

    Node* findNodeByValue(const std::string& value) const;
    void print() const;
    Node* getFirst() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // FORWARDLIST_H
