#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include "array.h"
#include "ForwardList.h"
#include "DoubleList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "HashTable.h"

class Serializer {
public:
    // Текстовый формат
    static void saveArrayText(const DynamicArray& arr, const std::string& filename);
    static void loadArrayText(DynamicArray& arr, const std::string& filename);

    static void saveTreeText(const AVLTree& tree, const std::string& filename);
    static void loadTreeText(AVLTree& tree, const std::string& filename);

    // Бинарный формат
    static void saveArrayBinary(const DynamicArray& arr, const std::string& filename);
    static void loadArrayBinary(DynamicArray& arr, const std::string& filename);

    static void saveTreeBinary(const AVLTree& tree, const std::string& filename);
    static void loadTreeBinary(AVLTree& tree, const std::string& filename);

    static void saveHashBinary(const ChainHashTable& ht, const std::string& filename);
    static void loadHashBinary(ChainHashTable& ht, const std::string& filename);
};

#endif
