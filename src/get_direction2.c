/*
** get_direction2.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jul 01 17:04:16 2013 Sergio Baez
** Last update Fri Jul 12 15:05:43 2013 fabien massaro
*/

#include	"get_direction.h"

extern int	g_map[9];

void		get_good_tab(int map[9], t_client *player)
{
  int		dir;
  int		offset;
  int		i;

  offset = 0;
  dir = NORTH;
  while (dir != (int)player->direction.front)
    {
      offset += 2;
      dir++;
    }
  i = 0;
  while (i < 9)
    {
      if (g_map[i] != 0)
	{
	  map[i] = g_map[i] + offset;
	  if (map[i] > 8)
	    map[i] = map[i] % 8;
	}
      else
	map[i] = g_map[i];
      i++;
    }
}

int		best_direction(int tab[9], int map[9])
{
  int		indice;
  int		lowest;
  int		i;

  indice = 0;
  lowest = tab[0];
  i = 0;
  while (i < 9)
    {
      if (lowest > tab[i])
	{
	  lowest = tab[i];
	  indice = i;
	}
      i++;
    }
  return (map[indice]);
}

void		free_map(int **world, t_server *server)
{
  int		i;

  i = -1;
  while (++i < (int)server->width)
    free(world[i]);
  free(world);
}
