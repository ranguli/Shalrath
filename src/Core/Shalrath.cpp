#include "Shalrath.h"
#include "CommandLineOptions.h"
#include "DatabaseManager.h"
#include "DownloadManager.h"
#include "MainWindow.h"
#include "MapDao.h"
#include "QuaddictedXMLParser.h"
#include "WelcomeDialog.h"
#include <QDebug>
#include <QSettings>
#include <QThread>

Shalrath::Shalrath(int &argc, char **argv) : QApplication(argc, argv), downloadManager(std::make_unique<DownloadManager>()) {
    handleCommandLineOptions();

    DatabaseManager::instance();
    initialize();
}

Shalrath::~Shalrath() = default;

void Shalrath::handleCommandLineOptions() {
    const CommandLineOptions options(arguments());

    if (options.isFirstRun()) {
        QSettings settings("YourCompany", "YourAppName");
        settings.remove("hasSeenWelcomeDialog");
    }
}

void Shalrath::initialize() const {
    QSettings settings("YourCompany", "YourAppName");

    WelcomeDialog welcomeDialog;

    connect(&welcomeDialog, &WelcomeDialog::startInitialization, this, &Shalrath::initializeMapDatabase);
    connect(this, &Shalrath::updateProgress, &welcomeDialog, &WelcomeDialog::setProgressBarPercentage);

    if (welcomeDialog.exec() == QDialog::Accepted) {
        settings.setValue("hasSeenWelcomeDialog", true);
    } else {
        QCoreApplication::quit();
    }

    MainWindow mainWindow;
    mainWindow.show();

    exec();
}

void Shalrath::initializeMapDatabase() {
    connect(downloadManager.get(), &DownloadManager::xmlDownloaded, this, &Shalrath::onMapDatabaseDownloaded);

    downloadManager->downloadMapDatabase();

    for (int i = 0; i <= 100; i += 20) {
        QThread::msleep(100);
        emit updateProgress(i);
        QCoreApplication::processEvents();
    }
}

void Shalrath::onMapDatabaseDownloaded(const QString &xmlData) {
    // qDebug() << "XML Data received:" << xmlData;

    // Parse the XML data into a list of Map objects
    QList<Map> maps = QuaddictedXMLParser::parse(xmlData);

    // Convert QList<Map> to std::vector<Map> for bulkInsertMaps
    std::vector<Map> mapVector;
    for (const Map &map : maps) {
        qDebug() << QString::fromStdString(map.getMapID());
        mapVector.push_back(map);
    }

    // Get the database instance and insert maps
    QSqlDatabase db = DatabaseManager::instance().database();
    MapDao mapDao(db);
    mapDao.bulkInsertMaps(mapVector);

    // Update the progress bar to 100%
    emit updateProgress(100);

    // Close the welcome dialog
    QMetaObject::invokeMethod(qApp->activeModalWidget(), "accept", Qt::QueuedConnection);

    // Disconnect the signal once done
    disconnect(downloadManager.get(), &DownloadManager::xmlDownloaded, this, &Shalrath::onMapDatabaseDownloaded);
}

void Shalrath::onMapDownloaded() {
    qDebug() << "Map downloaded and saved as downloaded_map.zip.";
    // Further processing of the map can be done here
}

void Shalrath::onThumbnailDownloaded(const QImage &image) {
    qDebug() << "Thumbnail downloaded with size:" << image.size();
    // Further processing of the image can be done here
}
