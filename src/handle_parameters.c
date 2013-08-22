/*
** handle_parameters.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:41:05 2013 Sergio Baez
** Last update Fri Jul 12 15:19:26 2013 fabien massaro
*/

#include	<string.h>
#include	<stdio.h>
#include	"teams.h"
#include	"my_functions.h"
#include	"parameter_structure.h"
#include	"server_structure.h"
#include	"server_error_functions.h"

t_cmd		g_cmd[] =
{
  {"-p", &parse_port},
  {"-x", &parse_width},
  {"-y", &parse_height},
  {"-n", &parse_teams},
  {"-c", &parse_clients},
  {"-t", &parse_time},
  {NULL, NULL}
};

int		get_parameters(int c, char **v, t_server *p)
{
  int		i;
  int		j;

  i = 1;
  j = 0;
  while (i < c)
    {
      while (g_cmd[j].cmd != NULL)
	{
	  if ((strcmp(g_cmd[j].cmd, v[i]) == 0) && (g_cmd[j].fc(p, c, v, i) == -1))
	    return (-1);
	  j++;
	}
      j = 0;
      i++;
    }
  if (test_parameters(p) == -1)
    return (-1);
  return (0);
}

int		parse_port(t_server *params, int argc, char **argv, int offset)
{
  u_int		port;

  (void)argc;
  if (str_is_nbr(argv[offset + 1]) != 0)
    return (parameters_error("port value [-p]"));
  port = atoi(argv[offset + 1]);
  if ((port < 1200) || (port > 65553))
    {
      fprintf(stderr, "port shold be between 1200 and 65535\n");
      return (-1);
    }
  params->port = port;
  return (0);
}

int		parse_width(t_server *params, int argc, char **argv, int offset)
{
  int		width;

  (void)argc;
  if (str_is_nbr(argv[offset + 1]) != 0)
    return (parameters_error("width [-x]"));
  width = atoi(argv[offset + 1]);
  if (width < 0)
    {
      fprintf(stderr, "the width sould be a positive number\n");
      return (-1);
    }
  params->width = (unsigned int) width;
  return (0);
}

int		parse_height(t_server *params, int argc, char **argv, int offset)
{
  int		height;

  (void)argc;
  if (str_is_nbr(argv[offset + 1]) != 0)
    return (parameters_error("height [-y]"));
  height = atoi(argv[offset + 1]);
  if (height < 0)
    {
      fprintf(stderr, "the height sould be a positive number\n");
      return (-1);
    }
  params->height = (unsigned int) height;
  return (0);
}

int		parse_teams(t_server *params, int argc, char **argv, int offset)
{
  int		i;
  int		id;
  t_list	*teams;

  if ((teams = new_list()) == NULL)
    {
      fprintf(stderr, "Could not allocate memory for the teams\n");
      return (-1);
    }
  i = offset + 1;
  id = 0;
  while (i < argc)
    {
      if (strchr(argv[i], '-') != NULL)
	i = argc;
      else if (add_team_name(&teams, argv[i], id) == -1)
	{
	  clear_list(&teams);
	  return (-1);
	}
      i++;
      id++;
    }
  params->teams = teams;
  return (0);
}
