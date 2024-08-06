// src/Network/INetworkClient.h
#pragma once

#include <string>

class INetworkClient {
public:
    virtual ~INetworkClient() = default;
    virtual void downloadMapDatabase(const std::string& url = "") = 0;
};
