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
    void setMapID(const string &new_map_id);
    void setType(int new_type);
    void setNormalizedUsersRating(double new_normalized_users_rating);
    void setAuthor(const string &new_author);
    void setTitle(const string &new_title);
    void setMD5Sum(const string &new_md5sum);
    void setSize(int new_size);
    void setDate(const string &new_date);
    void setDescription(const string &new_description);
    void addTag(const std::string &tag);
    void setZipBaseDir(const string &new_zipbasedir);
    void setCommandLine(const string &new_commandline);
    void setStartMap(const string &new_startmap);
    void setThumbnail(const vector<unsigned char> &new_thumbnail);

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
