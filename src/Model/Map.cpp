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

void Map::setAuthor(const std::string &newAuthor) {
    author = newAuthor;
}

void Map::setTitle(const std::string &newTitle) {
    title = newTitle;
}

void Map::setMD5Sum(const std::string &newMD5Sum) {
    MD5Sum = newMD5Sum;
}

void Map::setSize(int new_size) {
    size = new_size;
}

void Map::setDate(const std::string &new_date) {
    date = new_date;
}

void Map::setDescription(const std::string &newDescription) {
    description = newDescription;
}

void Map::addTag(const std::string &tag) {
    tags.push_back(tag);
}

void Map::setZipBaseDir(const std::string &newZipBaseDir) {
    zipBaseDir = newZipBaseDir;
}

void Map::setCommandLine(const std::string &newCommandLine) {
    commandLine = newCommandLine;
}

void Map::setStartMap(const std::string &newStartMap) {
    startMap = newStartMap;
}

void Map::setThumbnail(const std::vector<unsigned char> &newThumbnail) {
    thumbnail = newThumbnail;
}
