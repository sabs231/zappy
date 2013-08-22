/*
** move_commands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 23:52:29 2013 Sergio Baez
** Last update Sat Jul 13 14:35:53 2013 fabien massaro
*/

#include	<stdio.h>
#include	<string.h>
#include	"commands.h"
#include	"get_direction.h"

int			advance(t_server* server, t_client* pl, char *word)
{
  int			i;
  static t_direction	move_directions[] =
    {
      {NORTH, &move_north},
      {SOUTH, &move_south},
      {EAST, &move_east},
      {WEST, &move_west},
      {99, NULL}
    };

  (void)word;
  i = 0;
  while (move_directions[i].dir != 99)
    {
      if (pl->direction.front == move_directions[i].dir)
	{
	  if (move_directions[i].function(server, pl) == -1)
	    return (-1);
	  if (write_client(server, pl, "ok\n", strlen("ok\n")) == -1)
	    return (-1);
	  fprintf(stdout, "Message to player %d: [avance]=>ok\n", pl->cs);
	}
      i++;
    }
  return (0);
}

int		rigth(t_server *server, t_client *player, char *word)
{
  char		buff[32];

  memset(buff, '\0', 32);
  (void)word;
  player->direction.front = ((player->direction.front + 1) % DIR_NUM);
  if (write_client(server, player, "ok\n", strlen("ok\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [droite]=>ok\n", player->cs);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, player->my_cell->x,
      player->my_cell->y, graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", player->cs, buff);
  return (0);
}

int		left(t_server *server, t_client *player, char *word)
{
  char		buff[32];

  memset(buff, '\0', 32);
  (void)word;
  player->direction.front = ((player->direction.front - 1) % DIR_NUM);
  if (write_client(server, player, "ok\n", strlen("ok\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [gauche]=>ok\n", player->cs);
  sprintf(buff, "ppo #%d %d %d %d\n", player->cs, player->my_cell->x,
	  player->my_cell->y, graph_directions(player->direction.front));
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", player->cs, buff);
  return (0);
}

int		expel_aux(t_server *server, t_client *current, t_client *player)
{
  char		buff[32];

  if (current != player)
    {
      if (player->direction.front == NORTH)
	move_north(server, current);
      else if (player->direction.front == EAST)
	move_east(server, current);
      else if (player->direction.front == WEST)
	move_west(server, current);
      else
	move_south(server, current);
      sprintf(buff, "move: %d\n", get_direction(current, player, server));
      if (write_client(server, current, buff, strlen(buff)) == -1)
	{
	  write_client(server, player, "ko\n", strlen("ko\n"));
	  return (-1);
	  fprintf(stdout, "Message to player %d: [expel]=>ko\n", player->cs);
	}
    }
  return (0);
}

int		expel(t_server *server, t_client *pl, char *word)
{
  t_link	*curr;
  t_link	*tmp;
  t_client	*curr_pl;
  char		buff[32];

  (void)word;
  sprintf(buff, "pex #%d\n", pl->cs);
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    {
      write_client(server, pl, "ko\n", strlen("ko\n"));
      return (-1);
    }
  curr = pl->my_cell->players->first;
  while (curr != NULL)
    {
      curr_pl = ((t_client *)curr->data);
      tmp = curr->next;
      if (expel_aux(server, curr_pl, pl) == -1)
	return (-1);
      curr = tmp;
    }
  if (write_client(server, pl, "ok\n", strlen("ok\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [expel]=>ok\n", pl->cs);
  return (0);
}
