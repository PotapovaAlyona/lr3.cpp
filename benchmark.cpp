#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include "array.h"
#include "ForwardList.h"
#include "DoubleList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "HashTable.h"

using namespace std::chrono;

int main() {
    std::cout << "Запуск бенчмарков C++...\n\n";
    std::cout << "| Структура   | Время (μs) | Операции |\n";
    std::cout << "|-------------|------------|----------|\n";

    {
        ForwardList fl;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1500; ++i) fl.addToEnd("val_" + std::to_string(i));
        auto end = high_resolution_clock::now();
        std::cout << "| ForwardList | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 1500 << " |\n";
    }
    {
        DoubleList dl;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1500; ++i) dl.addToEnd("val_" + std::to_string(i));
        auto end = high_resolution_clock::now();
        std::cout << "| DoubleList  | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 1500 << " |\n";
    }
    {
        Stack st;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 3750; ++i) st.push("val");
        for (int i = 0; i < 3750; ++i) st.pop();
        auto end = high_resolution_clock::now();
        std::cout << "| Stack       | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 7500 << " |\n";
    }
    {
        Queue q;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 3750; ++i) q.enqueue("val");
        for (int i = 0; i < 3750; ++i) q.dequeue();
        auto end = high_resolution_clock::now();
        std::cout << "| Queue       | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 7500 << " |\n";
    }
    {
        AVLTree tree;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1500; ++i) tree.insert(i);
        auto end = high_resolution_clock::now();
        std::cout << "| AVLTree     | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 1500 << " |\n";
    }
    {
        DynamicArray arr;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 2500; ++i) arr.addToEnd("val");
        auto end = high_resolution_clock::now();
        std::cout << "| DynamicArr  | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 2500 << " |\n";
    }
    {
        ChainHashTable cht(500);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1500; ++i) cht.insert(("key_" + std::to_string(i)).c_str());
        auto end = high_resolution_clock::now();
        std::cout << "| HashTable   | " << std::setw(10) << duration_cast<microseconds>(end - start).count()
                  << " | " << std::setw(8) << 1500 << " |\n";
    }

    std::cout << "\nВсе бенчмарки завершены.\n";
    return 0;
}
