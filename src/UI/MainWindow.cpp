#include "MainWindow.h"

#include <QMenuBar>
#include <QPixmap>
#include <QSplitter>
#include <QStatusBar>
#include <QThread>
#include <QVBoxLayout>

#include "LeftPane.h"
#include "QuaddictedClient.h"
#include "RightPane.h"
#include "StatusBar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), client(new QuaddictedClient()), worker(new AsyncNetworkTaskUI(client)) {
    workerThread = new QThread;
    worker->moveToThread(workerThread);

    connect(this, &MainWindow::updateDatabaseRequested, worker, &AsyncNetworkTaskUI::doWork);
    connect(worker, &AsyncNetworkTaskUI::resultReady, this, &MainWindow::handleResults);
    connect(worker, &AsyncNetworkTaskUI::taskStarted, this, &MainWindow::handleTaskStarted);
    connect(worker, &AsyncNetworkTaskUI::finished, worker, &QObject::deleteLater);
    connect(worker, &QObject::destroyed, workerThread, &QThread::quit);
    connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    workerThread->start();

    setupUI();
}

MainWindow::~MainWindow() {
    workerThread->quit();
    workerThread->wait();
}

void MainWindow::setupUI() {
    setWindowTitle("Hello World");
    resize(1280, 960);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QSplitter *splitter = new QSplitter;

    auto leftPane = new LeftPane(this);
    auto rightPane = new RightPane(this);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);

    splitter->setStretchFactor(0, 4);
    splitter->setStretchFactor(1, 1);

    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(splitter);

    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *updateAction = fileMenu->addAction("Update Map Database...");
    connect(updateAction, &QAction::triggered, this, &MainWindow::updateMapDatabase);

    QMenu *editMenu = menuBar->addMenu("Edit");
    QMenu *viewMenu = menuBar->addMenu("View");
    QMenu *helpMenu = menuBar->addMenu("Help");

    statusBar = new StatusBar(this);
    setStatusBar(statusBar);

    connect(worker, &AsyncNetworkTaskUI::resultReady, statusBar, &StatusBar::displayMessage);
}

void MainWindow::updateMapDatabase() {
    emit updateDatabaseRequested("https://www.quaddicted.com/reviews/quaddicted_database.xml");
}

void MainWindow::handleTaskStarted() {
    QPixmap icon(":/icons/download.png");  // Replace with the actual path to your icon
    statusBar->displayMessageWithIcon("Updating map database", icon);
}

void MainWindow::handleResults(const QString &result) { statusBar->displayMessage("Map updated"); }
