#pragma once

#include <QMainWindow>
#include "LeftPane.h"
#include "RightPane.h"
#include "QuaddictedClient.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateDatabaseRequested();

private slots:
    void updateMapDatabase();

private:
    void setupUI();
    LeftPane *leftPane;
    RightPane *rightPane;
    QuaddictedClient *client;
};
