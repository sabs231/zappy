/*
** graphic_client_commands2.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Sat Jul 06 14:45:45 2013 Sergio Baez
** Last update Fri Jul 12 15:09:13 2013 fabien massaro
*/

#include	<string.h>
#include	"graph_commands.h"
#include	"server_structure.h"
#include	"client_structure.h"
#include	"teams.h"
#include	"list.h"

int		player_level(t_server *server, t_client *client, char *arg)
{
  char		buff[32];
  int		p_num;
  t_client	*pl;

  if (strlen(arg) <= 0)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  p_num = atoi(strtok(arg, "#"));
  if ((pl = get_player(server, p_num)) == NULL)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  memset(buff, '\0', 32);
  sprintf(buff, "plv #%d %d\n", p_num, pl->level);
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

int		player_inventory(t_server *server, t_client *client, char *arg)
{
  char		buff[32];
  int		p_num;
  t_client	*pl;

  if (strlen(arg) <= 0)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  p_num = atoi(strtok(arg, "#"));
  if ((pl = get_player(server, p_num)) == NULL)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  fill_inv_buff(&buff[0], pl, p_num);
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

int		time_unit(t_server *server, t_client *client, char *arg)
{
  char		buff[32];

  memset(buff, '\0', 32);
  sprintf(buff, "sgt %f\n", server->time_delay);
  (void)arg;
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

int		set_time_unit(t_server *server, t_client *client, char *arg)
{
  char		buff[32];
  int		time;

  memset(buff, '\0', 32);
  if (strlen(arg) <= 0)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  time = atoi(strtok(arg, " \t\n\r"));
  if (time <= 0)
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  server->time_delay = (double)time;
  sprintf(buff, "sgt %f\n", server->time_delay);
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

t_client	*get_player(t_server *server, int p_num)
{
  t_link	*current_team;
  t_link	*current_player;

  current_team = server->teams->first;
  while (current_team)
    {
      current_player = ((t_teams *)current_team->data)->players->first;
      while (current_player)
	{
	  if (((t_client *)current_player->data)->cs == p_num)
	    return ((t_client *)current_player->data);
	  current_player = current_player->next;
	}
      current_team = current_team->next;
    }
  return (NULL);
}
