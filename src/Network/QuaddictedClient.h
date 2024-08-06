#pragma once

#include "INetworkClient.h"
#include <string>

class QuaddictedClient : public INetworkClient {
public:
    QuaddictedClient() = default;
    ~QuaddictedClient() override = default;

    std::string downloadMapDatabase(const std::string &url = default_url) override;

private:
    static const std::string default_url;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};
