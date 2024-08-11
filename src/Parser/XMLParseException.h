// NOLINTBEGIN
#include <exception>
#include <string>
// NOLINTEND

class XMLParseException : public std::exception {
  public:
    explicit XMLParseException(const std::string &message) : msg_(message) {}

    const char *what() const noexcept override { return msg_.c_str(); }

  private:
    std::string msg_;
};
