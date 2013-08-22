/*
** graphic_client_functions3.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Sat Jul 13 17:51:05 2013 Sergio Baez
** Last update Sat Jul 13 18:23:46 2013 Sergio Baez
*/

#include	<stdio.h>
#include	<string.h>
#include	"server_structure.h"
#include	"client_structure.h"
#include	"teams.h"
#include	"list.h"

int             send_players_info(t_server *s, char *buff)
{
  t_link        *curr_team;
  t_link        *curr_pl;
  t_client      *pl;

  if (!s->teams)
    return (0);
  curr_team = s->teams->first;
  while (curr_team)
  {
    curr_pl = ((t_teams *)curr_team->data)->players->first;
    while (curr_pl)
    {
      pl = (t_client *)curr_pl->data;
      sprintf(buff, "pnw #%d %d %d %d %d %s\n", pl->cs, pl->my_cell->x,
          pl->my_cell->y, pl->direction.front,  pl->level,
          ((t_teams *)pl->my_team)->name);
      if (write_graphic_clients(s, buff, strlen(buff)) == -1)
        return (-1);
      curr_pl = curr_pl->next;
    }
    curr_team = curr_team->next;
  }
  return (0);
}

int             send_egg_info(t_server *s, char *buff)
{
  t_link        *curr_team;
  t_link        *curr_egg;
  t_egg         *egg;

  if (!s->teams)
    return (0);
  curr_team = s->teams->first;
  while (curr_team)
  {
    curr_egg = ((t_teams *)curr_team->data)->eggs->first;
    while (curr_egg)
    {
      egg = (t_egg *)curr_egg->data;
      sprintf(buff, "enw #%d #%d %d %d\n", egg->id, egg->pl_cs,
          egg->x, egg->y);
      if (write_graphic_clients(s, buff, strlen(buff)) == -1)
        return (-1);
      curr_egg = curr_egg->next;
    }
    curr_team = curr_team->next;
  }
  return (0);
}

int             send_complete_info(t_server *s, t_client *client, char *buff)
{
  if (send_graph_info(s, client->cs, &buff[0]) == -1)
    return (-1);
  if (send_team_names(s, client, &buff[0]) == -1)
    return (-1);
  if (send_players_info(s, &buff[0]) == -1)
    return (-1);
  if (send_egg_info(s, &buff[0]) == -1)
    return (-1);
  return (0);
}
