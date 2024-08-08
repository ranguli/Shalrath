#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QDir>
#include <QFile>

#include "Map.h"
#include "QuaddictedXMLParser.h"
#include "XMLParseException.h"

using std::string;
using std::vector;

using namespace testing;

class QuaddictedXMLParserTest : public ::testing::Test {
  protected:
    QString loadFixture(const QString &fixtureName) {
        QString fixturePath = QDir::currentPath() + "/tests/" + fixtureName;

        QFile file(fixturePath);
        if (!file.exists()) {
            qDebug() << "File does not exist: " << fixturePath;
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file: " << fixturePath;
            return "";
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();
        return content;
    }

    QList<Map> parseFixture(const QString &fixtureName) {
        QString xmlContent = loadFixture(fixtureName);
        EXPECT_FALSE(xmlContent.isEmpty()) << "Test fixture is empty";

        QuaddictedXMLParser parser;
        QList<Map> maps = parser.parse(xmlContent);

        EXPECT_FALSE(maps.isEmpty()) << "Parsed maps list is empty";
        return maps;
    }
};

TEST_F(QuaddictedXMLParserTest, ParsesMapIDCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getMapID(), "002blue");
}

TEST_F(QuaddictedXMLParserTest, ParsesTitleCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getTitle(), "Blue Is The Darkest Shade");
}

TEST_F(QuaddictedXMLParserTest, ParsesAuthorCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getAuthor(), "sodalimonada176");
}

TEST_F(QuaddictedXMLParserTest, ParsesSizeCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getSize(), 593);
}

TEST_F(QuaddictedXMLParserTest, ParsesDateCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getDate(), "08.10.2022");
}

TEST_F(QuaddictedXMLParserTest, ParsesDescriptionCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getDescription().substr(0, 34), "Small blue medieval castle map for");
}

TEST_F(QuaddictedXMLParserTest, ParsesZipBaseDirCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_EQ(firstMap.getZipBaseDir(), "id1/maps/");
}

TEST_F(QuaddictedXMLParserTest, ParsesTagsCorrectly) {
    auto maps = parseFixture("quaddicted_database.xml");
    const Map &firstMap = maps.first();
    EXPECT_THAT(firstMap.getTags(), ElementsAre("small", "medieval", "castle", "classic", "vanilla", "id1"));
}

/**
 * Test that we can simply parse the entire XML file without anything catching on fire.
 */
TEST_F(QuaddictedXMLParserTest, ParseAllFilesInXML) {
    QString xmlContent = loadFixture("quaddicted_database.xml");
    ASSERT_FALSE(xmlContent.isEmpty()) << "Test fixture is empty";

    QuaddictedXMLParser parser;

    try {
        QList<Map> maps = parser.parse(xmlContent);
        ASSERT_FALSE(maps.isEmpty()) << "Parsed maps list is empty";

        QXmlStreamReader xml(xmlContent);

        for (int i = 0; i < maps.size(); ++i) {
            const Map &map = maps[i];

            // Find the corresponding <file> element in the XML
            while (!xml.atEnd() && !xml.hasError()) {
                xml.readNext();
                if (xml.isStartElement() && xml.name() == QStringLiteral("file")) {
                    if (xml.attributes().value("id").toString().toStdString() == map.getMapID()) {
                        break;
                    }
                }
            }

            // Get the relevant section of the XML
            QString xmlSnippet;
            xmlSnippet = xml.readElementText(QXmlStreamReader::IncludeChildElements);
        }

        if (xml.hasError()) {
            throw XMLParseException("Error parsing XML: " + xml.errorString().toStdString());
        }
    } catch (const XMLParseException &e) {
        FAIL() << "XMLParseException: " << e.what();
    }
}