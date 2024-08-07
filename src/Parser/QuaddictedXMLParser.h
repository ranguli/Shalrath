#pragma once

#include <QList>
#include <QString>

#include "../Model/Map.h"

class QuaddictedXMLParser {
   public:
    QList<Map> parse(const QString &xmlContent);
};
