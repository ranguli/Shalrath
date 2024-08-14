#pragma once

#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class DownloadManager : public QObject {
    Q_OBJECT

  public:
    explicit DownloadManager(QObject *parent = nullptr);

    QNetworkRequest downloadMapDatabase();
    void downloadMap(const QString &url);
    void downloadThumbnail(const QString &url);

  signals:
    void xmlDownloaded(const QString &xmlData);
    void mapDownloaded();
    void thumbnailDownloaded(const QImage &image);

  private slots:
    void onDownloadFinished(QNetworkReply *reply);

  private:
    QNetworkAccessManager *networkManager; // Declare network manager as a private member
};