#include "NetworkManager.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

NetworkManager::NetworkManager(QObject* parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)) {
    connect(networkManager, &QNetworkAccessManager::finished, this,
            &NetworkManager::onDownloadFinished);
}

NetworkManager::~NetworkManager() { delete networkManager; }

void NetworkManager::downloadMapDatabase(const QString& url) {
    emit downloadStarted();

    QUrl qurl(url);
    QNetworkRequest request(qurl);
    networkManager->get(request);
}

void NetworkManager::onDownloadFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit downloadFinished("Map updated");
    } else {
        QString error = reply->errorString();
        emit downloadError(error);
    }
    reply->deleteLater();
}
