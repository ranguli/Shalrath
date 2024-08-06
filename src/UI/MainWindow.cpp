#include "MainWindow.h"

#include <QHBoxLayout>
#include <QMenuBar>
#include <QSplitter>
#include <QStatusBar>
#include <QVBoxLayout>
#include "../Network/QuaddictedClient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), client(new QuaddictedClient()), worker(new AsyncNetworkTaskUI(client)) {
    setupUI();
    connect(this, &MainWindow::updateDatabaseRequested, worker, &AsyncNetworkTaskUI::doWork);
    connect(worker, &AsyncNetworkTaskUI::resultReady, this, &MainWindow::handleResults);
    connect(worker, &AsyncNetworkTaskUI::finished, worker, &QObject::deleteLater);
}

MainWindow::~MainWindow() {
    delete client;
    delete worker;
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
    QAction *updateAction = new QAction("Update Map Database...", this);
    fileMenu->addAction(updateAction);

    connect(updateAction, &QAction::triggered, this, &MainWindow::updateMapDatabase);

    QStatusBar *statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}

void MainWindow::updateMapDatabase() {
    emit updateDatabaseRequested("https://www.quaddicted.com/reviews/quaddicted_database.xml");
}

void MainWindow::handleResults(const QString &result) {
    // Use the result parameter to avoid the unused parameter warning
    qDebug() << "Result received: " << result;
}
