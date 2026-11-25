#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

struct TNode {
    int key;
    int height;
    TNode* left;
    TNode* right;

    explicit TNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    TNode* root;
    char name[20];

    int getHeight(TNode* node) const;
    int getBalance(TNode* node) const;
    TNode* rightRotate(TNode* y);
    TNode* leftRotate(TNode* x);
    TNode* insertNode(TNode* node, int key);
    TNode* minValueNode(TNode* node) const;
    TNode* removeNode(TNode* node, int key, bool& removed);
    TNode* searchNode(TNode* node, int key) const;
    void freeTree(TNode* node);
    void printHorizontal(TNode* node, int level) const;
    void saveNodes(TNode* node, std::ofstream& file) const;
    void countNodes(TNode* node, int& count) const;

public:
    AVLTree();
    ~AVLTree();

    void setName(const char* n);
    const char* getName() const;
    void create();
    void insert(int key);
    bool remove(int key);
    bool search(int key) const;
    void destroy();
    void print() const;
    TNode* getRoot() const;
    int getCount() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // TREE_H
