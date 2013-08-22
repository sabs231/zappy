#include <unistd.h>

#include "Graphics.hpp"
#include "Map.hpp"

Graphics::~Graphics()
{
}

sf::Texture	&Graphics::createTexture(std::string const &str)
{
   sf::Texture	*texture = new sf::Texture();

  texture->loadFromFile(str);
  _textures.push_back(texture);
  return (*texture);
}
Graphics::Graphics() : _winW(800), _winH(600), _tileSize(64), _charSize(32), _itemSize(8),
	_cameraPos(0, 0), _window(sf::VideoMode(_winW, _winH), "Zappy"),
	_teamShape(sf::Vector2f(32, 4))
{
  _bg_sprite = sf::Sprite(createTexture("data/background.png"));
  _teamShape.setOrigin(16, 16);

  // Level 1
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level1.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level2.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level3.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level4.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level5.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level6.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level7.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level8.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level8.png")));
  _levels_sprites.push_back(new sf::Sprite(createTexture("data/level8.png")));

  // Level 2
  _items_sprites.push_back(new sf::Sprite(createTexture("data/food.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res1.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res2.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res3.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res4.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res5.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res6.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res7.png")));

  _items_sprites.push_back(new sf::Sprite(createTexture("data/res7.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res7.png")));
  _items_sprites.push_back(new sf::Sprite(createTexture("data/res7.png")));
}

void	Graphics::print()
{
  if (Map::isInit() == false)
    return ;
  _window.clear();
  printItems();
  printPlayers();
  _window.display();
}

sf::Color		Graphics::strToColor(std::string const &str) const
{
  unsigned int		v = 0;
  unsigned char		red = (unsigned char) str.c_str()[0] * 737373737;
  unsigned int		tmp;

  for (unsigned int i = 0; i < str.length(); i++)
  {
    tmp = ((unsigned int) str.c_str()[i]);
    if (i % 2)
      v *= tmp;
    else
      v += tmp;
  }
  //return (sf::Color(v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF));
  return (sf::Color(v & 0xFF, (v >> 8) & 0xFF, red));
}

void				Graphics::printPlayers()
{
  std::map<int, Player> const	&players = Map::getPlayers();
  int				levelId;

  for (std::map<int, Player>::const_iterator iter = players.begin(); iter != players.end(); ++iter)
  {
    levelId = (iter->second.level - 1) % 10;
    _levels_sprites[levelId]->setOrigin(16, 16);
    _levels_sprites[levelId]->setRotation(iter->second.dir * 90 + 180);
    //_levels_sprites[(iter->second.level - 1) % 10]->setOrigin(0, 0);
    _levels_sprites[levelId]->setPosition(
	(iter->second.x - 1) * _tileSize - _cameraPos.x + (iter->first * 7) % 32 + 16,
	     (iter->second.y - 1) * _tileSize - _cameraPos.y + (iter->first * 3) % 32 + 16);
    _window.draw(*_levels_sprites[levelId]);
    _teamShape.setFillColor(strToColor(iter->second.team));
    _teamShape.setPosition(_levels_sprites[levelId]->getPosition());
    _window.draw(_teamShape);
  }
  Map::releaseMutex();
}

void			Graphics::printItems()
{
  sf::Vector2i		pos(-_tileSize - _cameraPos.x % _tileSize,
     			 -_tileSize - _cameraPos.y % _tileSize);

  for (int j = 0; pos.y + j * _tileSize < _winH && j + _cameraPos.y / _tileSize < Map::height(); j++)
  {
    if ( j + _cameraPos.y / _tileSize < 0)
      continue ;
    for (int i = 0; pos.x + i * _tileSize < _winW && i + _cameraPos.x / _tileSize < Map::width(); i++)
    {
      if ( i + _cameraPos.x / _tileSize < 0)
        continue ;
      _bg_sprite.setPosition(pos.x + i * _tileSize, pos.y + j * _tileSize);
      _window.draw(_bg_sprite);
      Map::Cell const &cell =
		Map::cell(i + _cameraPos.x / _tileSize, j + _cameraPos.y / _tileSize);

      for (int k = 0; k < Res::COUNT; k++)
	for (int l = 0; l < cell.res[k]; l++)
	{
	  _items_sprites[k]->setPosition(pos.x + i * _tileSize + l * _itemSize,
	      pos.y + j * _tileSize + k * _itemSize);
	  _window.draw(*_items_sprites[k]);
	}
    }
  }
}

void			Graphics::loop()
{
  while (Map::alive)
  {
    print();
    input();
    usleep(10000);
  }
  _window.close();
}

void			Graphics::input()
{
  sf::Event event;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    _cameraPos.y += 10;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    _cameraPos.y -= 10;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    _cameraPos.x -= 10;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    _cameraPos.x += 10;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    Map::alive = false;
  while (_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      Map::alive = false;
  }
}
