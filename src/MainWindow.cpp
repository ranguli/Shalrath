#include "MainWindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    setWindowTitle("Hello World");
    resize(1280, 960);

    // Create a central widget and set it on the main window
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a splitter to manage the layout
    QSplitter *splitter = new QSplitter;

    // Create the left and right panes
    leftPane = new LeftPane(this);
    rightPane = new RightPane(this);

    // Add the left and right panes to the splitter
    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);

    // Set the stretch factors for the panes
    splitter->setStretchFactor(0, 4);  // Left pane gets 80%
    splitter->setStretchFactor(1, 1);  // Right pane gets 20%

    // Add the splitter to the central widget's layout
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(splitter);

    // Create a menu bar
    QMenuBar *menuBar = this->menuBar();

    // Add menus to the menu bar
    QMenu *fileMenu = menuBar->addMenu("File");
    QMenu *editMenu = menuBar->addMenu("Edit");
    QMenu *viewMenu = menuBar->addMenu("View");
    QMenu *helpMenu = menuBar->addMenu("Help");

    // Create a status bar and add it to the main window
    QStatusBar *statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}
