#include "MainWindow.h"

#include <QCloseEvent>
#include <QCoreApplication>
#include <QMenuBar>
#include <QPixmap>
#include <QSplitter>
#include <QStatusBar>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>

#include "LeftPane.h"
#include "RightPane.h"
#include "StatusBar.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 960;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), networkManager(new NetworkManager(this)) {
    connect(this, &MainWindow::updateDatabaseRequested, networkManager, &NetworkManager::downloadMapDatabase);
    connect(networkManager, &NetworkManager::downloadStarted, this, &MainWindow::handleMapDatabaseTaskStarted);
    connect(networkManager, &NetworkManager::downloadFinished, this, &MainWindow::handleMapDatabaseResults);
    connect(networkManager, &NetworkManager::mapDownloadFinished, this, &MainWindow::handleMapDownloadResults);
    connect(networkManager, &NetworkManager::thumbnailDownloadFinished, this, &MainWindow::handleThumbnailDownloadResults);

    setupUI();
}

void MainWindow::setupUI() {
    setWindowTitle("Hello World");
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Make an exemption for not using smart pointers because of how Qt manages its own memory
    // NOLINTBEGIN(cppcoreguidelines-owning-memory)
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *splitter = new QSplitter(this);

    auto leftPane = new LeftPane(this);
    auto rightPane = new RightPane(this);

    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);

    splitter->setStretchFactor(0, 4);
    splitter->setStretchFactor(1, 1);

    auto *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(splitter);

    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *updateAction = fileMenu->addAction("Update Map Database...");
    connect(updateAction, &QAction::triggered, this, &MainWindow::updateMapDatabase);

    // Comment out unused variables to avoid warnings
    // QMenu *editMenu = menuBar->addMenu("Edit");
    // QMenu *viewMenu = menuBar->addMenu("View");
    // QMenu *helpMenu = menuBar->addMenu("Help");

    statusBar = new StatusBar(this);
    // NOLINTEND(cppcoreguidelines-owning-memory)
    setStatusBar(statusBar);

    connect(networkManager, &NetworkManager::downloadFinished, statusBar, &StatusBar::displayMessage);
}

void MainWindow::initialize() {
    // This probably should be implemented elsewhere outside of the UI code, but called here.

    // 1. Download the map database in-memory
    // 2. Parse it with the QuaddictedXMLParser
    // 3. Update the database
}

void MainWindow::updateMapDatabase() {
    emit updateDatabaseRequested();
}

void MainWindow::handleMapDatabaseTaskStarted() {
    statusBar->displayMessage("Updating map database");
}

void MainWindow::handleMapDatabaseResults(const QString &result) {
    Q_UNUSED(result); // Suppress unused parameter warning
    statusBar->displayMessage("Map database updated");
}

void MainWindow::handleMapDownloadResults(const QString &result) {
    Q_UNUSED(result); // Suppress unused parameter warning
    statusBar->displayMessage("Map downloaded");
}

void MainWindow::handleThumbnailDownloadResults(const QString &result) {
    Q_UNUSED(result); // Suppress unused parameter warning
    statusBar->displayMessage("Thumbnail downloaded");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing application...";

    // Properly handle the event to prevent infinite loop
    event->accept();
    QCoreApplication::quit();
}
