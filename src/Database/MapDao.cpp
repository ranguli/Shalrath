#include "MapDao.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MapDao::MapDao(QSqlDatabase &database) : m_db(database) {
}

void MapDao::bulkInsertMaps(const std::vector<Map> &maps) {
    // Start a transaction
    m_db.transaction();

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO maps (map_id, type, normalized_users_rating, author, title, md5sum, size, date, "
                  "description, zipbasedir, commandline, startmap, thumbnail, favorited, downloaded) "
                  "VALUES (:map_id, :type, :normalized_users_rating, :author, :title, :md5sum, :size, :date, "
                  ":description, :zipbasedir, :commandline, :startmap, :thumbnail, :favorited, :downloaded)");

    for (const auto &map : maps) {
        query.bindValue(":map_id", QString::fromStdString(map.getMapID()));
        query.bindValue(":type", map.getType());
        query.bindValue(":normalized_users_rating", map.getNormalizedUsersRating());
        query.bindValue(":author", QString::fromStdString(map.getAuthor()));
        query.bindValue(":title", QString::fromStdString(map.getTitle()));
        query.bindValue(":md5sum", QString::fromStdString(map.getMD5Sum()));
        query.bindValue(":size", map.getSize());
        query.bindValue(":date", QString::fromStdString(map.getDate()));
        query.bindValue(":description", QString::fromStdString(map.getDescription()));
        query.bindValue(":zipbasedir", QString::fromStdString(map.getZipBaseDir()));
        query.bindValue(":commandline", QString::fromStdString(map.getCommandLine()));
        query.bindValue(":startmap", QString::fromStdString(map.getStartMap()));
        query.bindValue(":thumbnail", QByteArray(reinterpret_cast<const char *>(map.getThumbnail().data()),
                                                 static_cast<qsizetype>(map.getThumbnail().size())));
        query.bindValue(":favorited", false);  // Assuming default values for new maps
        query.bindValue(":downloaded", false); // Assuming default values for new maps

        if (!query.exec()) {
            qCritical() << "Error inserting map" << map.getMapID().c_str() << ":" << query.lastError().text();
            m_db.rollback(); // Rollback the transaction in case of an error
            return;
        }
    }

    // Commit the transaction
    if (!m_db.commit()) {
        qCritical() << "Error committing transaction:" << m_db.lastError().text();
        m_db.rollback(); // Rollback if the commit fails
    }
}
