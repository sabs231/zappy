/*
** world_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed Jun 12 14:15:19 2013 Sergio Baez
** Last update Fri Jul 12 16:55:52 2013 fabien massaro
*/

#include	<stdlib.h>
#include	"server_structure.h"
#include	"list.h"

void		free_world(t_server *server)
{
  u_int		i;
  u_int		j;

  i = 0;
  j = 0;
  while (i < server->width)
    {
      while (j < server->height)
	{
	  clear_list(&server->world[i][j].players);
	  clear_list(&server->world[i][j].minerals);
	  j++;
	}
      j = 0;
      free(server->world[i]);
      i++;
    }
  free(server->world);
}

int		init_cells(t_server *server)
{
  u_int		i;
  u_int		j;

  i = 0;
  j = 0;
  while (i < server->width)
    {
      while (j < server->height)
	{
	  if ((server->world[i][j].players = new_list()) == NULL)
	    return (-1);
	  if ((server->world[i][j].minerals = new_list()) == NULL)
	    return (-1);
	  server->world[i][j].x = i;
	  server->world[i][j].y = j;
	  j++;
	}
      i++;
      j = 0;
    }
  return (0);
}

