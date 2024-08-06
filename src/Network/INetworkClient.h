#pragma once

#include <string>

class INetworkClient {
public:
    virtual ~INetworkClient() = default;
    virtual std::string downloadMapDatabase(const std::string &url) = 0;
};
