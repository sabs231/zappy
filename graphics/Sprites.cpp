#include "Sprites.hpp"
#include "Utils.hpp"

Sprites::~Sprites(){}

Sprites::Sprites(std::string const &name)
{
  sf::Texture	texture;
  for (int i = 0; texture.loadFromFile("data/" + name + "/" + Utils::toString(i)); i++)
      _sprites.pushBack(new sf::Sprite(texture));
  _cur = 0;
}

void	Sprites::run()
{
  if (++_cur >= _sprites.size())
    _cur = 0;
}

Sprites::operator Sprite() const
{
  return (_sprites[_cur]);
}
