#include "Map.hpp"

bool			Map::_isInit = false;
bool			Map::alive = true;
std::map<int, Player>	Map::_players;		
std::map<int, Egg>	Map::_eggs;		
int			Map::_w;
int			Map::_h;
std::vector<Map::Cell>	Map::_cells;
pthread_mutex_t		Map::_mutex;
	

void			Map::init(int w, int h)
{
  if (w < 1 || h < 1 || w > 300 || h > 300)
  {
    alive = false;
    std::cout << "Map size not valid : " << w << "/" << h << std::endl;
    return ;
  }
  _cells.resize(w * h);
  _w = w;
  _h = h;
  pthread_mutex_init(&_mutex, NULL);
  _isInit = true;
}

void			Map::kill(int id)
{
  pthread_mutex_lock(&_mutex);
  _players.erase(id);
  pthread_mutex_unlock(&_mutex);
}

void			Map::raise(int id, Player const &player)
{
  pthread_mutex_lock(&_mutex);
  _players[id] = player;
  pthread_mutex_unlock(&_mutex);
}

std::map<int, Player> const	&Map::getPlayers()
{
  pthread_mutex_lock(&_mutex);
  return (_players);
}

Player				&Map::getPlayer(int id)
{
  return (_players[id]);
}

void			Map::releaseMutex()
{
  pthread_mutex_unlock(&_mutex);
}

Map::Cell		&Map::cell(int x, int y)
{
  if (x < 0 || y < 0 || x > _w || y > _h)
  {
    alive = false;
    std::cout << "Index out of bounds : " << x << "/" << y << std::endl;
    x = 0;
    y = 0;
  }
  return (_cells[y * _w + x]);
}

bool			Map::isInit()
{
  return (_isInit);
}

int			Map::width()
{
  return (_w);
} 

int			Map::height()
{
  return (_h);
}
void			Map::breakEgg(int id)
{
  
  cell(_eggs[id].x, _eggs[id].y).res[Res::EGG]--;
  _eggs.erase(id);

}

void			Map::raise(int id, Egg const &egg)
{
  _eggs[id] = egg;
  cell(_eggs[id].x, _eggs[id].y).res[Res::EGG]++;
}
