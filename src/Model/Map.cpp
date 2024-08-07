#include "Map.h"

// Getters
std::string Map::getMapID() const { return map_id; }

int Map::getType() const { return type; }

int Map::getRating() const { return rating; }

double Map::getNormalizedUsersRating() const { return normalized_users_rating; }

std::string Map::getAuthor() const { return author; }

std::string Map::getTitle() const { return title; }

std::string Map::getMD5Sum() const { return md5sum; }

int Map::getSize() const { return size; }

std::string Map::getDate() const { return date; }

std::string Map::getDescription() const { return description; }

std::string Map::getZipBaseDir() const { return zipbasedir; }

std::string Map::getCommandLine() const { return commandline; }

std::string Map::getStartMap() const { return startmap; }

std::vector<unsigned char> Map::getThumbnail() const { return thumbnail; }

// Setters
void Map::setMapID(const std::string& new_map_id) { map_id = new_map_id; }

void Map::setType(int new_type) { type = new_type; }

void Map::setRating(int new_rating) { rating = new_rating; }

void Map::setNormalizedUsersRating(double new_normalized_users_rating) {
    normalized_users_rating = new_normalized_users_rating;
}

void Map::setAuthor(const std::string& new_author) { author = new_author; }

void Map::setTitle(const std::string& new_title) { title = new_title; }

void Map::setMD5Sum(const std::string& new_md5sum) { md5sum = new_md5sum; }

void Map::setSize(int new_size) { size = new_size; }

void Map::setDate(const std::string& new_date) { date = new_date; }

void Map::setDescription(const std::string& new_description) { description = new_description; }

void Map::setZipBaseDir(const std::string& new_zipbasedir) { zipbasedir = new_zipbasedir; }

void Map::setCommandLine(const std::string& new_commandline) { commandline = new_commandline; }

void Map::setStartMap(const std::string& new_startmap) { startmap = new_startmap; }

void Map::setThumbnail(const std::vector<unsigned char>& new_thumbnail) {
    thumbnail = new_thumbnail;
}
