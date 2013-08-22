/*
** players_functions2.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jul 01 17:04:16 2013 Sergio Baez
** Last update Sat Jul 13 15:42:06 2013 Sergio Baez
*/

#include	<string.h>
#include	<time.h>
#include	"client_structure.h"
#include	"server_error_functions.h"
#include	"my_functions.h"
#include	"list.h"
#include	"teams.h"

int		put_player_info(t_teams *team, t_link *client)
{
  int		i;

  i = 0;
  ((t_client *)client->data)->client_function = read_for_player;
  ((t_client *)client->data)->my_team = team;
  ((t_client *)client->data)->level = 1;
  ((t_client *)client->data)->direction.front = rand() % DIR_NUM;
  while (i < REQ_NUM)
    {
      ((t_client *)client->data)->requests[i].called = 0;
      i++;
    }
  if (my_time(&(((t_client *)client->data)->life_time)) == (time_t) -1)
    return (-1);
  memset(((t_client *)client->data)->inventory, 0, NUM_MIN * sizeof(int));
  ((t_client *)client->data)->inventory[0] = 10;
  client->next = team->players->first;
  team->players->first = client;
  team->num_players--;
  return (0);
}

int		handle_life(t_server *server, t_client *player)
{
  time_t	actual_time;
  double	delay_time;
  char		buff[32];

  memset(buff, '\0', 32);
  delay_time = LIFE_NUM * server->time_delay;
  if (my_time(&actual_time) == (time_t) -1)
    return (-1);
  if (difftime(actual_time, player->life_time) >= delay_time)
    {
      (player->inventory[0])--;
      player->life_time = actual_time;
    }
  if (player->inventory[0] <= 0)
    {
      sprintf(buff, "pdi #%d\n", player->cs);
      if (write_graphic_clients(server, buff, strlen(buff)) == -1)
	return (-1);
      fprintf(stdout, "Message to all graph clients: pdi #%d\n", player->cs);
      if (close_connection(player,
			   ((t_teams *)player->my_team)->players) == -1)
	return (-1);
    }
  return (0);
}

int		check_life_players(t_server *server)
{
  t_link	*current_team;
  t_link	*current_player;
  t_client	*pl;

  if (!server->teams)
    return (0);
  current_team = server->teams->first;
  while (current_team)
    {
      current_player = ((t_teams *)current_team->data)->players->first;
      while (current_player)
	{
	  pl = (t_client *)current_player->data;
	  if (handle_life(server, pl) == -1)
	    return (-1);
	  current_player = current_player->next;
	}
      current_team = current_team->next;
    }
  return (0);
}

int		get_broadcast_msg(char *msg, t_client *player,
				  t_client *from, t_server *server)
{
  char		*buff;
  int		size;
  int		res;

  size = 12 + strlen(msg);
  if ((buff = my_malloc((size) * sizeof(char), MSG)) == NULL)
    return (0);
  memset(buff, 0, size);
  res = get_direction(player, from, server);
  if (res == -1)
    {
      free(buff);
      return (-1);
    }
  sprintf(buff, "message %d,%s", res, msg);
  if (write_client(server, player, buff, strlen(buff)) == -1)
    {
      free(buff);
      return (-1);
    }
  fprintf(stdout, "Message to player %d: %s\n", player->cs, buff);
  free(buff);
  return (0);
}
