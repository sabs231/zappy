/*
** handle_parameters1.c for src in /home/baezse_s/zappy/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Thu May 09 13:48:04 2013 Sergio Baez
** Last update Fri Jul 12 15:17:26 2013 fabien massaro
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"list.h"
#include	"my_functions.h"
#include	"parameter_structure.h"
#include	"server_error_functions.h"

int		parse_clients(t_server *params, int argc, char **argv, int offset)
{
  int		clients;

  (void)argc;
  if (str_is_nbr(argv[offset + 1]) != 0)
    return (parameters_error("client number [-c]"));
  clients = atoi(argv[offset + 1]);
  if (clients < 0)
    {
      fprintf(stderr, "the width sould be a positive number\n");
      return (-1);
    }
  params->num_clients = (unsigned int)clients;
  return (0);
}

int		parse_time(t_server *params, int argc, char **argv, int offset)
{
  int		time;

  (void)argc;
  if (str_is_nbr(argv[offset + 1]) != 0)
    return (parameters_error("time delay [-d]"));
  time = atoi(argv[offset + 1]);
  if (time < 0)
    {
      fprintf(stderr, "the width sould be a positive number\n");
      return (-1);
    }
  params->time_delay = (unsigned int) time;
  return (0);
}

int		test_parameters(t_server *params)
{
  if (params->port == 0)
    return (parameters_error("port value [-p]"));
  if (params->width == 0)
    return (parameters_error("width [-x]"));
  if (params->height == 0)
    return (parameters_error("height [-y]"));
  if (is_empty_list(params->teams))
    return (parameters_error("team names [-n]"));
  if (params->num_clients == 0)
    return (parameters_error("client number [-c]"));
  if (params->time_delay == 0)
    return (parameters_error("time delay [-t]"));
  return (0);
}
