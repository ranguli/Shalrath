// NOLINTBEGIN
#include <exception>
#include <string>
// NOLINTEND

using std::exception;
using std::string;

class XMLParseException : public exception { // NOLINT(cppcoreguidelines-special-member-functions)
  public:
    explicit XMLParseException(const string &message) : msg_(message) {}

    [[nodiscard]] auto what() const noexcept -> const char * override { return msg_.c_str(); }

  private:
    string msg_;
};
