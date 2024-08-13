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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), downloadManager(new DownloadManager(this)), statusBar(new StatusBar(this)) {

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

    statusBar = new StatusBar(this); // Ensure statusBar is initialized
    setStatusBar(statusBar);         // Assign the statusBar to the QMainWindow's status bar
    // NOLINTEND(cppcoreguidelines-owning-memory)
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing application...";

    // Properly handle the event to prevent infinite loop
    event->accept();
    QCoreApplication::quit();
}
