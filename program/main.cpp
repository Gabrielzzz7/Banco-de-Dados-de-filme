#include "Interface.hpp"
#include <iostream>

int main() {

    sqlite3* db;
    if (sqlite3_open("filmes.db", &db) != SQLITE_OK) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    Interface menu(db);
    menu.ExibirMenu();

    sqlite3_close(db);
    return 0;
}