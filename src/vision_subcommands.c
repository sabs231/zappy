/*
** vision_subcommands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 18 13:02:14 2013 Sergio Baez
** Last update Fri Jul 12 16:55:04 2013 fabien massaro
*/

#include	<string.h>
#include	"list.h"
#include	"commands.h"
#include	"my_functions.h"
#include	"get_direction.h"
#include	"server_structure.h"

t_minerals	g_min[] =
{
  {FOOD, "nourriture"},
  {LINEMATE, "linemate"},
  {DERAUMERE, "deraumere"},
  {SIBUR, "sibur"},
  {MENDIANE, "mendiane"},
  {PHIRAS, "phiras"},
  {THYSTAME, "thystame"},
  {99, ""}
};

void		show_cell_content(t_server *ser, t_client *pl, int i, int j)
{
  t_link	*tmp;

  tmp = (ser->world[i][j]).players->first;
  while (tmp)
    {
      if (((t_client *)tmp->data)->cs != pl->cs)
	{
	  if (strlen(ser->msg) > 1)
	    strcat(ser->msg, " ");
	  strcat(ser->msg, "player");
	}
      tmp = tmp->next;
    }
  tmp = (ser->world[i][j]).minerals->first;
  while (tmp)
    {
      if (strlen(ser->msg) > 1)
	strcat(ser->msg, " ");
      strcat(ser->msg, g_min[(*(t_mineral *)tmp->data)].name);
      tmp = tmp->next;
    }
}

int		view_north(t_server *server, t_client *player)
{
  t_counters	curr;

  curr.j = 0;
  memset(server->msg, '\0', 4096);
  strcat(server->msg, "{");
  while ((int)curr.j < (player->level + 1))
    {
      curr.i = player->my_cell->x - curr.j;
      while ((int)curr.i <= (int)(player->my_cell->x + curr.j))
	{
	  curr.save_i = curr.i;
	  curr.save_i = my_modulo(curr.save_i, server->width);
	  curr.save_j = my_modulo((player->my_cell->y - curr.j), server->height);
	  if (curr.j != 0)
	    strcat(server->msg, ",");
	  show_cell_content(server, player, curr.save_i, curr.save_j);
	  curr.i++;
	}
      curr.j++;
    }
  strcat(server->msg, "}\n");
  if (write_client(server, player, server->msg, 4096) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, server->msg);
  return (0);
}

int		view_south(t_server *server, t_client *player)
{
  t_counters	curr;

  curr.j = 0;
  memset(server->msg, '\0', 4096);
  strcat(server->msg, "{");
  while ((int)curr.j < (player->level + 1))
    {
      curr.i = player->my_cell->x + curr.j;
      while ((int)curr.i >= (int)(player->my_cell->x - curr.j))
	{
	  curr.save_i = curr.i;
	  curr.save_i = my_modulo(curr.save_i, server->width);
	  curr.save_j = my_modulo((player->my_cell->y + curr.j), server->height);
	  if (curr.j != 0)
	    strcat(server->msg, ",");
	  show_cell_content(server, player, curr.save_i, curr.save_j);
	  curr.i--;
	}
      curr.j++;
    }
  strcat(server->msg, "}\n");
  if (write_client(server, player, server->msg, 4096) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, server->msg);
  return (0);
}

int		view_east(t_server *server, t_client *player)
{
  t_counters	curr;

  curr.j = 0;
  memset(server->msg, '\0', 4096);
  strcat(server->msg, "{");
  while ((int)curr.j < (player->level + 1))
    {
      curr.i = player->my_cell->y - curr.j;
      while ((int)curr.i <= (int)(player->my_cell->y + curr.j))
	{
	  curr.save_i = curr.i;
	  curr.save_i = my_modulo(curr.save_i, server->height);
	  curr.save_j = my_modulo((player->my_cell->x + curr.j), server->width);
	  if (curr.j != 0)
	    strcat(server->msg, ",");
	  show_cell_content(server, player, curr.save_j, curr.save_i);
	  curr.i++;
	}
      curr.j++;
    }
  strcat(server->msg, "}\n");
  if (write_client(server, player, server->msg, 4096) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, server->msg);
  return (0);
}

int		view_west(t_server *server, t_client *player)
{
  t_counters	curr;

  curr.j = 0;
  memset(server->msg, '\0', 4096);
  strcat(server->msg, "{");
  while ((int)curr.j < (player->level + 1))
    {
      curr.i = player->my_cell->y + curr.j;
      while ((int)curr.i >= (int)(player->my_cell->y - curr.j))
	{
	  curr.save_i = curr.i;
	  curr.save_i = my_modulo(curr.save_i, server->height);
	  curr.save_j = my_modulo((player->my_cell->x - curr.j), server->width);
	  if (curr.j != 0)
	    strcat(server->msg, ",");
	  show_cell_content(server, player, curr.save_j, curr.save_i);
	  curr.i--;
	}
      curr.j++;
    }
  strcat(server->msg, "}\n");
  if (write_client(server, player, server->msg, 4096) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, server->msg);
  return (0);
}
