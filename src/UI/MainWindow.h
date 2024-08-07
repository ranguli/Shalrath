#pragma once

#include <QMainWindow>

#include "AsyncNetworkTaskUI.h"
#include "INetworkClient.h"
#include "StatusBar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   signals:
    void updateDatabaseRequested(const QString& url);

   public slots:
    void updateMapDatabase();
    void handleResults(const QString& result);
    void handleTaskStarted();

   private:
    INetworkClient* client;
    AsyncNetworkTaskUI* worker;
    QThread* workerThread;
    StatusBar* statusBar;
    void setupUI();
};
