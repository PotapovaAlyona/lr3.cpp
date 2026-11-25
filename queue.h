#ifndef QUEUE_H
#define QUEUE_H

#include "ForwardList.h"

class Queue {
private:
    Node* front;
    Node* rear;
    char name[20];

public:
    Queue();
    ~Queue();

    void setName(const char* n);
    const char* getName() const;
    void create();

    void enqueue(const std::string& data);
    std::string dequeue();
    std::string peek() const;
    void print() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif 