#pragma once

#include <QMainWindow>

#include "DownloadManager.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

  signals:
    void updateDatabaseRequested();

  private slots:
    void updateMapDatabase();
    void handleMapDatabaseTaskStarted();
    void handleMapDatabaseResults(const QString &result);
    void handleMapDownloadResults(const QString &result);
    void handleThumbnailDownloadResults(const QString &result);

  protected:
    void closeEvent(QCloseEvent *event) override;

  private:
    DownloadManager *downloadManager;
    StatusBar *statusBar;

    void setupUI();
    void initialize();
};
