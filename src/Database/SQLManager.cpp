#include "SQLManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

SQLManager::SQLManager(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
    }
}

SQLManager::~SQLManager() {
    if (db) {
        sqlite3_close(db);
    }
}

bool SQLManager::initialize(const std::string& schemaPath) {
    std::ifstream schemaFile(schemaPath);
    if (!schemaFile) {
        std::cerr << "Failed to open schema file: " << schemaPath << std::endl;
        return false;
    }

    std::stringstream schemaBuffer;
    schemaBuffer << schemaFile.rdbuf();
    std::string schemaSQL = schemaBuffer.str();

    char* errMsg = nullptr;
    if (sqlite3_exec(db, schemaSQL.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Failed to execute schema: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

std::vector<std::vector<std::string>> SQLManager::querySQL(const std::string& sql) {
    sqlite3_stmt* statement;
    std::vector<std::vector<std::string>> results;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    int cols = sqlite3_column_count(statement);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < cols; i++) {
            const char* text = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
            row.push_back(text ? text : "");
        }
        results.push_back(row);
    }

    sqlite3_finalize(statement);
    return results;
}
