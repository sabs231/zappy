# include <cstdlib>
# include <stdexcept>
# include "Socket.hpp"
# include "Utils.hpp"

int		Socket::_sock;
std::string	Socket::_buffer;
std::map<std::string, Socket::PF> 	Socket::_cmd;

bool		Socket::init(std::string const &ip, int port)
{
  Map::alive = false;
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  pe = getprotobyname("TCP");
  if (!pe)
    return (false);
  if ((_sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (false);
  s_in.sin_addr.s_addr = inet_addr(ip.c_str());
  s_in.sin_port = htons(port);
  s_in.sin_family = AF_INET;
  if (connect(_sock, (struct sockaddr *) &s_in, sizeof(s_in)) == -1)
  {
    std::cerr << "Could not connect" << std::endl;
    return (false);
  }

  // INIT MAP
  _cmd.insert(std::make_pair(std::string("msz"), &Socket::initMap));
  _cmd.insert(std::make_pair(std::string("bct"), &Socket::cellUpdated));
  _cmd.insert(std::make_pair(std::string("pnw"), &Socket::newPlayer));
  _cmd.insert(std::make_pair(std::string("ppo"), &Socket::playerMoved));
  _cmd.insert(std::make_pair(std::string("pdr"), &Socket::playerDropped));
  _cmd.insert(std::make_pair(std::string("pgt"), &Socket::playerTook));
  _cmd.insert(std::make_pair(std::string("enw"), &Socket::eggCreated));
  _cmd.insert(std::make_pair(std::string("seg"), &Socket::gameStop));
  _cmd.insert(std::make_pair(std::string("pdi"), &Socket::playerStarve));
  _cmd.insert(std::make_pair(std::string("pex"), &Socket::playerExpulse));
  _cmd.insert(std::make_pair(std::string("pbc"), &Socket::playerBroadcast));
  _cmd.insert(std::make_pair(std::string("eht"), &Socket::eggOpenned));
  _cmd.insert(std::make_pair(std::string("ebo"), &Socket::eggOpenned));
  _cmd.insert(std::make_pair(std::string("edi"), &Socket::eggOpenned));
  _cmd.insert(std::make_pair(std::string("plv"), &Socket::playerLevel));

  Map::alive = true;

  return (true);
}

void		*Socket::run(void *)
{
  size_t	len;

  while (Map::alive)
  {
    try
    {
      if (read())
      {
	// For each command found
	while ((len = _buffer.find('\n')) != std::string::npos)
	{
	  std::string cmd = _buffer.substr(0, len);
	  _buffer = _buffer.substr(len + 1);

	  if (cmd == "BIENVENUE")
	    welcolm();
	  else if (_cmd.find(cmd.substr(0, 3)) != _cmd.end())
	  {
	    std::string	subcmd = cmd.substr(3);
	    _cmd.find(cmd.substr(0, 3))->second(subcmd);
	  }
	}
      }
    }
    // Protocol crashed, start again
    catch (const std::exception &ex)
    {
      _buffer.clear();
    }
  }
  return (NULL);
}

bool		Socket::read()
{
  int		len;
  static char	buf[BUFF_SIZE];

  if ((len = recv(_sock, buf, BUFF_SIZE - 1, MSG_NOSIGNAL)) <= 0)
  {
    Map::alive = false;
    return (false);
  }
  if (!len)
    return (false);
  buf[len] = '\0';
  _buffer.append(buf);
  std::cout << _buffer << std::endl;
  return (true);
}

void		Socket::playerLevel(std::string &cmd)
{
  std::string id_s;
  cmd >> id_s;
  int id;
  id = Utils::toVal<int>(id_s.substr(1));

  Player &player = Map::getPlayer(id);
  cmd >> player.level;
}

void	Socket::initMap(std::string &str)
{
  int	x, y;

  str >> x >> y;
  Map::init(x, y);
}

void	Socket::cellUpdated(std::string &cmd)
{
  int	x, y;

  cmd >> x >> y;
  Map::Cell	&cell = Map::cell(x, y);
  cmd >> cell.res[Res::FOOD];
  cmd >> cell.res[Res::LINEMATE];
  cmd >> cell.res[Res::DERAUMERE];
  cmd >> cell.res[Res::SIBUR];
  cmd >> cell.res[Res::MENDIANE];
  cmd >> cell.res[Res::PHIRAS];
  cmd >> cell.res[Res::THYSTAME];
}

void	Socket::playerMoved(std::string &cmd)
{
  std::string id_s;
  cmd >> id_s;
  int id;
  id = Utils::toVal<int>(id_s.substr(1));
  Player &player = Map::getPlayer(id);
  cmd >> player.x;
  cmd >> player.y;
  cmd >> player.dir;
}

void	Socket::welcolm()
{
  // I'm a graphic
  send(_sock, "GRAPHIC\n", 8, MSG_NOSIGNAL);
}

void	Socket::newPlayer(std::string &cmd)
{
  Player player;

  std::string id_s;
  cmd >> id_s;
  int id;
  id = Utils::toVal<int>(id_s.substr(1));
  cmd >> player.x;
  cmd >> player.y;
  cmd >> player.dir;
  cmd >> player.level;
  cmd >> player.team;
  Map::raise(id, player);
}

void	Socket::playerDropped(std::string &cmd)
{
  int	id;
  std::string id_s;

  cmd >> id_s;
  id_s = id_s.substr(1);
  id_s >> id;
  const Player	&p = Map::getPlayer(id);
  int	rsrc;
  cmd >> rsrc;
  ++Map::cell(p.x, p.y).res[rsrc];
}

void	Socket::playerTook(std::string &cmd)
{
  int	id;
  std::string id_s;

  cmd >> id_s;
  id_s = id_s.substr(1);
  id_s >> id;
  const Player	&p = Map::getPlayer(id);
  int	rsrc;
  cmd >> rsrc;
  --Map::cell(p.x, p.y).res[rsrc];
}

void	Socket::eggCreated(std::string &cmd)
{
  int	id_e, id_p;

  // Id egg
  std::string id_e_s;
  cmd >> id_e_s;
  id_e_s = id_e_s.substr(1);
  id_e_s >> id_e;

  // Id player
  std::string id_p_s;
  cmd >> id_p_s;
  id_p_s = id_p_s.substr(1);
  id_p_s >> id_p;

  Egg egg;
  cmd >> egg.x >> egg.y;
  Map::raise(id_e, egg);
}

void	Socket::gameStop(std::string &)
{
  Map::alive = false;
}

void	Socket::playerStarve(std::string &cmd)
{
  int	id;
  std::string id_s;

  cmd >> id_s;
  id_s = id_s.substr(1);
  id_s >> id;
  Map::kill(id);
}

void	Socket::playerExpulse(std::string &)
{
}

void	Socket::playerBroadcast(std::string &)
{
}

void	Socket::eggOpenned(std::string &cmd)
{
  int	id_e;
  std::string id_s_e;

  cmd >> id_s_e;
  id_s_e = id_s_e.substr(1);
  id_s_e >> id_e;
  Map::breakEgg(id_e);
}

std::string	&operator>>(std::string &str, std::string &buf)
{
  std::stringstream	ss;

  ss << str;
  ss >> buf;
  std::getline(ss, str);
  return (str);
}

std::string	&operator>>(std::string &str, int &buf)
{
 std::string nb_str;

 str >> nb_str;
 buf = Utils::toVal<int>(nb_str);
 return (str);
}
