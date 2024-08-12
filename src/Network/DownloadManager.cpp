#include "DownloadManager.h"

// NOLINTBEGIN
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
// NOLINTEND

DownloadManager::DownloadManager(QObject *parent) : QObject(parent), downloadManager(new QNetworkAccessManager(this)) {
    connect(downloadManager, &QNetworkAccessManager::finished, this, &DownloadManager::onDownloadFinished);
}

void DownloadManager::downloadMapDatabase() {
    emit downloadStarted();
    QNetworkRequest request{QUrl(mapDatabaseUrl)};
    downloadManager->get(request);
}

void DownloadManager::downloadMap(const QString &url) {
    emit downloadStarted();
    QNetworkRequest request{QUrl(url)};
    downloadManager->get(request);
}

void DownloadManager::downloadThumbnail(const QString &url) {
    emit downloadStarted();
    QNetworkRequest request{QUrl(url)};
    downloadManager->get(request);
}

void DownloadManager::onDownloadFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString result = QString::fromUtf8(reply->readAll());
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
