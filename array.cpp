#include "array.h"

DynamicArray::DynamicArray(int initialCapacity) {
    if (initialCapacity <= 0) initialCapacity = 1;
    data = new std::string[initialCapacity];
    capacity = initialCapacity;
    size = 0;
    name[0] = '\0';
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* DynamicArray::getName() const {
    return name;
}

void DynamicArray::resizeIfNeeded() {
    if (size >= capacity) {
        int newCapacity = capacity * 2;
        auto* newData = new std::string[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

void DynamicArray::addToEnd(const std::string& value) {
    resizeIfNeeded();
    data[size++] = value;
}

void DynamicArray::addAtIndex(int index, const std::string& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    resizeIfNeeded();
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::removeAtIndex(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

std::string DynamicArray::getElement(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

void DynamicArray::setElement(int index, const std::string& value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    data[index] = value;
}

int DynamicArray::getLength() const {
    return size;
}

void DynamicArray::print() const {
    std::cout << "Массив " << name << ": [ ";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << (i + 1 < size ? ", " : " ");
    }
    std::cout << "]\n";
}

void DynamicArray::save(std::ofstream& file) const {
    file << name << " " << size << " ";
    for (int i = 0; i < size; ++i) {
        file << data[i] << " ";
    }
    file << "\n";
}

void DynamicArray::load(std::ifstream& file) {
    int count = 0;
    if (!(file >> name >> count)) return;
    size = 0;
    for (int i = 0; i < count; ++i) {
        std::string val;
        if (file >> val) addToEnd(val);
    }
}
