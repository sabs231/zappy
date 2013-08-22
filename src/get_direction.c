/*
** get_direction.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jul 01 17:04:16 2013 Sergio Baez
** Last update Fri Jul 12 15:06:59 2013 fabien massaro
*/

#include	"get_direction.h"
#include	"my_functions.h"
#include	"server_error_functions.h"

int		g_map[9] = {2, 1, 8, 3, 0, 7, 4, 5, 6};

static void	update_raw(t_cell *c, t_cell *from,
		t_server *server, int **world)
{
  u_int		count;

  count = (2 * c->food) + 2;
  while (--count > 0)
    {
      c->y = my_modulo(from->y + c->food, server->height);
      if (world[c->x][c->y] == -1 || world[c->x][c->y] > (int)c->food)
	world[c->x][c->y] = c->food;
      c->y = my_modulo(from->y - c->food, server->height);
      if (world[c->x][c->y] == -1 || world[c->x][c->y] > (int)c->food)
	world[c->x][c->y] = c->food;
      c->x = my_modulo(c->x + 1, server->width);
    }
  count = (2 * c->food) + 2;
  while (--count > 0)
    {
      c->x = my_modulo(from->x + c->food, server->width);
      if (world[c->x][c->y] == -1 || world[c->x][c->y] > (int)c->food)
	world[c->x][c->y] = c->food;
      c->x = my_modulo(from->x - c->food, server->width);
      if (world[c->x][c->y] == -1 || world[c->x][c->y] > (int)c->food)
	world[c->x][c->y] = c->food;
      c->y = my_modulo(c->y + 1, server->height);
    }
}

static void	init_map(int **world, t_server *server, int val)
{
  u_int		i;
  u_int		j;

  i = 0;
  while (i < server->height)
    {
      j = 0;
      while (j < server->width)
	{
	  world[j][i] = val;
	  j++;
	}
      i++;
    }
}

static int	get_lower_direction(t_client *p, int **world, t_server *server)
{
  int		tab[9];
  int		map[9];
  t_counters	c;

  c.min = 0;
  c.j = -1;
  while (c.j < 2)
    {
      c.i = -1;
      while (c.i < 2)
	{
	  tab[c.min] = world[my_modulo(p->my_cell->x + c.i, server->width)]
	    [my_modulo(p->my_cell->y + c.j, server->height)];
	  c.min++;
	  c.i++;
	}
      c.j++;
    }
  get_good_tab(map, p);
  return (best_direction(tab, map));
}

static int	get_player_direction(t_client *player,
				t_cell *from, t_server *server)
{
  int		**world;
  t_cell	cell;
  int		max;
  u_int		x;

  if ((world = my_malloc(sizeof(int *) * server->width, CELL)) == NULL)
    return (0);
  x = -1;
  while (++x < server->width)
    {
      if ((world[x] = my_malloc(sizeof(int) * server->height, CELL)) == NULL)
	return (0);
    }
  init_map(world, server, -1);
  world[from->x][from->y] = 0;
  cell.food = 0;
  max = MAX(server->width, server->height);
  while ((int)++cell.food < max)
    {
      cell.x = my_modulo(from->x - cell.food, server->width);
      update_raw(&cell, from, server, world);
    }
  max = get_lower_direction(player, world, server);
  free_map(world, server);
  return (max);
}

int		get_direction(t_client *player, t_client *from, t_server *server)
{
  int		res;

  if (player->my_cell == from->my_cell)
    return (0);
  res = get_player_direction(player, from->my_cell, server);
  if (res == -1)
    return (-1);
  return (res);
}
