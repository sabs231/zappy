/*
** extra_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Thu May 09 16:09:01 2013 Sergio Baez
** Last update Fri Jul 12 17:12:04 2013 fabien massaro
*/

#include	<string.h>
#include	"list.h"
#include	"teams.h"
#include	"my_functions.h"
#include	"server_structure.h"

int		str_is_nbr(char *str)
{
  int		i;

  i = 0;
  if (!str)
    return (1);
  while (str[i] != '\0')
    {
      if (str[i] > '9' || str[i] < '0')
	return (1);
      i++;
    }
  return (0);
}

void		free_server(t_server *server)
{
  t_link	*aux;

  if (server == NULL || server->teams == NULL)
    return ;
  aux = server->teams->first;
  while (aux != NULL)
    {
      free(((t_teams *)aux->data)->name);
      free((t_teams *)aux->data);
      aux = aux->next;
    }
  clear_list(&server->teams);
  free(server);
}

void		free_list(t_list **list)
{
  t_link	*aux;

  if ((*list) == NULL || (*list)->first == NULL)
    return ;
  aux = (*list)->first;
  while (aux != NULL)
    {
      free(((t_teams *)aux->data)->name);
      free(aux->data);
      aux = aux->next;
    }
}

void		clean_str(char *str)
{
  int		i;

  i = 0;
  while (str[i] && (str[i] != '\n' && str[i] != '\r'))
    {
      i++;
    }
  str[i] = '\0';
}

int		name_exist(t_list **teams, char *name)
{
  t_link	*tmp;

  if ((*teams) == NULL || (*teams)->first == NULL)
    return (0);
  tmp = (*teams)->first;
  while (tmp != NULL)
    {
      if (strcmp(((t_teams *)tmp->data)->name, name) == 0)
	{
	  fprintf(stderr, "The team %s exists, the team names must be different\n",
		  name);
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}
