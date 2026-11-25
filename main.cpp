#include <iostream>
#include <string>
#include "database.h"

int main(int argc, char* argv[]) {
    std::string filename;
    std::string query;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty()) {
        std::cerr << "Использование: ./lr3 --file <путь_к_файлу> --query '<команда>'\n";
        return 1;
    }

    Database db;
    db.loadFromFile(filename);
    db.processCommand(query);
    db.saveToFile(filename);

    return 0;
}
