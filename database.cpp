#include "database.h"

Database::Database() {
    init();
}

Database::~Database() {
    destroy();
}

void Database::init() {
    arrayCount = forwardListCount = doubleListCount = 0;
    stackCount = queueCount = treeCount = 0;
    chainTableCount = openTableCount = 0;
}

void Database::destroy() {
    for (int i = 0; i < treeCount; ++i) trees[i].destroy();
    init();
}

DynamicArray* Database::findArray(const char* name) {
    for (int i = 0; i < arrayCount; ++i)
        if (std::strcmp(arrays[i].getName(), name) == 0) return &arrays[i];
    return nullptr;
}

ForwardList* Database::findForwardList(const char* name) {
    for (int i = 0; i < forwardListCount; ++i)
        if (std::strcmp(forwardLists[i].getName(), name) == 0) return &forwardLists[i];
    return nullptr;
}

DoubleList* Database::findDoubleList(const char* name) {
    for (int i = 0; i < doubleListCount; ++i)
        if (std::strcmp(doubleLists[i].getName(), name) == 0) return &doubleLists[i];
    return nullptr;
}

Stack* Database::findStack(const char* name) {
    for (int i = 0; i < stackCount; ++i)
        if (std::strcmp(stacks[i].getName(), name) == 0) return &stacks[i];
    return nullptr;
}

Queue* Database::findQueue(const char* name) {
    for (int i = 0; i < queueCount; ++i)
        if (std::strcmp(queues[i].getName(), name) == 0) return &queues[i];
    return nullptr;
}

AVLTree* Database::findTree(const char* name) {
    for (int i = 0; i < treeCount; ++i)
        if (std::strcmp(trees[i].getName(), name) == 0) return &trees[i];
    return nullptr;
}

ChainHashTable* Database::findChainTable(const char* name) {
    for (int i = 0; i < chainTableCount; ++i)
        if (std::strcmp(chainTables[i].getName(), name) == 0) return &chainTables[i];
    return nullptr;
}

OpenHashTable* Database::findOpenTable(const char* name) {
    for (int i = 0; i < openTableCount; ++i)
        if (std::strcmp(openTables[i].getName(), name) == 0) return &openTables[i];
    return nullptr;
}

void Database::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd, name, arg1;
    iss >> cmd >> name;

    if (cmd == "MPUSHTOEND") {
        iss >> arg1;
        DynamicArray* arr = findArray(name.c_str());
        if (!arr && arrayCount < MAX_STRUCTURES) {
            arr = &arrays[arrayCount++];
            arr->setName(name.c_str());
            std::cout << "Создан новый массив: " << name << "\n";
        }
        if (arr) arr->addToEnd(arg1);
    } else if (cmd == "FPUSH") {
        iss >> arg1;
        ForwardList* fl = findForwardList(name.c_str());
        if (!fl && forwardListCount < MAX_STRUCTURES) {
            fl = &forwardLists[forwardListCount++];
            fl->setName(name.c_str());
        }
        if (fl) fl->addToEnd(arg1);
    } else if (cmd == "LPUSH") {
        iss >> arg1;
        DoubleList* dl = findDoubleList(name.c_str());
        if (!dl && doubleListCount < MAX_STRUCTURES) {
            dl = &doubleLists[doubleListCount++];
            dl->setName(name.c_str());
        }
        if (dl) dl->addToEnd(arg1);
    } else if (cmd == "SPUSH") {
        iss >> arg1;
        Stack* st = findStack(name.c_str());
        if (!st && stackCount < MAX_STRUCTURES) {
            st = &stacks[stackCount++];
            st->setName(name.c_str());
        }
        if (st) st->push(arg1);
    } else if (cmd == "QPUSH") {
        iss >> arg1;
        Queue* q = findQueue(name.c_str());
        if (!q && queueCount < MAX_STRUCTURES) {
            q = &queues[queueCount++];
            q->setName(name.c_str());
        }
        if (q) q->enqueue(arg1);
    } else if (cmd == "TINSERT") {
        iss >> arg1;
        AVLTree* t = findTree(name.c_str());
        if (!t && treeCount < MAX_STRUCTURES) {
            t = &trees[treeCount++];
            t->setName(name.c_str());
        }
        if (t) t->insert(std::stoi(arg1));
    } else if (cmd == "TDEL") {
        iss >> arg1;
        AVLTree* t = findTree(name.c_str());
        if (t) t->remove(std::stoi(arg1));
    } else if (cmd == "HINSERT") {
        iss >> arg1;
        ChainHashTable* ht = findChainTable(name.c_str());
        if (!ht && chainTableCount < MAX_STRUCTURES) {
            ht = &chainTables[chainTableCount++];
            ht->setName(name.c_str());
        }
        if (ht) ht->insert(arg1.c_str());
    } else if (cmd == "PRINT") {
        if (auto* a = findArray(name.c_str())) a->print();
        else if (auto* f = findForwardList(name.c_str())) f->print();
        else if (auto* d = findDoubleList(name.c_str())) d->print();
        else if (auto* s = findStack(name.c_str())) s->print();
        else if (auto* q = findQueue(name.c_str())) q->print();
        else if (auto* t = findTree(name.c_str())) t->print();
        else if (auto* h = findChainTable(name.c_str())) h->print();
        else if (auto* o = findOpenTable(name.c_str())) o->print();
    } else {
        std::cout << "Неизвестная команда: " << cmd << "\n";
    }
}

void Database::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << arrayCount << "\n";
    for (int i = 0; i < arrayCount; ++i) arrays[i].save(file);

    file << forwardListCount << "\n";
    for (int i = 0; i < forwardListCount; ++i) forwardLists[i].save(file);

    file << doubleListCount << "\n";
    for (int i = 0; i < doubleListCount; ++i) doubleLists[i].save(file);

    file << stackCount << "\n";
    for (int i = 0; i < stackCount; ++i) stacks[i].save(file);

    file << queueCount << "\n";
    for (int i = 0; i < queueCount; ++i) queues[i].save(file);

    file << treeCount << "\n";
    for (int i = 0; i < treeCount; ++i) trees[i].save(file);

    file << chainTableCount << "\n";
    for (int i = 0; i < chainTableCount; ++i) chainTables[i].save(file);

    file << openTableCount << "\n";
    for (int i = 0; i < openTableCount; ++i) openTables[i].save(file);
}

void Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Файл не найден, будет создан новый: " << filename << "\n";
        return;
    }
    destroy();

    if (file >> arrayCount)
        for (int i = 0; i < arrayCount; ++i) arrays[i].load(file);
    if (file >> forwardListCount)
        for (int i = 0; i < forwardListCount; ++i) forwardLists[i].load(file);
    if (file >> doubleListCount)
        for (int i = 0; i < doubleListCount; ++i) doubleLists[i].load(file);
    if (file >> stackCount)
        for (int i = 0; i < stackCount; ++i) stacks[i].load(file);
    if (file >> queueCount)
        for (int i = 0; i < queueCount; ++i) queues[i].load(file);
    if (file >> treeCount)
        for (int i = 0; i < treeCount; ++i) trees[i].load(file);
    if (file >> chainTableCount)
        for (int i = 0; i < chainTableCount; ++i) chainTables[i].load(file);
    if (file >> openTableCount)
        for (int i = 0; i < openTableCount; ++i) openTables[i].load(file);
}
