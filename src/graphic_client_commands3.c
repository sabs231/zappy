/*
** graphic_client_commands3.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jul 08 15:09:46 2013 Sergio Baez
** Last update Fri Jul 12 15:10:32 2013 fabien massaro
*/

#include	<string.h>
#include	"graph_commands.h"
#include	"server_structure.h"
#include	"client_structure.h"
#include	"teams.h"
#include	"list.h"

extern int	g_incant[][NUM_MIN];

void		fill_inv_buff(char *buff, t_client *pl, int p_num)
{
  memset(buff, '\0', 32);
  sprintf(buff, "pin #%d %d %d %d %d %d %d %d %d %d\n", p_num, pl->my_cell->x,
	  pl->my_cell->y, pl->inventory[FOOD], pl->inventory[LINEMATE],
	  pl->inventory[DERAUMERE], pl->inventory[SIBUR], pl->inventory[MENDIANE],
	  pl->inventory[PHIRAS], pl->inventory[THYSTAME]);
}

int		send_graphic(char *buff, t_server *server, t_client *p)
{
  if (write_client(server, p, "elevation en cours\n", 19) == -1)
    return (-1);
  strncat(buff, "\n", 1);
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}

int		send_graph_inst(t_server *server, t_client *p, char *cmd)
{
  char		buff[128];
  char		temp[32];
  t_link	*current;
  int		need_players;
  int		nb_players;

  need_players = g_incant[p->level - 1][0];
  nb_players = 0;
  current = p->my_cell->players->first;
  if (strcmp(cmd, "incantation") != 0)
    return (0);
  sprintf(buff, "pic %d %d %d", p->my_cell->x, p->my_cell->y, p->level);
  while (current != NULL)
    {
      if (((t_client *)current->data)->level == p->level)
	{
	  sprintf(temp, " #%d", ((t_client *)current->data)->cs);
	  strncat(buff, temp, strlen(temp));
	  if (++nb_players >= need_players)
	    return (send_graphic(buff, server, p));
	}
      current = current->next;
    }
  return (send_graphic(buff, server, p));
}

int		update_map(t_server *server)
{
  char		buff[64];

  memset(buff, '\0', 64);
  if (send_graph_info(server, 0, &buff[0]) == -1)
    return (-1);
  return (0);
}
