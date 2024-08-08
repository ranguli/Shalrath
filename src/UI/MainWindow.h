#pragma once

#include <QMainWindow>

#include "NetworkManager.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    NetworkManager *networkManager;
    StatusBar *statusBar;

    void setupUI();
};
