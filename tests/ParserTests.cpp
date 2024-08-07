#include <gtest/gtest.h>
#include <QFile>
#include <QDir>
#include "QuaddictedXMLParser.h"
#include "Map.h"

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
};

TEST_F(QuaddictedXMLParserTest, ParseMapXML) {
    QString xmlContent = loadFixture("quaddicted_database.xml");
    ASSERT_FALSE(xmlContent.isEmpty()) << "Test fixture is empty";

    QuaddictedXMLParser parser;
    QList<Map> maps = parser.parse(xmlContent);

    ASSERT_FALSE(maps.isEmpty()) << "Parsed maps list is empty";

    // Validate some fields for the first map
    const Map& firstMap = maps.first();
    EXPECT_EQ(firstMap.getMapID(), "002blue");
    EXPECT_EQ(firstMap.getTitle(), "Blue Is The Darkest Shade");
    EXPECT_EQ(firstMap.getAuthor(), "sodalimonada176");
    EXPECT_EQ(firstMap.getSize(), 593);
    EXPECT_EQ(firstMap.getDate(), "08.10.2022");
    EXPECT_EQ(firstMap.getDescription().substr(0, 34), "Small blue medieval castle map for");
    // Add more validations as needed
}
