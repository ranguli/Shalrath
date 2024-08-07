#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class NetworkManager : public QObject {
    Q_OBJECT

   public:
    explicit NetworkManager(QObject* parent = nullptr);
    ~NetworkManager();

   public slots:
    void downloadMapDatabase(const QString& url);

   signals:
    void downloadStarted();
    void downloadFinished(const QString& result);
    void downloadError(const QString& error);

   private slots:
    void onDownloadFinished(QNetworkReply* reply);

   private:
    QNetworkAccessManager* networkManager;
};
