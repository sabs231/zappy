/*
** server_main.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:05:43 2013 Sergio Baez
** Last update Sat Jul 13 15:42:19 2013 Sergio Baez
*/

#include	<signal.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>
#include	"list.h"
#include	"teams.h"
#include	"my_functions.h"
#include	"parameter_structure.h"
#include	"server_error_functions.h"

t_server	g_server;

void		sigint_handler(int dummy)
{
  (void)dummy;
  free_everything(&g_server);
  exit(0);
}

int		main(int argc, char **argv)
{
  srand(time(NULL));
  signal(SIGINT, sigint_handler);
  if (argc == 1)
    return (incorrect_param_number(argv));
  else
    {
      if (get_parameters(argc, argv, &g_server) == -1)
	return (-1);
      if (prepare_server(&g_server) == -1)
	return (-1);
    }
  return (0);
}

void		free_everything(t_server *server)
{
  free_commands(server);
  free_world(server);
  free_teams(server);
  clear_list(&server->new_clients);
  clear_list(&server->graphic_clients);
}
