#pragma once

#include <QMainWindow>

#include "NetworkManager.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

    // Delete copy operations to prevent copying
    MainWindow(const MainWindow &) = delete;                     // Explicitly delete the copy constructor
    auto operator=(const MainWindow &) -> MainWindow & = delete; // Delete copy assignment

    // Default move operations for efficiency
    MainWindow(MainWindow &&) noexcept = default;                     // Default move constructor
    auto operator=(MainWindow &&) noexcept -> MainWindow & = default; // Default move assignment

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
    void initialize();
};
