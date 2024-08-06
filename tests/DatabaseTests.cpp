#include <gtest/gtest.h>
#include "SQLManager.h"
#include <iostream>
#include <algorithm>

class SQLManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        sqlManager = new SQLManager(":memory:");
        ASSERT_TRUE(sqlManager->initialize("../src/Database/schema.sql"));
    }

    void TearDown() override {
        delete sqlManager;
    }

    SQLManager* sqlManager;
};

TEST_F(SQLManagerTest, TablesExist) {
    auto results = sqlManager->querySQL("SELECT name FROM sqlite_master WHERE type='table';");
    std::vector<std::string> expectedTables = {
        "maps", "tags", "map_tags", "user_downloads", "user_favorites", "user_map_stats", "user_quake_configs"
    };

    std::vector<std::string> actualTables;
    for (const auto& row : results) {
        if (!row.empty() && row[0] != "sqlite_sequence") {
            actualTables.push_back(row[0]);
        }
    }

    std::cout << "Actual tables found:" << std::endl;
    for (const auto& table : actualTables) {
        std::cout << table << std::endl;
    }

    ASSERT_EQ(expectedTables.size(), actualTables.size());
    for (const auto& table : expectedTables) {
        EXPECT_NE(std::find(actualTables.begin(), actualTables.end(), table), actualTables.end());
    }
}

TEST_F(SQLManagerTest, ColumnsExist) {
    auto checkColumns = [&](const std::string& table, const std::vector<std::string>& expectedColumns) {
        auto results = sqlManager->querySQL("PRAGMA table_info(" + table + ");");

        std::vector<std::string> actualColumns;
        for (const auto& row : results) {
            if (row.size() > 1) {
                actualColumns.push_back(row[1]); // Column name is in the second position
            }
        }

        std::cout << "Columns in table " << table << ":" << std::endl;
        for (const auto& column : actualColumns) {
            std::cout << column << std::endl;
        }

        ASSERT_EQ(expectedColumns.size(), actualColumns.size());
        for (const auto& column : expectedColumns) {
            EXPECT_NE(std::find(actualColumns.begin(), actualColumns.end(), column), actualColumns.end());
        }
    };

    checkColumns("maps", {"map_id", "type", "rating", "normalized_users_rating", "author", "title", "md5sum", "size", "date", "description", "zipbasedir", "commandline", "startmap", "thumbnail"});
    checkColumns("tags", {"tag"});
    checkColumns("map_tags", {"map_id", "tag"});
    checkColumns("user_downloads", {"user_id", "map_id", "downloaded"});
    checkColumns("user_favorites", {"user_id", "map_id", "favorited"});
    checkColumns("user_map_stats", {"user_id", "map_id", "played", "play_count", "total_play_time", "last_played"});
    checkColumns("user_quake_configs", {"user_id", "config_id", "quake_directory", "quake_executable", "extra_commandline_options"});
}
