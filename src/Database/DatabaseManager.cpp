#include "DatabaseManager.h"
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
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

    initializeDatabase();
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

void DatabaseManager::initializeDatabase() {
    QSqlQuery query(m_db);

    // Create the "maps" table if it doesn't exist
    query.prepare("CREATE TABLE IF NOT EXISTS maps ("
                  "map_id TEXT PRIMARY KEY,"
                  "type INTEGER,"
                  "normalized_users_rating REAL,"
                  "author TEXT,"
                  "title TEXT,"
                  "md5sum TEXT,"
                  "size INTEGER,"
                  "date TEXT,"
                  "description TEXT,"
                  "zipbasedir TEXT,"
                  "commandline TEXT,"
                  "startmap TEXT,"
                  "thumbnail BLOB,"
                  "favorited INTEGER,"
                  "downloaded INTEGER,"
                  "dependencies TEXT"
                  ")");

    if (!query.exec()) {
        qCritical() << "Error creating maps table:" << query.lastError().text();
    } else {
        qDebug() << "Maps table created or already exists.";
    }
}