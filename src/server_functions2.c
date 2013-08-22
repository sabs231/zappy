/*
** server_functions2.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jul 09 15:02:50 2013 Sergio Baez
** Last update Fri Jul 12 16:37:54 2013 fabien massaro
*/

#include	<string.h>
#include	"server_structure.h"
#include	"cell_structure.h"
#include	"my_functions.h"
#include	"commands.h"
#include	"list.h"
#include	"teams.h"

void		free_commands(t_server *server)
{
  int		i;

  i = 0;
  while (i < NUM_CMDS)
    {
      free(server->commands[i].cmd);
      i++;
    }
}

int		prepare_server(t_server *server)
{
  memset(server->fd_type, FD_FREE, MAX_FD);
  if (prepare_commands(server) == -1)
    return (-1);
  init_minerals(server);
  if ((init_world(server) == -1) || (init_clients(server) == -1) ||
      (prepare_socket(server) == -1) || (generate_minerals(server) == -1))
    return (-1);
  if (start_main_cicle(server) == -1)
    return (-1);
  return (0);
}
