/*
** end_game.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jul 01 17:04:16 2013 Sergio Baez
** Last update Sat Jul 13 15:28:40 2013 fabien massaro
*/

#include	"server_structure.h"
#include	"teams.h"

int		check_end_game(t_server *server, int max_lvl)
{
  t_link	*current_team;
  t_link	*current_player;
  t_client	*pl;

  current_team = server->teams->first;
  while (current_team)
    {
      current_player = ((t_teams *)current_team->data)->players->first;
      while (current_player)
	{
	  pl = (t_client *)current_player->data;
	  if (pl->level >= max_lvl)
	    return (-1);
	  current_player = current_player->next;
	}
      current_team = current_team->next;
    }
  return (0);
}
