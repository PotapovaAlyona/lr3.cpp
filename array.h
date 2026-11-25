#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>

class DynamicArray {
private:
    std::string* data;
    int capacity;
    int size;
    char name[20];

    void resizeIfNeeded();

public:
    explicit DynamicArray(int initialCapacity = 10);
    ~DynamicArray();
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;


    void setName(const char* n);
    const char* getName() const;

    void addToEnd(const std::string& value);
    void addAtIndex(int index, const std::string& value);
    void removeAtIndex(int index);
    std::string getElement(int index) const;
    void setElement(int index, const std::string& value);
    int getLength() const;
    void print() const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // ARRAY_H
