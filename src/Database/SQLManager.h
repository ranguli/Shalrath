#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

class SQLManager {
public:
    explicit SQLManager(const std::string &dbPath);
    ~SQLManager();

    bool initialize(const std::string &schemaPath);
    std::vector<std::vector<std::string>> querySQL(const std::string &sql);

private:
    sqlite3 *db = nullptr;
};

