#ifndef CONNECT_HPP_
# define CONNECT_HPP_

# include <sys/types.h>
# include <string>
# include <iostream>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include "Map.hpp"

# define	BUFF_SIZE	4096

class Socket
{
  public:
    typedef void (*PF)(std::string &);
    static bool			read();
    static bool			init(std::string const &ip, int port);
    static void			*run(void *);

  private:
    ~Socket();
    Socket();
    static int		_sock;
    static std::string	_buffer;
    static std::map<std::string, PF>	_cmd;

    static void			welcolm();
    static void			playerLevel(std::string &);
    static void			initMap(std::string &);
    static void			cellUpdated(std::string &);
    static void			newPlayer(std::string &);
    static void			playerMoved(std::string &);
    static void			playerDropped(std::string &);
    static void			playerTook(std::string &);
    static void			eggCreated(std::string &);
    static void			gameStop(std::string &);
    static void			playerStarve(std::string &);
    static void			playerExpulse(std::string &);
    static void			playerBroadcast(std::string &);
    static void			eggOpenned(std::string &);
};

std::string	&operator>>(std::string &str, std::string &buf);
std::string	&operator>>(std::string &str, int &buf);

#endif /* !CONNECT_HPP_ */
