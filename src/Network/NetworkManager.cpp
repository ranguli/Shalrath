#include "NetworkManager.h"

#include <QNetworkReply>
#include <QNetworkRequest>

const QString NetworkManager::mapDatabaseUrl =
    "https://www.quaddicted.com/reviews/quaddicted_database.xml";

NetworkManager::NetworkManager(QObject* parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)) {
    connect(networkManager, &QNetworkAccessManager::finished, this,
            &NetworkManager::onDownloadFinished);
}

void NetworkManager::downloadMapDatabase() {
    emit downloadStarted();
    QUrl url(mapDatabaseUrl);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void NetworkManager::onDownloadFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit downloadFinished("Map database updated");
    } else {
        emit downloadFinished("Could not update map database");
    }
    reply->deleteLater();
}
