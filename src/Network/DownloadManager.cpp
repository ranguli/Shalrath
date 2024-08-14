#include "DownloadManager.h"
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

const QString mapDatabaseUrl = "https://www.quaddicted.com/reviews/quaddicted_database.xml";

DownloadManager::DownloadManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)) // Initialize network manager
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &DownloadManager::onDownloadFinished);
}

QNetworkRequest DownloadManager::downloadMapDatabase() {
    QNetworkRequest request{QUrl(mapDatabaseUrl)};
    networkManager->get(request);
    return request;
}

void DownloadManager::downloadMap(const QString &url) {
    QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
}

void DownloadManager::downloadThumbnail(const QString &url) {
    QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
}

void DownloadManager::onDownloadFinished(QNetworkReply *reply) {
    QUrl url = reply->url();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        if (url == QUrl(mapDatabaseUrl)) {
            QString xmlString = QString::fromUtf8(data);
            emit xmlDownloaded(xmlString);
        } else if (url.path().endsWith(".zip")) {
            QFile file("downloaded_map.zip");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(data);
                file.close();
                emit mapDownloaded();
            }
        } else if (url.path().endsWith(".jpg") || url.path().endsWith(".png")) {
            QImage image;
            image.loadFromData(data);
            if (image.save("downloaded_thumbnail.jpg")) {
                emit thumbnailDownloaded(image);
            }
        }
    } else {
        qDebug() << "Download failed: " << reply->errorString();
    }

    reply->deleteLater();
}
