/*
** check_commands.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 23:46:08 2013 Sergio Baez
** Last update Sat Jul 13 15:33:05 2013 Sergio Baez
*/

#include	<string.h>
#include	"teams.h"
#include	"commands.h"
#include	"my_functions.h"

int		put_request(t_server *server, t_client *player, char *word2, int i)
{
  int		j;

  j = 0;
  while (j < REQ_NUM)
    {
      if (player->requests[j].called == 0)
	{
	  player->requests[j].fc = server->commands[i].fc;
	  player->requests[j].player = player;
	  player->requests[j].arg = strdup(word2);
	  if (player->requests[j].arg == NULL)
	    player->requests[j].arg = word2;
	  player->requests[j].called = 1;
	  if (gettimeofday(&player->requests[j].call_time, NULL) == -1)
	    {
	      perror("time");
	      return (-1);
	    }
	  return (0);
	}
      j++;
    }
  return (0);
}

int		check_command(t_server *server, t_client *player, char *cmd)
{
  int		i;
  char		*word1;
  char		*word2;

  i = -1;
  word1 = strtok(cmd, " \t\n\r");
  if (word1 != NULL)
    {
      word2 = cmd + strlen(word1) + 1;
      while (++i < NUM_CMDS)
	{
	  if (strcmp(server->commands[i].cmd, word1) == 0)
	    {
	      if (send_graph_inst(server, player, server->commands[i].cmd) == -1)
		return (-1);
	      if (put_request(server, player, word2, i) == -1)
		return (-1);
	      return (0);
	    }
	}
      if (die(server, player) == -1)
	return (-1);
      return (1);
    }
  return (0);
}

double		get_time_delay(t_server *server, t_client *pl, int num_req)
{
  int		i;

  i = 0;
  while (i < NUM_CMDS)
    {
      if (server->commands[i].fc == pl->requests[num_req].fc)
	return (server->commands[i].delay / server->time_delay);
      i++;
    }
  return (0.0);
}

int			handle_request(t_server *server, t_client *pl)
{
  int			i;
  struct timeval	now;
  struct timeval	req_time;
  long int		diff_time;

  i = -1;
  while (++i < REQ_NUM)
    {
      if (pl->requests[i].called == 1)
	{
	  req_time = pl->requests[i].call_time;
	  if (gettimeofday(&now, NULL) == -1)
	    return (-1);
	  diff_time = ((now.tv_sec * 1000000 + now.tv_usec) -
		       (req_time.tv_sec * 1000000 + req_time.tv_usec));
	  if (diff_time >= (get_time_delay(server, pl, i) * 1000000))
	    {
	      if (pl->requests[i].fc(server, pl, pl->requests[i].arg) == -1)
		return (-1);
	      pl->requests[i].called = 0;
	      free(pl->requests[i].arg);
	    }
	}
    }
  return (0);
}

int		check_requests(t_server *server)
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
	  if (handle_request(server, pl) == -1)
	    return (-1);
	  current_player = current_player->next;
	}
      current_team = current_team->next;
    }
  return (0);
}
