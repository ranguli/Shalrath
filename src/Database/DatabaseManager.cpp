#include "DatabaseManager.h"
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QStandardPaths>

DatabaseManager::DatabaseManager() {
    QString dbPath = getDatabasePath();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qCritical() << "Error: Could not open database at" << dbPath << "-" << m_db.lastError().text();
    } else {
        qDebug() << "Database connection established at" << dbPath;
    }
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
        qDebug() << "Database connection closed.";
    }
}

QString DatabaseManager::getDatabasePath() const {
    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    // Ensure the directory exists
    QDir dir(configLocation);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString dbPath = dir.filePath("shalrath.sqlite"); // Name your database file accordingly
    return dbPath;
}

DatabaseManager &DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

QSqlDatabase &DatabaseManager::database() {
    return m_db;
}
