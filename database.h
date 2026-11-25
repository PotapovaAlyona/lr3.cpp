#ifndef DATABASE_H
#define DATABASE_H

#include <sstream>
#include "array.h"
#include "ForwardList.h"
#include "DoubleList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "HashTable.h"

constexpr int MAX_STRUCTURES = 10;

class Database {
private:
    DynamicArray arrays[MAX_STRUCTURES];
    ForwardList forwardLists[MAX_STRUCTURES];
    DoubleList doubleLists[MAX_STRUCTURES];
    Stack stacks[MAX_STRUCTURES];
    Queue queues[MAX_STRUCTURES];
    AVLTree trees[MAX_STRUCTURES];
    ChainHashTable chainTables[MAX_STRUCTURES];
    OpenHashTable openTables[MAX_STRUCTURES];

    int arrayCount;
    int forwardListCount;
    int doubleListCount;
    int stackCount;
    int queueCount;
    int treeCount;
    int chainTableCount;
    int openTableCount;

    DynamicArray* findArray(const char* name);
    ForwardList* findForwardList(const char* name);
    DoubleList* findDoubleList(const char* name);
    Stack* findStack(const char* name);
    Queue* findQueue(const char* name);
    AVLTree* findTree(const char* name);
    ChainHashTable* findChainTable(const char* name);
    OpenHashTable* findOpenTable(const char* name);

public:
    Database();
    ~Database();

    void init();
    void destroy();
    void processCommand(const std::string& command);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // DATABASE_H
