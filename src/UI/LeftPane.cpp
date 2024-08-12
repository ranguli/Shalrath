#include "LeftPane.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>

LeftPane::LeftPane(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void LeftPane::setupUI() {
    // Make an exemption for not using smart pointers because of how Qt manages its own memory
    // NOLINTBEGIN(cppcoreguidelines-owning-memory)
    auto *layout = new QVBoxLayout(this);

    // Add a horizontal layout for the "Search" label and the line edit
    auto *searchLayout = new QHBoxLayout(this);
    auto *searchLabel = new QLabel("Search", this);
    searchLineEdit = new QLineEdit(this);
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);

    // NOLINTEND(cppcoreguidelines-owning-memory)

    // Add the search layout to the main layout
    layout->addLayout(searchLayout);

    // Add a table below the search layout
    table = new QTableWidget(50, 8); // NOLINT(cppcoreguidelines-owning-memory)
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the table headers
    const QStringList headers = {"", "", "Filename", "Title", "Description", "Author", "Date Released", "User Ratings"};
    table->setHorizontalHeaderLabels(headers);

    // Set icons for "Installed" and "Favorited" columns
    const QIcon downloadIcon = QIcon::fromTheme("document-save");
    const QIcon favoriteIcon = QIcon::fromTheme("emblem-favorite");
    const QIcon starIcon = QIcon::fromTheme("starred");

    // Hide the vertical header (row numbers)
    table->verticalHeader()->setVisible(false);

    // Make columns stretch to fill available space, except for the first two and
    // the last one
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set a minimum section size to prevent header text from being cut off
    table->horizontalHeader()->setMinimumSectionSize(20);

    // Set the resize mode for the first two columns to resize to contents
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    // Fix the size of the first two columns to the icon size
    int iconSize = 24;                  // Assuming the icons are 24x24 pixels
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
        auto *installedItem = new QTableWidgetItem; // NOLINT(cppcoreguidelines-owning-memory)
        installedItem->setIcon(downloadIcon);
        table->setItem(row, 0, installedItem);

        // Add heart icon to "Favorited" column
        auto *favoritedItem = new QTableWidgetItem; //NOLINT(cppcoreguidelines-owning-memory)
        favoritedItem->setIcon(favoriteIcon);
        table->setItem(row, 1, favoritedItem);

        // Exemption for smart pointers because of how Qt handles memory
        // NOLINTBEGIN(cppcoreguidelines-owning-memory)
        table->setItem(row, 2, new QTableWidgetItem("Filename"));
        table->setItem(row, 3, new QTableWidgetItem("Title"));
        table->setItem(row, 4, new QTableWidgetItem("Description"));
        table->setItem(row, 5, new QTableWidgetItem("Author"));
        table->setItem(row, 6, new QTableWidgetItem("Date Released"));

        // Add star icons and review text to "User Ratings" column
        auto *ratingWidget = new QWidget(this);
        auto *ratingLayout = new QHBoxLayout(ratingWidget);
        
        // NOLINTEND(cppcoreguidelines-owning-memory)

        // NOLINTEND(cppcoreguidelines-owning-memory)

        ratingLayout->setContentsMargins(0, 0, 0, 0);
        ratingLayout->setSpacing(2);
        for (int i = 0; i < 5; ++i) {
            auto *starLabel = new QLabel(this); // NOLINT(cppcoreguidelines-owning-memory)
            starLabel->setPixmap(starIcon.pixmap(16, 16));
            ratingLayout->addWidget(starLabel);
        }
        auto *reviewLabel = new QLabel("(42 reviews)", this); // NOLINT(cppcoreguidelines-owning-memory)
        ratingLayout->addWidget(reviewLabel);
        ratingWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        table->setCellWidget(row, 7, ratingWidget);
    }

    layout->addWidget(table);
}
