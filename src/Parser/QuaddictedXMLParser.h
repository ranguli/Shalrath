#pragma once

// NOLINTBEGIN
#include <QList>
#include <QString>
#include <QXmlStreamReader>
// NOLINTEND

#include "../Model/Map.h"

class QuaddictedXMLParser {
  public:
    static auto parse(const QString &xmlContent) -> QList<Map>;

  private:
    static void parseFileElementAttributes(QXmlStreamReader &xml, Map &map);
    static void parseFileElementChildren(QXmlStreamReader &xml, Map &map);
};
