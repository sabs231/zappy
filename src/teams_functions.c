/*
** teams_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Thu May 09 11:40:11 2013 Sergio Baez
** Last update Fri Jul 12 16:50:55 2013 fabien massaro
*/

#include	<stdio.h>
#include	<string.h>
#include	"list.h"
#include	"teams.h"
#include	"my_functions.h"
#include	"server_error_functions.h"

int		add_team_name(t_list **teams, char *name, int id)
{
  t_teams	*a_team;

  if (name_exist(teams, name))
    {
      free_list(teams);
      return (-1);
    }
  if ((a_team = (t_teams *)my_malloc(sizeof(t_teams), NEW_TEAM)) == NULL)
    return (-1);
  if ((a_team->name = (char *)my_malloc(strlen(name) + 1, TEAM_NAME)) == NULL)
    return (-1);
  a_team->id = id;
  a_team->name = strcpy(a_team->name, name);
  if (insert_in_list(teams, a_team) == -1)
    return (-1);
  return (0);
}

int		check_add_players(t_server *server, t_client *client, char *name)
{
  t_link	*tmp;

  if (server->teams == NULL || server->teams->first == NULL)
    return (-1);
  tmp = server->teams->first;
  while (tmp)
    {
      if (strcmp(((t_teams *)tmp->data)->name, name) == 0)
	{
	  if (((t_teams *)tmp->data)->num_players <= 0)
	    {
	      if (close_connection(client, server->new_clients) == -1)
		return (-1);
	      return (-1);
	    }
	  if (move_to_players(((t_teams *)tmp->data), server->new_clients,
			      client, server) == -1)
	    return (-1);
	  return (0);
	}
      tmp = tmp->next;
    }
  return (2);
}

void		free_teams(t_server *server)
{
  t_link	*tmp;

  tmp = server->teams->first;
  while (tmp)
    {
      clear_list(&((t_teams *)tmp->data)->players);
      free(((t_teams *)tmp->data)->name);
      tmp = tmp->next;
    }
  clear_list(&server->teams);
  free(server->teams);
}
