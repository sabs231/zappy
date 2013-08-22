
#ifndef UTILS_HPP_
# define UTILS_HPP_

# include <string>
# include <sstream>

class Utils
{
public:
  template <typename T>
  static std::string	toString(T val)
  {
    std::stringstream	stream;

    stream << val;
    return (stream.str());
  }

  template <typename T>
  static T	toVal(std::string const &str)
  {
    std::stringstream	stream;
    T 			val;

    stream << str;
    stream >> val;
    return (val);
  }

private:
  ~Utils();
  Utils();
  Utils(Utils const &other);
  Utils const		&operator=(Utils const &other);
};

#endif /* !UTILS_HPP_ */
