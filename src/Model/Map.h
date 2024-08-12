#pragma once

// NOLINTBEGIN
#include <string>
#include <vector>
// NOLINTEND

using std::string;
using std::vector;

class Map {
  public:
    // Constructors
    Map() = default;

    // Getters
    [[nodiscard]] auto getMapID() const -> string;
    [[nodiscard]] auto getType() const -> int;
    [[nodiscard]] auto getNormalizedUsersRating() const -> double;
    [[nodiscard]] auto getAuthor() const -> string;
    [[nodiscard]] auto getTitle() const -> string;
    [[nodiscard]] auto getMD5Sum() const -> string;
    [[nodiscard]] auto getSize() const -> int;
    [[nodiscard]] auto getDate() const -> string;
    [[nodiscard]] auto getDescription() const -> string;
    [[nodiscard]] auto getTags() const -> const vector<string> &;
    [[nodiscard]] auto getZipBaseDir() const -> string;
    [[nodiscard]] auto getCommandLine() const -> string;
    [[nodiscard]] auto getStartMap() const -> string;
    [[nodiscard]] auto getThumbnail() const -> vector<unsigned char>;

    // Setters
    void setMapID(const string &newMapID);
    void setType(int newType);
    void setNormalizedUsersRating(double newNormalizedUsersRating);
    void setAuthor(const string &newAuthor);
    void setTitle(const string &newTitle);
    void setMD5Sum(const string &newMD5Sum);
    void setSize(int newSize);
    void setDate(const string &newDate);
    void setDescription(const string &newDescription);
    void addTag(const std::string &tag);
    void setZipBaseDir(const string &newZipBaseDir);
    void setCommandLine(const string &newCommandline);
    void setStartMap(const string &newStartmap);
    void setThumbnail(const vector<unsigned char> &newThumbnail);

  private:
    string mapID;
    int type = 0;
    double normalizedUsersRating = 0.0;
    string author;
    string title;
    string MD5Sum;
    int size = 0;
    string date;
    string description;
    vector<string> tags;
    string zipBaseDir;
    string commandLine;
    string startMap;
    vector<unsigned char> thumbnail;
};
