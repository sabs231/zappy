/*
** move_subcommands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 25 15:04:44 2013 Sergio Baez
** Last update Fri Jul 12 15:26:23 2013 fabien massaro
*/

#include	<string.h>
#include	"commands.h"
#include	"list.h"
#include	"my_functions.h"

void		move_player(t_client *player, t_list *src, t_list *dest)
{
  t_link	*prev;
  t_link	*tmp;

  prev = src->first;
  tmp = src->first->next;
  if (((t_client *)prev->data)->cs == player->cs)
    {
      src->first = prev->next;
      prev->next = dest->first;
      dest->first = prev;
      return ;
    }
  while (tmp)
    {
      if (((t_client *)tmp->data)->cs == player->cs)
	{
	  prev->next = tmp->next;
	  tmp->next = dest->first;
	  dest->first = tmp;
	  return ;
	}
      tmp = tmp->next;
      prev = prev->next;
    }
}

int		move_north(t_server *server, t_client *player)
{
  int		x;
  int		y;
  char		buff[32];

  memset(buff, '\0', 32);
  x = (int)player->my_cell->x;
  y = my_modulo(((int)player->my_cell->y - 1), server->height);
  move_player(player, player->my_cell->players, (server->world[x][y]).players);
  player->my_cell = &(server->world[x][y]);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, x, y,
	  graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}

int		move_south(t_server *server, t_client* player)
{
  int		x;
  int		y;
  char		buff[32];

  memset(buff, '\0', 32);
  x = (int)player->my_cell->x;
  y = my_modulo(((int)player->my_cell->y + 1), server->height);
  move_player(player, player->my_cell->players, (server->world[x][y]).players);
  player->my_cell = &(server->world[x][y]);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, x, y,
	  graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}

int		move_east(t_server *server, t_client* player)
{
  int		x;
  int		y;
  char		buff[32];

  memset(buff, '\0', 32);
  x = my_modulo(((int)player->my_cell->x + 1), (int)server->width);
  y = (int)player->my_cell->y;
  move_player(player, player->my_cell->players, (server->world[x][y]).players);
  player->my_cell = &(server->world[x][y]);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, x, y,
	  graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}

int		move_west(t_server *server, t_client* player)
{
  int		x;
  int		y;
  char		buff[32];

  memset(buff, '\0', 32);
  x = my_modulo(((int)player->my_cell->x - 1), (int)server->width);
  y = (int)player->my_cell->y;
  move_player(player, player->my_cell->players, (server->world[x][y]).players);
  player->my_cell = &(server->world[x][y]);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, x, y,
	  graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}
