#include <iostream>
#include <pthread.h>

#include "Socket.hpp"
#include "Graphics.hpp"
#include "Utils.hpp"

int		main(int ac, char **av)
{
  if (ac < 3)
  {
    std::cout << "./graphics ip port" << std::endl;
    return (0);
  }

  try
  {
    Graphics	graphics;
    pthread_t	thread;

    Socket::init(std::string(av[1]), Utils::toVal<int>(av[2]));
    pthread_create(&thread, NULL, &Socket::run, NULL);
    graphics.loop();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  exit(0);
  return (0);
}
