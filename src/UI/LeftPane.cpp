#include "LeftPane.h"

#include "DatabaseManager.h"
#include "MapDao.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QSqlDatabase>
#include <QVBoxLayout>

LeftPane::LeftPane(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void LeftPane::setupUI() {
    // Make an exemption for not using smart pointers because of how Qt manages its own memory

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *layout = new QVBoxLayout(this);

    auto *searchLayout = setupSearchLayout();

    // Add the search layout to the main layout
    layout->addLayout(searchLayout);

    table = setupTable();

    layout->addWidget(table);
}

auto LeftPane::setupSearchLayout() -> QHBoxLayout * {
    // Add a horizontal layout for the "Search" label and the line edit

    // NOLINTBEGIN(cppcoreguidelines-owning-memory)
    auto *searchLayout = new QHBoxLayout(this);
    auto *searchLabel = new QLabel("Search", this);
    searchLineEdit = new QLineEdit(this);
    // NOLINTEND(cppcoreguidelines-owning-memory)

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);

    return searchLayout;
}

void LeftPane::populateTableWithData() {
    // Get the database instance and create a MapDao
    QSqlDatabase db = DatabaseManager::instance().database();
    MapDao mapDao(db);

    // Fetch all maps from the database
    std::vector<Map> maps = mapDao.getAllMaps();

    table->setRowCount(static_cast<int>(maps.size())); // Set the row count to the number of maps

    // Populate the table with data from the maps
    for (size_t row = 0; row < maps.size(); ++row) {
        const Map &map = maps[row];

        // Set installed and favorited icons as placeholders (or fetch actual status if available)
        auto *installedItem = new QTableWidgetItem; // NOLINT(cppcoreguidelines-owning-memory)
        installedItem->setIcon(QIcon::fromTheme("document-save"));
        table->setItem(static_cast<int>(row), 0, installedItem);

        auto *favoritedItem = new QTableWidgetItem; // NOLINT(cppcoreguidelines-owning-memory)
        favoritedItem->setIcon(QIcon::fromTheme("emblem-favorite"));
        table->setItem(static_cast<int>(row), 1, favoritedItem);

        // Fill in the rest of the columns with actual data
        table->setItem(static_cast<int>(row), 2, new QTableWidgetItem(QString::fromStdString(map.getMapID())));
        table->setItem(static_cast<int>(row), 3, new QTableWidgetItem(QString::fromStdString(map.getTitle())));
        table->setItem(static_cast<int>(row), 4, new QTableWidgetItem(QString::fromStdString(map.getDescription())));
        table->setItem(static_cast<int>(row), 5, new QTableWidgetItem(QString::fromStdString(map.getAuthor())));
        table->setItem(static_cast<int>(row), 6, new QTableWidgetItem(QString::fromStdString(map.getDate())));

        // Add user ratings (adjust based on your actual rating system)
        auto *ratingWidget = new QWidget(this);
        auto *ratingLayout = new QHBoxLayout(ratingWidget);

        ratingLayout->setContentsMargins(0, 0, 0, 0);
        ratingLayout->setSpacing(2);
        int userRating = static_cast<int>(map.getNormalizedUsersRating() / 2); // Assuming rating is out of 10, convert to 5 stars
        QIcon starIcon = QIcon::fromTheme("starred");

        for (int i = 0; i < 5; ++i) {
            auto *starLabel = new QLabel(this); // NOLINT(cppcoreguidelines-owning-memory)
            starLabel->setPixmap(starIcon.pixmap(16, 16));
            if (i >= userRating) {
                starLabel->setPixmap(QIcon::fromTheme("non-starred").pixmap(16, 16));
            }
            ratingLayout->addWidget(starLabel);
        }

        QString reviewText =
            QString("(%1 reviews)").arg(map.getNormalizedUsersRating()); // Replace with actual review count if available
        auto *reviewLabel = new QLabel(reviewText, this);                // NOLINT(cppcoreguidelines-owning-memory)
        ratingLayout->addWidget(reviewLabel);
        ratingWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        table->setCellWidget(static_cast<int>(row), 7, ratingWidget);
    }
}

auto LeftPane::setupTable() -> QTableWidget * {
    // Add a table below the search layout
    table = new QTableWidget(50, 8); // NOLINT(cppcoreguidelines-owning-memory)
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

    // Make columns stretch to fill available space, except for the first two and
    // the last one
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set a minimum section size to prevent header text from being cut off
    table->horizontalHeader()->setMinimumSectionSize(20);

    // Set the resize mode for the first two columns to resize to contents
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    // Fix the size of the first two columns to the icon size
    const int iconSize = 24;            // Assuming the icons are 24x24 pixels
    table->setColumnWidth(0, iconSize); // Width for the "Installed" column
    table->setColumnWidth(1, iconSize); // Width for the "Favorited" column

    // Set minimum width for the other columns
    for (int col = 2; col < table->columnCount() - 1; ++col) {
        table->horizontalHeader()->resizeSection(col, 150); // Adjust the value 150 as necessary
    }

    // Set fixed width for the "User Ratings" column to fit the content
    table->setColumnWidth(7, 200); // Adjust this value if necessary

    populateTableWithData();

    return table;
}
