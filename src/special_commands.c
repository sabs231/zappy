/*
** special_commands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 11 00:01:51 2013 Sergio Baez
** Last update Fri Jul 12 16:47:29 2013 fabien massaro
*/

#include	<string.h>
#include	<stdio.h>
#include	"commands.h"
#include	"my_functions.h"
#include	"server_error_functions.h"
#include	"teams.h"

int		do_the_broadcast(t_server *server, t_client *player, char *w)
{
  t_link	*current_team;
  t_link	*current_player;

  current_team = server->teams->first;
  while (current_team)
    {
      current_player = ((t_teams *)current_team->data)->players->first;
      while (current_player)
	{
	  if (((t_client *)(current_player->data)) != player)
	    {
	      if (get_broadcast_msg(w, ((t_client *)(current_player->data)),
				    player, server) == -1)
		return (-1);
	    }
	  current_player = current_player->next;
	}
      current_team = current_team->next;
    }
  return (0);
}

int		broadcast(t_server *server, t_client *player, char *word)
{
  char		*graph_buff;
  int		size;

  size = 9 + strlen(word);
  if ((graph_buff = my_malloc(size, MSG)) == NULL)
    return (0);
  memset(graph_buff, 0, size);
  if (word != NULL)
    {
      if (do_the_broadcast(server, player, word) == -1)
	return (-1);
    }
  clean_str(word);
  sprintf(graph_buff, "pbc #%d %s\n", player->cs, word);
  if (write_graphic_clients(server, graph_buff, strlen(graph_buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to all graph clients: %s\n", graph_buff);
  if (write_client(server, player, "ok\n", 3) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [broadcast]=>ok\n", player->cs);
  return (0);
}

int		player_fork(t_server *server, t_client * player, char *word)
{
  t_egg		*egg;
  char		buff[32];

  (void)word;
  sprintf(buff, "pfk #%d\n", player->cs);
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  if ((egg = (t_egg *)my_malloc(sizeof(t_egg), EGG)) == NULL)
    {
      write_client(server, player, "ko\n", strlen("ko\n"));
      return (0);
    }
  get_my_egg(egg, server, player);
  if (insert_in_list(&((t_teams *)player->my_team)->eggs, egg) == -1)
    {
      write_client(server, player, "ko\n", strlen("ko\n"));
      return (-1);
    }
  ((t_teams *)player->my_team)->num_players++;
  if (write_client(server, player, "ok\n", strlen("ok\n")) == -1)
    return (0);
  sprintf(buff, "enw #%d #%d %d %d\n", egg->id, player->cs, egg->x, egg->y);
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}

int		die(t_server *server, t_client *player)
{
  char		buff[32];

  memset(buff, 0, 32);
  sprintf(buff, "pdi #%d\n", player->cs);
  if (write_graphic_clients(server, buff, strlen(buff)) == -1)
    return (-1);
  if (close_connection(player, ((t_teams *)player->my_team)->players) == -1)
    return (-1);
  return (1);
}
