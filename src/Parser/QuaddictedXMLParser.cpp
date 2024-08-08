#include "QuaddictedXMLParser.h"
#include "XMLParseException.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <functional>
#include <unordered_map>

const QString ELEMENT_FILE = QStringLiteral("file");
const QString ELEMENT_AUTHOR = QStringLiteral("author");
const QString ELEMENT_TITLE = QStringLiteral("title");
const QString ELEMENT_MD5SUM = QStringLiteral("md5sum");
const QString ELEMENT_SIZE = QStringLiteral("size");
const QString ELEMENT_DATE = QStringLiteral("date");
const QString ELEMENT_DESCRIPTION = QStringLiteral("description");
const QString ELEMENT_ZIPBASEDIR = QStringLiteral("zipbasedir");
const QString ELEMENT_COMMANDLINE = QStringLiteral("commandline");
const QString ELEMENT_STARTMAP = QStringLiteral("startmap");
const QString ELEMENT_TAG = QStringLiteral("tag");
const QString ELEMENT_RATING = QStringLiteral("normalized_users_rating");
const QString ELEMENT_TYPE = QStringLiteral("type");
const QString ELEMENT_ID = QStringLiteral("id");

auto QuaddictedXMLParser::parse(const QString &xmlContent) -> QList<Map> {
    QList<Map> maps;
    QXmlStreamReader xml(xmlContent);

    try {
        while (!xml.atEnd() && !xml.hasError()) {
            xml.readNext();

            if (!xml.isStartElement() || xml.name() != QStringLiteral("file")) {
                continue;
            }

            Map map;
            QuaddictedXMLParser::parseFileElementAttributes(xml, map);

            while (!(xml.isEndElement() && xml.name() == QStringLiteral("file"))) {
                xml.readNext();

                if (xml.isStartElement()) {
                    QuaddictedXMLParser::parseFileElementChildren(xml, map);
                }
            }

            maps.append(map);
        }

        if (xml.hasError()) {
            throw XMLParseException("Error parsing XML: " + xml.errorString().toStdString());
        }
    } catch (const XMLParseException &e) {
        qDebug() << "XMLParseException:" << e.what();
        throw; // Re-throw the exception to allow higher-level handling
    }

    return maps;
}

void QuaddictedXMLParser::parseFileElementAttributes(QXmlStreamReader &xml, Map &map) {
    map.setMapID(xml.attributes().value(ELEMENT_ID).toString().toStdString());
    map.setType(xml.attributes().value(ELEMENT_TYPE).toInt());
    map.setNormalizedUsersRating(xml.attributes().value(ELEMENT_RATING).toDouble());
}

void QuaddictedXMLParser::parseFileElementChildren(QXmlStreamReader &xml, Map &map) {
    static const std::unordered_map<QString, std::function<void(QXmlStreamReader &, Map &)>> elementHandlers = {
        {ELEMENT_AUTHOR, [](QXmlStreamReader &reader, Map &m) { m.setAuthor(reader.readElementText().toStdString()); }},
        {ELEMENT_TITLE, [](QXmlStreamReader &reader, Map &m) { m.setTitle(reader.readElementText().toStdString()); }},
        {ELEMENT_MD5SUM, [](QXmlStreamReader &reader, Map &m) { m.setMD5Sum(reader.readElementText().toStdString()); }},
        {ELEMENT_SIZE, [](QXmlStreamReader &reader, Map &m) { m.setSize(reader.readElementText().toInt()); }},
        {ELEMENT_DATE, [](QXmlStreamReader &reader, Map &m) { m.setDate(reader.readElementText().toStdString()); }},
        {ELEMENT_DESCRIPTION, [](QXmlStreamReader &reader, Map &m) { m.setDescription(reader.readElementText().toStdString()); }},
        {ELEMENT_ZIPBASEDIR, [](QXmlStreamReader &reader, Map &m) { m.setZipBaseDir(reader.readElementText().toStdString()); }},
        {ELEMENT_COMMANDLINE, [](QXmlStreamReader &reader, Map &m) { m.setCommandLine(reader.readElementText().toStdString()); }},
        {ELEMENT_STARTMAP, [](QXmlStreamReader &reader, Map &m) { m.setStartMap(reader.readElementText().toStdString()); }},
        {ELEMENT_TAG, [](QXmlStreamReader &reader, Map &m) { m.addTag(reader.readElementText().toStdString()); }},
    };

    const QString elementName = xml.name().toString();
    auto it = elementHandlers.find(elementName);
    if (it != elementHandlers.end()) {
        it->second(xml, map);
    } else if (elementName == QStringLiteral("tags")) {
        while (!(xml.isEndElement() && xml.name() == QStringLiteral("tags"))) {
            xml.readNext();
            if (xml.isStartElement() && xml.name() == QStringLiteral("tag")) {
                elementHandlers.at(QStringLiteral("tag"))(xml, map);
            }
        }
    } else {
        // Handle the case where the element name is not found
    }
}
