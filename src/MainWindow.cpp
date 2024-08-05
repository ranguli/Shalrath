#include "MainWindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QIcon>
#include <QHeaderView>

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

    // Create the first pane (left column)
    QWidget *leftPane = new QWidget;
    QVBoxLayout *firstColumnLayout = new QVBoxLayout(leftPane);

    // Add a horizontal layout for the "Search" label and the line edit
    QHBoxLayout *searchLayout = new QHBoxLayout;
    QLabel *searchLabel = new QLabel("Search");
    searchLineEdit = new QLineEdit;
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);

    // Add the search layout to the first column layout
    firstColumnLayout->addLayout(searchLayout);

    // Add a table below the search layout
    table = new QTableWidget(50, 8); // 50 rows and 8 columns for example
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the table headers
    QStringList headers = {"", "", "Filename", "Title", "Description", "Author", "Date Released", "User Ratings"};
    table->setHorizontalHeaderLabels(headers);

    // Set icons for "Installed" and "Favorited" columns
    QIcon downloadIcon = QIcon::fromTheme("document-save");
    QIcon favoriteIcon = QIcon::fromTheme("emblem-favorite");
    QIcon starIcon = QIcon::fromTheme("starred");

    // Hide the vertical header (row numbers)
    table->verticalHeader()->setVisible(false);

    // Make columns stretch to fill available space, except for the first two and the last one
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set a minimum section size to prevent header text from being cut off
    table->horizontalHeader()->setMinimumSectionSize(100);

    // Set the minimum section size for the first two columns to fit the icons
    int iconSize = 24;  // Assuming the icons are 24x24 pixels
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    // Fix the size of the first two columns to the icon size
    table->setColumnWidth(0, iconSize); // Width for the "Installed" column
    table->setColumnWidth(1, iconSize); // Width for the "Favorited" column

    // Set minimum width for the other columns
    for (int col = 2; col < table->columnCount() - 1; ++col) {
        table->horizontalHeader()->resizeSection(col, 150); // Adjust the value 150 as necessary
    }

    // Set fixed width for the "User Ratings" column to fit the content
    table->setColumnWidth(7, 200); // Adjust this value if necessary

    // Populate the table with icons in "Installed" and "Favorited" columns
    for (int row = 0; row < table->rowCount(); ++row) {
        // Add download icon to "Installed" column
        QTableWidgetItem *installedItem = new QTableWidgetItem;
        installedItem->setIcon(downloadIcon);
        table->setItem(row, 0, installedItem);

        // Add heart icon to "Favorited" column
        QTableWidgetItem *favoritedItem = new QTableWidgetItem;
        favoritedItem->setIcon(favoriteIcon);
        table->setItem(row, 1, favoritedItem);

        // Add other items as examples
        table->setItem(row, 2, new QTableWidgetItem("Filename"));
        table->setItem(row, 3, new QTableWidgetItem("Title"));
        table->setItem(row, 4, new QTableWidgetItem("Description"));
        table->setItem(row, 5, new QTableWidgetItem("Author"));
        table->setItem(row, 6, new QTableWidgetItem("Date Released"));

        // Add star icons and review text to "User Ratings" column
        QWidget *ratingWidget = new QWidget();
        QHBoxLayout *ratingLayout = new QHBoxLayout(ratingWidget);
        ratingLayout->setContentsMargins(0, 0, 0, 0);
        ratingLayout->setSpacing(2);
        for (int i = 0; i < 5; ++i) {
            QLabel *starLabel = new QLabel();
            starLabel->setPixmap(starIcon.pixmap(16, 16));
            ratingLayout->addWidget(starLabel);
        }
        QLabel *reviewLabel = new QLabel("(42 reviews)");
        ratingLayout->addWidget(reviewLabel);
        ratingWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        table->setCellWidget(row, 7, ratingWidget);
    }

    firstColumnLayout->addWidget(table);

    // Create the second pane (right column)
    QFrame *rightPane = new QFrame;
    rightPane->setFrameShape(QFrame::Box); // Example frame shape
    rightPane->setFrameShadow(QFrame::Raised);

    QVBoxLayout *frameLayout = new QVBoxLayout(rightPane);

    // Add an image placeholder at the top
    imageLabel = new QLabel;

    // Load and scale the image
    QPixmap pixmap(":/image.png");
    int maxWidth = 300;  // Example max width
    int maxHeight = 200; // Example max height
    QPixmap scaledPixmap = pixmap.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(imageLabel);

    // Add a text widget below the image
    textBrowser = new QTextBrowser;
    textBrowser->setText("This is a placeholder for a paragraph of text. It is not editable by the user.");
    frameLayout->addWidget(textBrowser);

    // Add a horizontal layout for the "Install" and "Uninstall" buttons
    QHBoxLayout *installationButtons = new QHBoxLayout;
    installButton = new QPushButton("Install");
    uninstallButton = new QPushButton("Uninstall");

    installationButtons->addWidget(installButton);
    installationButtons->addWidget(uninstallButton);
    frameLayout->addLayout(installationButtons);

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
