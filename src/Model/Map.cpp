#include <string>
#include <vector>

#include "Map.h"

using std::string;
using std::vector;

// Getters
auto Map::getMapID() const -> string {
    return mapID;
}

auto Map::getType() const -> int {
    return type;
}

auto Map::getNormalizedUsersRating() const -> double {
    return normalizedUsersRating;
}

auto Map::getAuthor() const -> string {
    return author;
}

auto Map::getTitle() const -> string {
    return title;
}

auto Map::getMD5Sum() const -> string {
    return MD5Sum;
}

auto Map::getSize() const -> int {
    return size;
}

auto Map::getDate() const -> string {
    return date;
}

auto Map::getDescription() const -> string {
    return description;
}

auto Map::getTags() const -> const vector<string> & {
    return tags;
}

auto Map::getZipBaseDir() const -> string {
    return zipBaseDir;
}

auto Map::getCommandLine() const -> string {
    return commandLine;
}

auto Map::getStartMap() const -> string {
    return startMap;
}

auto Map::getThumbnail() const -> vector<unsigned char> {
    return thumbnail;
}

// Setters
void Map::setMapID(const string &newMapID) {
    mapID = newMapID;
}

void Map::setType(int newType) {
    type = newType;
}

void Map::setNormalizedUsersRating(double newNormalizedUsersRating) {
    normalizedUsersRating = newNormalizedUsersRating;
}

void Map::setAuthor(const string &newAuthor) {
    author = newAuthor;
}

void Map::setTitle(const string &newTitle) {
    title = newTitle;
}

void Map::setMD5Sum(const string &newMD5Sum) {
    MD5Sum = newMD5Sum;
}

void Map::setSize(int newSize) {
    size = newSize;
}

void Map::setDate(const string &newDate) {
    date = newDate;
}

void Map::setDescription(const string &newDescription) {
    description = newDescription;
}

void Map::addTag(const string &tag) {
    tags.push_back(tag);
}

void Map::setZipBaseDir(const string &newZipBaseDir) {
    zipBaseDir = newZipBaseDir;
}

void Map::setCommandLine(const string &newCommandLine) {
    commandLine = newCommandLine;
}

void Map::setStartMap(const string &newStartMap) {
    startMap = newStartMap;
}

void Map::setThumbnail(const vector<unsigned char> &newThumbnail) {
    thumbnail = newThumbnail;
}
