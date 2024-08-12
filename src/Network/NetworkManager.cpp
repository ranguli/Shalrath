#include "NetworkManager.h"

// NOLINTBEGIN
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
// NOLINTEND

NetworkManager::NetworkManager(QObject *parent) : QObject(parent), networkManager(new QNetworkAccessManager(this)) {
    connect(networkManager, &QNetworkAccessManager::finished, this, &NetworkManager::onDownloadFinished);
}

void NetworkManager::downloadMapDatabase() {
    emit downloadStarted();
    const QNetworkRequest request{QUrl(mapDatabaseUrl)};
    networkManager->get(request);
}

void NetworkManager::downloadMap(const QString &url) {
    emit downloadStarted();
    const QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
}

void NetworkManager::downloadThumbnail(const QString &url) {
    emit downloadStarted();
    const QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
}

void NetworkManager::onDownloadFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        const QString result = QString::fromUtf8(reply->readAll());
        if (reply->url().toString() == mapDatabaseUrl) {
            emit downloadFinished("Map database updated");
        } else if (reply->url().toString().endsWith(".zip")) { // Assuming maps are zip files
            emit mapDownloadFinished("Map downloaded");
        } else if (reply->url().toString().endsWith(".jpg") ||
                   reply->url().toString().endsWith(".png")) { // Assuming thumbnails are jpg or png
            emit thumbnailDownloadFinished("Thumbnail downloaded");
        }
    } else {
        emit downloadFinished("Could not update map database");
    }
    reply->deleteLater();
}
