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
    void downloadFinished(const QString &result);           // For map database content
    void mapDownloadFinished(const QByteArray &data);       // For maps
    void thumbnailDownloadFinished(const QByteArray &data); // For thumbnails
    void downloadStatusMessage(const QString &message);     // New signal for status messages
    void downloadError(const QString &errorMessage);        // General error signal

  private slots:
    void onDownloadFinished(QNetworkReply *reply);

  private:
    QNetworkAccessManager *downloadManager;
    QString mapDatabaseUrl = "https://www.quaddicted.com/reviews/quaddicted_database.xml";
};
