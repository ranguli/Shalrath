#pragma once

#include <QMainWindow>
#include <QObject>
#include "LeftPane.h"
#include "RightPane.h"
#include "../Network/INetworkClient.h"
#include "AsyncNetworkTaskUI.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateDatabaseRequested(const QString &url);

private slots:
    void updateMapDatabase();
    void handleResults(const QString &result);

private:
    void setupUI();
    LeftPane *leftPane;
    RightPane *rightPane;
    INetworkClient *client;
    AsyncNetworkTaskUI *worker;
};
