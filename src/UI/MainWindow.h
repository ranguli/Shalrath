#pragma once

#include <QMainWindow>

#include "DownloadManager.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

  protected:
    void closeEvent(QCloseEvent *event) override;

  private:
    DownloadManager *downloadManager;
    StatusBar *statusBar;

    void setupUI();
    void initialize();
};
