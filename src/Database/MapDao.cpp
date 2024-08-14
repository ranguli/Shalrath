#include "MapDao.h" // Ensure this is the correct path to the MapDao header
#include "Map.h"    // Ensure this is the correct path to the Map class header

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

// Your existing MapDao implementation

MapDao::MapDao(QSqlDatabase &database) : m_db(database) {
    // Initialization or any additional logic
}

void MapDao::bulkInsertMaps(const std::vector<Map> &maps) {
    m_db.transaction();

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO maps (map_id, type, normalized_users_rating, author, title, md5sum, size, date, "
                  "description, zipbasedir, commandline, startmap, thumbnail, favorited, downloaded, dependencies) "
                  "VALUES (:map_id, :type, :normalized_users_rating, :author, :title, :md5sum, :size, :date, "
                  ":description, :zipbasedir, :commandline, :startmap, :thumbnail, :favorited, :downloaded, :dependencies)");

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

        QByteArray thumbnailData(reinterpret_cast<const char *>(map.getThumbnail().data()),
                                 static_cast<qsizetype>(map.getThumbnail().size()));
        query.bindValue(":thumbnail", thumbnailData.isEmpty() ? QVariant(QMetaType(QMetaType::QByteArray)) : QVariant(thumbnailData));

        query.bindValue(":dependencies", QString::fromStdString(map.getDependencies()));

        query.bindValue(":favorited", false);  // Default value
        query.bindValue(":downloaded", false); // Default value

        if (!query.exec()) {
            qCritical() << "Error inserting map" << map.getMapID().c_str() << ":" << query.lastError().text();
            m_db.rollback();
            return;
        }
    }

    if (!m_db.commit()) {
        qCritical() << "Error committing transaction:" << m_db.lastError().text();
        m_db.rollback();
    }
}

std::vector<Map> MapDao::getAllMaps() {
    std::vector<Map> maps;

    QSqlQuery query(m_db);
    query.prepare("SELECT map_id, type, normalized_users_rating, author, title, md5sum, size, date, "
                  "description, zipbasedir, commandline, startmap, thumbnail, dependencies "
                  "FROM maps");

    if (query.exec()) {
        while (query.next()) {
            Map map;
            map.setMapID(query.value("map_id").toString().toStdString());
            map.setType(query.value("type").toInt());
            map.setNormalizedUsersRating(query.value("normalized_users_rating").toDouble());
            map.setAuthor(query.value("author").toString().toStdString());
            map.setTitle(query.value("title").toString().toStdString());
            map.setMD5Sum(query.value("md5sum").toString().toStdString());
            map.setSize(query.value("size").toInt());
            map.setDate(query.value("date").toString().toStdString());
            map.setDescription(query.value("description").toString().toStdString());
            map.setZipBaseDir(query.value("zipbasedir").toString().toStdString());
            map.setCommandLine(query.value("commandline").toString().toStdString());
            map.setStartMap(query.value("startmap").toString().toStdString());

            // Fetch and store the thumbnail data
            QByteArray byteArray = query.value("thumbnail").toByteArray();
            std::vector<unsigned char> thumbnail(byteArray.begin(), byteArray.end());
            map.setThumbnail(thumbnail);

            map.setDependencies(query.value("dependencies").toString().toStdString());

            maps.push_back(map);
        }
    } else {
        qCritical() << "Error fetching maps:" << query.lastError().text();
    }

    return maps;
}