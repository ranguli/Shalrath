#include <exception>
#include <string>

class XMLParseException : public std::exception {
  public:
    explicit XMLParseException(const std::string &message) : msg_(message) {}

    virtual const char *what() const noexcept override { return msg_.c_str(); }

  private:
    std::string msg_;
};
