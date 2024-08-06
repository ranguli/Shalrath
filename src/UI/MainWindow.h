// src/UI/MainWindow.h
#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QWidget>
#include "LeftPane.h"
#include "RightPane.h"
#include "INetworkClient.h"
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
    INetworkClient *client;
};
