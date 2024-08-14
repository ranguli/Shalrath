// NOLINTBEGIN
#include <string>
#include <vector>

#include <QSqlDatabase>
// NOLINTEND

#include "Map.h"

class MapDao {
  public:
    explicit MapDao(QSqlDatabase &database);

    // CRUD Operations
    void addMap(const Map &map);
    std::vector<Map> getAllMaps();

    // Bulk insertion method
    void bulkInsertMaps(const std::vector<Map> &maps);

  private:
    QSqlDatabase &m_db;
};
