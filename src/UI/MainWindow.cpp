// src/UI/MainWindow.cpp
#include "MainWindow.h"
#include <QHBoxLayout>
#include <QSplitter>
#include <QVBoxLayout>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), client(new QuaddictedClient()) {
    setupUI();
    connect(this, &MainWindow::updateDatabaseRequested, this, &MainWindow::updateMapDatabase);
}

MainWindow::~MainWindow() {
    delete client;
}

void MainWindow::setupUI() {
    setWindowTitle("Hello World");
    resize(1280, 960);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QSplitter *splitter = new QSplitter;

    leftPane = new LeftPane(this);
    rightPane = new RightPane(this);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);

    splitter->setStretchFactor(0, 4);
    splitter->setStretchFactor(1, 1);

    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(splitter);

    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");

    QAction *updateAction = new QAction("Install Map Database...", this);
    fileMenu->addAction(updateAction);
    connect(updateAction, &QAction::triggered, this, &MainWindow::updateMapDatabase);

    QStatusBar *statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}

void MainWindow::updateMapDatabase() {
    std::cout << "Emitting updateDatabaseRequested signal" << std::endl;
    client->downloadMapDatabase();
}
