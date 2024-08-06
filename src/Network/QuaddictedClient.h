#pragma once
#include <string>

class QuaddictedClient {
public:
    static bool downloadXMLDatabase(const std::string& url, const std::string& outputFile);
};
