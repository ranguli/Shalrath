#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
  public:
    static DatabaseManager &instance();

    QSqlDatabase &database();

  private:
    DatabaseManager();
    ~DatabaseManager();

    QString getDatabasePath() const; // New method to determine the database path

    QSqlDatabase m_db;

    void initializeDatabase();
};

#endif // DATABASEMANAGER_H
