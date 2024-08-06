#include "QuaddictedClient.h"
#include "QuaddictedXMLParser.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <ostream>

// Define the default URL
const std::string QuaddictedClient::default_url = "https://www.quaddicted.com/reviews/quaddicted_database.xml";

QuaddictedClient::QuaddictedClient(QObject *parent) : QObject(parent) {}

QuaddictedClient::~QuaddictedClient() {}

void QuaddictedClient::downloadMapDatabase() {
    std::string manifest = downloadXMLManifest();
    std::cout << manifest;
    //QuaddictedXMLParser::parseXMLManifest(manifest);
}

std::string QuaddictedClient::downloadXMLManifest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::stringstream stream;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QuaddictedClient::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L); // 30 second timeout

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return "";
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return stream.str();
}

size_t QuaddictedClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ostream* stream = static_cast<std::ostream*>(userp);
    size_t totalSize = size * nmemb;
    stream->write(static_cast<char*>(contents), static_cast<std::streamsize>(totalSize));
    return totalSize;
}
