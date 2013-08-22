#include <iostream>

#ifndef MAP_HPP_
# define MAP_HPP_

# include <vector>
# include <string>
# include <pthread.h>
# include <map>

namespace Res
{
  enum
  {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG,
    COUNT
  };
}

struct Player
{
  int				dir;
  int				x;
  int				y;
  int				level;
  std::string			team;
};

struct Egg
{
  int				x;
  int				y;
};

class Map
{
public:

  struct Cell
  {
    int		res[Res::COUNT];
  };

public:
  static void				init(int w, int h);
  static void				kill(int id);
  static void				raise(int id, Player const &player);
  static Cell				&cell(int x, int y);
  static bool				isInit();
  static std::map<int, Player> const	&getPlayers();
  static Player				&getPlayer(int id);
  static void				releaseMutex();
  static int				width();
  static int				height();
  static void				breakEgg(int id);
  static void				raise(int id, Egg const &egg);

public:
  static bool			alive;
private:
  ~Map();
  Map();
  static std::vector<Cell>	_cells;
  static int			_w;
  static int			_h;
  static std::map<int, Player>	_players;		
  static std::map<int, Egg>	_eggs;		
  static bool			_isInit;
  static pthread_mutex_t	_mutex;
};

#endif /* !MAP_HPP_ */
