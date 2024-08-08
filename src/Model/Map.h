#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Map {
  public:
    // Constructors
    Map() = default;

    // Getters
    string getMapID() const;
    int getType() const;
    int getRating() const;
    double getNormalizedUsersRating() const;
    string getAuthor() const;
    string getTitle() const;
    string getMD5Sum() const;
    int getSize() const;
    string getDate() const;
    string getDescription() const;
    vector<string> getTags() const;
    string getZipBaseDir() const;
    string getCommandLine() const;
    string getStartMap() const;
    vector<unsigned char> getThumbnail() const;

    // Setters
    void setMapID(const string &new_map_id);
    void setType(int new_type);
    void setRating(int new_rating);
    void setNormalizedUsersRating(double new_normalized_users_rating);
    void setAuthor(const string &new_author);
    void setTitle(const string &new_title);
    void setMD5Sum(const string &new_md5sum);
    void setSize(int new_size);
    void setDate(const string &new_date);
    void setDescription(const string &new_description);
    void setZipBaseDir(const string &new_zipbasedir);
    void setCommandLine(const string &new_commandline);
    void setStartMap(const string &new_startmap);
    void setThumbnail(const vector<unsigned char> &new_thumbnail);

  private:
    string map_id;
    int type = 0;
    int rating = 0;
    double normalized_users_rating = 0.0;
    string author;
    string title;
    string md5sum;
    int size = 0;
    string date;
    string description;
    vector<string> tags;
    string zipbasedir;
    string commandline;
    string startmap;
    vector<unsigned char> thumbnail;
};
