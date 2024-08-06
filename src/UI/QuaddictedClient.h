#pragma once

#include <QObject>
#include <string>

class QuaddictedClient : public QObject {
    Q_OBJECT

public:
    explicit QuaddictedClient(QObject *parent = nullptr);
    ~QuaddictedClient();

public slots:
    void downloadMapDatabase();

private:
    std::string downloadXMLManifest(const std::string& url = default_url);
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    static const std::string default_url;
};
