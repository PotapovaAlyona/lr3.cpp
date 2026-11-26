#include "serializer.h"
#include <fstream>
#include <vector>
#include <cstdint>

namespace {
void writeStringBinary(std::ofstream& out, const std::string& s) {
    uint32_t len = static_cast<uint32_t>(s.size());
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        out.write(s.data(), len);
    }
}

std::string readStringBinary(std::ifstream& in) {
    uint32_t len = 0;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len == 0) {
        return "";
    }
    std::vector<char> buf(len);
    in.read(buf.data(), len);
    return std::string(buf.begin(), buf.end());
}

void writeTreeNodesBinary(std::ofstream& out, TNode* node) {
    if (!node) return;
    int32_t key = node->key;
    out.write(reinterpret_cast<const char*>(&key), sizeof(key));
    writeTreeNodesBinary(out, node->left);
    writeTreeNodesBinary(out, node->right);
}
} // namespace

// --- Текстовый формат ---

void Serializer::saveArrayText(const DynamicArray& arr, const std::string& filename) {
    std::ofstream out(filename);
    arr.save(out);
}

void Serializer::loadArrayText(DynamicArray& arr, const std::string& filename) {
    std::ifstream in(filename);
    arr.load(in);
}

void Serializer::saveTreeText(const AVLTree& tree, const std::string& filename) {
    std::ofstream out(filename);
    tree.save(out);
}

void Serializer::loadTreeText(AVLTree& tree, const std::string& filename) {
    std::ifstream in(filename);
    tree.load(in);
}

// --- Бинарный формат ---

void Serializer::saveArrayBinary(const DynamicArray& arr, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    writeStringBinary(out, arr.getName());
    uint32_t count = static_cast<uint32_t>(arr.getLength());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (uint32_t i = 0; i < count; ++i) {
        writeStringBinary(out, arr.getElement(i));
    }
}

void Serializer::loadArrayBinary(DynamicArray& arr, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    std::string name = readStringBinary(in);
    arr.setName(name.c_str());
    uint32_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (uint32_t i = 0; i < count; ++i) {
        arr.addToEnd(readStringBinary(in));
    }
}

void Serializer::saveTreeBinary(const AVLTree& tree, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    writeStringBinary(out, tree.getName());
    uint32_t count = static_cast<uint32_t>(tree.getCount());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    writeTreeNodesBinary(out, tree.getRoot());
}

void Serializer::loadTreeBinary(AVLTree& tree, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    std::string name = readStringBinary(in);
    tree.setName(name.c_str());
    tree.create();
    uint32_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (uint32_t i = 0; i < count; ++i) {
        int32_t key = 0;
        in.read(reinterpret_cast<char*>(&key), sizeof(key));
        tree.insert(key);
    }
}

void Serializer::saveHashBinary(const ChainHashTable& ht, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    ht.save(out);
}

void Serializer::loadHashBinary(ChainHashTable& ht, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    ht.load(in);
}
