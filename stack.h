#ifndef STACK_H
#define STACK_H

#include "ForwardList.h"

class Stack {
private:
    Node* top;
    char name[20];

public:
    Stack();
    ~Stack();

    void setName(const char* n);
    const char* getName() const;
    void create();

    void push(const std::string& data);
    std::string pop();
    std::string peek() const;
    void print() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif
