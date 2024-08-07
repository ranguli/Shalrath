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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), networkManager(new NetworkManager(this)), isClosing(false) {
    connect(this, &MainWindow::updateDatabaseRequested, networkManager,
            &NetworkManager::downloadMapDatabase);
    connect(networkManager, &NetworkManager::downloadFinished, this, &MainWindow::handleResults);
    connect(networkManager, &NetworkManager::downloadStarted, this, &MainWindow::handleTaskStarted);

    setupUI();
}

MainWindow::~MainWindow() {

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

    // Comment out unused variables to avoid warnings
    // QMenu *editMenu = menuBar->addMenu("Edit");
    // QMenu *viewMenu = menuBar->addMenu("View");
    // QMenu *helpMenu = menuBar->addMenu("Help");

    statusBar = new StatusBar(this);
    setStatusBar(statusBar);

    connect(networkManager, &NetworkManager::downloadFinished, statusBar,
            &StatusBar::displayMessage);
}

void MainWindow::updateMapDatabase() {
    emit updateDatabaseRequested("https://www.quaddicted.com/reviews/quaddicted_database.xml");
}

void MainWindow::handleTaskStarted() {
    QPixmap icon(":/icons/download.png");  // Replace with the actual path to your icon
    statusBar->displayMessageWithIcon("Updating map database", icon);
}

void MainWindow::handleResults(const QString &result) {
    Q_UNUSED(result);  // Suppress unused parameter warning
    statusBar->displayMessage("Map updated");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!isClosing) {
        isClosing = true;
        qDebug() << "Closing application...";
        event->ignore();
        // Call QCoreApplication::quit() using QMetaObject to avoid direct call
        QMetaObject::invokeMethod(QCoreApplication::instance(), "quit", Qt::QueuedConnection);
    }
}
