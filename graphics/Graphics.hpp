#include <SFML/Graphics.hpp>

#ifndef GRAPHICS_HPP_
# define GRAPHICS_HPP_

class Graphics
{
public:
  ~Graphics();
  Graphics();
  void		loop();
private:
  void		print();
  void		printItems();
  void		printPlayers();
  void		input();
  sf::Color	strToColor(std::string const &str) const;
  sf::Texture	&createTexture(std::string const &str);

  /*
  void		printPlayer(int level, int team, int x, int y, cardinal_dir dir) const;
  void		printMineral(t_mineral type, int x, int y) const;
  void		printBackground() const;
  */


 
private:
  const int			_winW;
  const int			_winH;
  const int			_tileSize;
  const int			_charSize;
  const int			_itemSize;
  sf::Vector2i			_cameraPos;

  sf::RenderWindow		_window;
  sf::RectangleShape		_teamShape;
  std::vector<sf::Texture *>	_textures;

  std::vector<sf::Sprite *>	_levels_sprites;
  std::vector<sf::Sprite *>	_items_sprites;


  sf::Sprite			_bg_sprite;
};

#endif /* !GRAPHICS_HPP_ */
