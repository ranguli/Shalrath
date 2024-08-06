#include "NetworkUtils.h"

#include <curl/curl.h>

bool NetworkUtils::checkInternetConnection() {
    CURL *curl;
    CURLcode res;
    bool isConnected = false;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://cloudflare.com");
        curl_easy_setopt(curl, CURLOPT_NOBODY,
                         1L);                          // We don't need the body of the response
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // 10 second timeout

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            isConnected = true;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return isConnected;
}
