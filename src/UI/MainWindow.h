#pragma once

#include <QMainWindow>

#include "NetworkManager.h"

class StatusBar;

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   signals:
    void updateDatabaseRequested();

   public slots:
    void updateMapDatabase();
    void handleResults(const QString& result);
    void handleTaskStarted();

   protected:
    void closeEvent(QCloseEvent* event) override;

   private:
    NetworkManager* networkManager;
    StatusBar* statusBar;
    bool isClosing;

    void setupUI();
};
