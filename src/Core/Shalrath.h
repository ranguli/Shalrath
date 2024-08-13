#pragma once

#include <QApplication>
#include <QString>
#include <memory>

class DownloadManager;

class Shalrath : public QApplication {
    Q_OBJECT

  public:
    Shalrath(int &argc, char **argv);
    ~Shalrath() override;

  signals:
    void updateProgress(int percentage);

  private slots:
    void initializeMapDatabase();
    void onMapDatabaseDownloaded(const QString &xmlData);
    void onMapDownloaded();
    void onThumbnailDownloaded(const QImage &image);

  private:
    void handleCommandLineOptions();
    void initialize() const;

    std::unique_ptr<DownloadManager> downloadManager;
    QString mapDatabaseXml;
};