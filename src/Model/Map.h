#pragma once

#include <string>
#include <vector>

class Map {
   public:
    // Constructors
    Map() = default;

    // Getters
    std::string getMapID() const;
    int getType() const;
    int getRating() const;
    double getNormalizedUsersRating() const;
    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getMD5Sum() const;
    int getSize() const;
    std::string getDate() const;
    std::string getDescription() const;
    std::string getZipBaseDir() const;
    std::string getCommandLine() const;
    std::string getStartMap() const;
    std::vector<unsigned char> getThumbnail() const;

    // Setters
    void setMapID(const std::string& new_map_id);
    void setType(int new_type);
    void setRating(int new_rating);
    void setNormalizedUsersRating(double new_normalized_users_rating);
    void setAuthor(const std::string& new_author);
    void setTitle(const std::string& new_title);
    void setMD5Sum(const std::string& new_md5sum);
    void setSize(int new_size);
    void setDate(const std::string& new_date);
    void setDescription(const std::string& new_description);
    void setZipBaseDir(const std::string& new_zipbasedir);
    void setCommandLine(const std::string& new_commandline);
    void setStartMap(const std::string& new_startmap);
    void setThumbnail(const std::vector<unsigned char>& new_thumbnail);

   private:
    std::string map_id;
    int type = 0;
    int rating = 0;
    double normalized_users_rating = 0.0;
    std::string author;
    std::string title;
    std::string md5sum;
    int size = 0;
    std::string date;
    std::string description;
    std::string zipbasedir;
    std::string commandline;
    std::string startmap;
    std::vector<unsigned char> thumbnail;
};