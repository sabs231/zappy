
#ifndef IREQUEST_HPP_
# define IREQUEST_HPP_

# include "Connect.hpp"

class ARequest
{
public:
  ~ARequest(){}
  ARequest(std::string const &name);
  virtual void		run() = 0;
  bool			match(std::string const &str);

private:
  std::string		_name;
};

#endif /* !IREQUEST_HPP_ */
