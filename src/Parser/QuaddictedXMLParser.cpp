#include "QuaddictedXMLParser.h"

#include <QDebug>
#include <QXmlStreamReader>

QList<Map> QuaddictedXMLParser::parse(const QString &xmlContent) {
    QList<Map> maps;

    QXmlStreamReader xml(xmlContent);
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QStringLiteral("file")) {
                Map map;

                map.setMapID(xml.attributes().value(QStringLiteral("id")).toString().toStdString());
                map.setType(xml.attributes().value(QStringLiteral("type")).toInt());
                map.setRating(xml.attributes().value(QStringLiteral("rating")).toInt());
                map.setNormalizedUsersRating(
                    xml.attributes().value(QStringLiteral("normalized_users_rating")).toDouble());

                while (!(xml.isEndElement() && xml.name() == QStringLiteral("file"))) {
                    xml.readNext();

                    if (xml.isStartElement()) {
                        QString elementName = xml.name().toString();

                        if (elementName == QStringLiteral("author")) {
                            map.setAuthor(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("title")) {
                            map.setTitle(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("md5sum")) {
                            map.setMD5Sum(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("size")) {
                            map.setSize(xml.readElementText().toInt());
                        } else if (elementName == QStringLiteral("date")) {
                            map.setDate(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("description")) {
                            map.setDescription(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("zipbasedir")) {
                            map.setZipBaseDir(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("commandline")) {
                            map.setCommandLine(xml.readElementText().toStdString());
                        } else if (elementName == QStringLiteral("startmap")) {
                            map.setStartMap(xml.readElementText().toStdString());
                        }
                    }
                }

                maps.append(map);
            }
        }
    }

    if (xml.hasError()) {
        qDebug() << "Error parsing XML:" << xml.errorString();
    }

    return maps;
}
