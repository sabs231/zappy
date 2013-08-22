#include <list>

#ifndef SPRITES_HPP_
# define SPRITES_HPP_

class Sprites
{
public:
  ~Sprites();
  Sprites(const std::string &name);
  void			run();
  operator Sprite() const;


private:
  std::vector<sf::Sprite>	_sprites;
  int				_cur;
};

#endif /* !SPRITES_HPP_ */
