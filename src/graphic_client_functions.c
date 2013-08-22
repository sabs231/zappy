/*
** graphic_client_functions.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Fri Jul 05 11:23:46 2013 Sergio Baez
** Last update Sat Jul 13 18:23:15 2013 Sergio Baez
*/

#include	<stdio.h>
#include	<string.h>
#include	"server_structure.h"
#include	"client_structure.h"
#include	"teams.h"
#include	"list.h"

int		send_graph_info(t_server *s, int id, char *buff)
{
  int		i;
  int		j;

  (void)id;
  i = 0;
  j = 0;
  while (i < (int)s->width)
    {
      while (j < (int)s->height)
	{
	  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", i, j,
		  cnt_min(&s->world[i][j], FOOD), cnt_min(&s->world[i][j], LINEMATE),
		  cnt_min(&s->world[i][j], DERAUMERE), cnt_min(&s->world[i][j], SIBUR),
		  cnt_min(&s->world[i][j], MENDIANE), cnt_min(&s->world[i][j], PHIRAS),
		  cnt_min(&s->world[i][j], THYSTAME));
	  if (write_graphic_clients(s, buff, strlen(buff)) == -1)
	    return (-1);
	  j++;
	}
      j = 0;
      i++;
    }
  return (0);
}

int		send_team_names(t_server *server, t_client *client, char *buff)
{
  t_link	*current_team;
  t_teams	*team;

  memset(buff, '\0', 32);
  current_team = server->teams->first;
  while (current_team)
    {
      team = (t_teams *)current_team->data;
      sprintf(buff, "tna %s\n", team->name);
      if (write_client(server, client, buff, strlen(buff)) == -1)
	return (-1);
      fprintf(stdout, "Msg to graph client %d: tna %s\n", client->cs, buff);
      current_team = current_team->next;
    }
  return (0);
}

int		insert_graph_client(t_server *server, t_link *client)
{
  char		buff[32];

  memset(buff, '\0', 32);
  ((t_client *)client->data)->my_cell = NULL;
  prepare_graph_commands((t_client *)client->data);
  ((t_client *)client->data)->client_function = read_for_graph_client;
  client->next = server->graphic_clients->first;
  server->graphic_clients->first = client;
  sprintf(buff, "msz %d %d\nsgt %f\n", server->width, server->height,
	  server->time_delay);
  if (write_client(server, (t_client *)client->data, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: msz %d %d\nsgt %f\n",
	  ((t_client *)client->data)->cs, server->width, server->height,
	  server->time_delay);
  memset(buff, '\0', 32);
  /*
  if (send_graph_info(server, ((t_client *)client->data)->cs, &buff[0]) == -1)
    return (-1);
  if (send_team_names(server, ((t_client *)client->data), &buff[0]) == -1)
    return (-1);
  if (send_players_info(server, &buff[0]) == -1)
    return (-1);
  if (send_egg_info(server, &buff[0]) == -1)
    return (-1);*/
  if (send_complete_info(server, (t_client *)client->data, &buff[0]) == -1)
    return (-1);
  ((t_client *)client->data)->ready = 0;
  return (0);
}

int		move_to_graph_clients(t_server *server, t_client *client)
{
  t_link	*prev;
  t_link	*tmp;

  prev = server->new_clients->first;
  tmp = server->new_clients->first->next;
  if ((t_client *)prev->data == client)
    {
      server->new_clients->first = tmp;
      return (insert_graph_client(server, prev));
    }
  while (tmp)
    {
      if ((t_client *)tmp->data == client)
	{
	  prev->next = tmp->next;
      return (insert_graph_client(server, tmp));
	}
      prev = prev->next;
      tmp = tmp->next;
    }
  fprintf(stderr, "Could not find the client\n");
  return (-1);
}

int		read_for_graph_client(t_server *server, t_client *client)
{
  char		buff[4096];
  int		r;

  if (!client->ready)
    return (ready_to_write(client));
  if ((r = recv(client->cs, buff, 4096, 0)) > 0)
    {
      buff[r] = '\0';
      if (check_graph_commands(server, client, buff) == -1)
	return (-1);
    }
  else if (r != 0)
    perror("read");
  else
    {
      if (close_connection(client, server->graphic_clients) == -1)
	return (-1);
      return (1);
    }
  return (0);
}
