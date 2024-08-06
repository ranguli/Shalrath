#include "QuaddictedClient.h"
#include <curl/curl.h>
#include <sstream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::stringstream* ss = static_cast<std::stringstream*>(userp);
    size_t totalSize = size * nmemb;
    ss->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string QuaddictedClient::downloadXMLDatabase(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::stringstream ss;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ss);
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

    return ss.str();
}
