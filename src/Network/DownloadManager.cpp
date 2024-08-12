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
        QByteArray data = reply->readAll();
        QString url = reply->url().toString();

        if (url == mapDatabaseUrl) {
            QString result = QString::fromUtf8(data);
            emit downloadFinished(result);                      // Emit the XML data as a string
            emit downloadStatusMessage("Map database updated"); // Emit a simple status message
        } else if (url.endsWith(".zip")) {                      // Assuming maps are zip files
            emit mapDownloadFinished(data);                     // Emit raw data for map files
            emit downloadStatusMessage("Map downloaded");
        } else if (url.endsWith(".jpg") || url.endsWith(".png")) { // Assuming thumbnails are jpg or png
            emit thumbnailDownloadFinished(data);                  // Emit raw data for thumbnails
            emit downloadStatusMessage("Thumbnail downloaded");
        }
    } else {
        emit downloadError("Download failed: " + reply->errorString());
    }
    reply->deleteLater();
}
