#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class NetworkManager : public QObject {
    Q_OBJECT

   public:
    explicit NetworkManager(QObject* parent = nullptr);

   public slots:
    void downloadMapDatabase();

   signals:
    void downloadStarted();
    void downloadFinished(const QString& result);

   private slots:
    void onDownloadFinished(QNetworkReply* reply);

   private:
    QNetworkAccessManager* networkManager;
    static const QString mapDatabaseUrl;
};
