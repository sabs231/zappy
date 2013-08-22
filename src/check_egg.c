/*
** check_egg.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 14:22:40 2013 Sergio Baez
** Last update Sat Jul 13 18:16:39 2013 Sergio Baez
*/

#include	<string.h>
#include	"teams.h"
#include	"server_structure.h"

static int	test_id(t_server *server, int id)
{
  t_link	*current_team;
  t_link	*current_egg;

  current_team = server->teams->first;
  while (current_team)
    {
      current_egg = ((t_teams *)current_team->data)->eggs->first;
      while (current_egg)
	{
	  if (((t_egg *)current_egg->data)->id == id)
	    return (1);
	  current_egg = current_egg->next;
	}
      current_team = current_team->next;
    }
  return (0);
}

int		get_unique_id(t_server *server)
{
  int		unique;

  unique = rand();
  while (test_id(server, unique) != 0)
    unique = rand();
  return (unique);
}

void		get_my_egg(t_egg *egg, t_server *server, t_client *player)
{
  egg->id = get_unique_id(server);
  egg->x = player->my_cell->x;
  egg->y = player->my_cell->y;
  egg->pl_cs = player->cs;
}

int		check_for_egg(t_server *server, t_teams *team,
		      u_int *x, u_int *y)
{
  t_egg		*egg;
  char		buff[32];

  if (!(team->eggs == NULL || team->eggs->first == NULL))
    {
      egg = (t_egg *)(team->eggs->first->data);
      memset(buff, 0, 32);
      sprintf(buff, "eht #%d\nebo #%d\n", egg->id, egg->id);
      if (write_graphic_clients(server, buff, strlen(buff)) == -1)
	return (-1);
      *x = egg->x;
      *y = egg->y;
      team->eggs->first = team->eggs->first->next;
      free(egg);
    }
  return (0);
}
