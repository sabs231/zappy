/*
** players_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 14:22:40 2013 Sergio Baez
** Last update Fri Jul 12 16:36:05 2013 fabien massaro
*/

#include	<string.h>
#include	<stdio.h>
#include	"client_structure.h"
#include	"commands.h"
#include	"list.h"
#include	"teams.h"

int		move_to_players(t_teams *team, t_list *new_clients,
				t_client *client, t_server *s)
{
  t_link	*prev;
  t_link	*tmp;

  prev = new_clients->first;
  tmp = new_clients->first->next;
  if ((t_client *)prev->data == client)
    {
      new_clients->first = tmp;
      return (insert_player(team, prev, s));
    }
  while (tmp)
    {
      if ((t_client *)tmp->data == client)
	{
	  prev->next = tmp->next;
	  return (insert_player(team, tmp, s));
	}
      prev = prev->next;
      tmp = tmp->next;
    }
  fprintf(stderr, "Could not find the client\n");
  return (-1);
}

int		send_info(t_teams *team, t_link *client, t_server *server)
{
  char		msg[32];
  t_client	*cl;

  cl = (t_client *)client->data;
  sprintf(msg, "%d\n", team->num_players);
  if (write_client(server, cl, msg, strlen(msg)) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", ((t_client *)client->data)->cs,
	  msg);
  memset(msg, '\0', 32);
  sprintf(msg, "%d %d\n", server->width, server->height);
  if (write_client(server, cl, msg, strlen(msg)) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", ((t_client *)client->data)->cs,
	  msg);
  memset(msg, '\0', 32);
  sprintf(msg, "pnw #%d %d %d %d %d %s\n", cl->cs, cl->my_cell->x,
	  cl->my_cell->y, graph_directions(cl->direction.front),
	  cl->level, ((t_teams *)cl->my_team)->name);
  if (write_graphic_clients(server, msg, strlen(msg)) == -1)
    return (-1);
  fprintf(stdout, "Message to all graph clients: %s\n", msg);
  return (0);
}

int		init_player_data(t_teams *team, t_link *client, t_server *server)
{
  t_link	*client_copy;
  u_int		x;
  u_int		y;

  x = rand() % server->width;
  y = rand() % server->height;
  if (check_for_egg(server, team, &x, &y) == -1)
    return (-1);
  ((t_client *)client->data)->my_cell = &server->world[x][y];
  if (put_player_info(team, client) == -1)
    return (-1);
  if ((client_copy = new_link(client->data)) == NULL)
    return (-1);
  client_copy->next = (server->world[x][y].players->first);
  (server->world[x][y]).players->first = client_copy;
  return (send_info(team, client, server));
}

int		insert_player(t_teams *team, t_link *client, t_server *server)
{
  if (team == NULL)
    {
      fprintf(stderr, "The team list is empty\n");
      return (-1);
    }
  if (init_player_data(team, client, server) == -1)
    return (-1);
  return (0);
}

int		read_for_player(t_server *server, t_client *client)
{
  char		buff[4096];
  int		r;

  memset(buff, '\0', 4096);
  if ((r = recv(client->cs, buff, 4096, 0)) > 0)
    {
      buff[r] = '\0';
      fprintf(stdout, "Received msg from player %d: %s\n", client->cs, buff);
      if ((r = check_command(server, client, buff)) == -1)
	return (-1);
      if (r == 1)
	return (1);
    }
  else if (r != 0)
    perror("read");
  else
    return (die(server, client));
  return (0);
}
