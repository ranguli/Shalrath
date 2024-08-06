#include "MainWindow.h"
#include <QThread>
#include <QMenuBar>
#include <QStatusBar>
#include <QSplitter>
#include <QVBoxLayout>
#include <QDebug>
#include "../Network/QuaddictedClient.h"

#include "LeftPane.h"
#include "RightPane.h"

void MainWindow::setupUI() {
    setWindowTitle("Hello World");
    resize(1280, 960);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QSplitter* splitter = new QSplitter;

    auto leftPane = new LeftPane(this);
    auto rightPane = new RightPane(this);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);

    splitter->setStretchFactor(0, 4);
    splitter->setStretchFactor(1, 1);

    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(splitter);

    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* updateAction = fileMenu->addAction("Update Map Database...");
    connect(updateAction, &QAction::triggered, this, &MainWindow::updateMapDatabase);

    QMenu* editMenu = menuBar->addMenu("Edit");
    QMenu* viewMenu = menuBar->addMenu("View");
    QMenu* helpMenu = menuBar->addMenu("Help");

    QStatusBar* statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), client(new QuaddictedClient()), worker(new AsyncNetworkTaskUI(client)), workerThread(new QThread(this)) {
    
    worker->moveToThread(workerThread);

    connect(this, &MainWindow::updateDatabaseRequested, worker, &AsyncNetworkTaskUI::doWork);
    connect(worker, &AsyncNetworkTaskUI::resultReady, this, &MainWindow::handleResults);
    connect(worker, &AsyncNetworkTaskUI::finished, workerThread, &QThread::quit);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    workerThread->start();

    setupUI();
}

MainWindow::~MainWindow() {
    workerThread->quit();
    workerThread->wait();
}



void MainWindow::updateMapDatabase() {
    emit updateDatabaseRequested("https://www.quaddicted.com/reviews/quaddicted_database.xml");
}

void MainWindow::handleResults(const QString& result) {
    qDebug() << "Result received: " << result;
}
