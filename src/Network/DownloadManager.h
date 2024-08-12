#pragma once

// NOLINTBEGIN
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QString>
// NOLINTEND

class DownloadManager : public QObject {
    Q_OBJECT

  public:
    explicit DownloadManager(QObject *parent = nullptr);
    void downloadMapDatabase();
    void downloadMap(const QString &url);
    void downloadThumbnail(const QString &url);

  signals:
    void downloadStarted();
    void downloadFinished(const QString &result);
    void mapDownloadFinished(const QString &result);
    void thumbnailDownloadFinished(const QString &result);

  private slots:
    void onDownloadFinished(QNetworkReply *reply);

  private:
    QNetworkAccessManager *downloadManager;
    QString mapDatabaseUrl = "https://www.quaddicted.com/reviews/quaddicted_database.xml";
};