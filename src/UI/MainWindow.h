#pragma once

#include <QMainWindow>
#include "INetworkClient.h"
#include "AsyncNetworkTaskUI.h"

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

private:
    INetworkClient* client;
    AsyncNetworkTaskUI* worker;
    QThread* workerThread;
    void setupUI();
};
