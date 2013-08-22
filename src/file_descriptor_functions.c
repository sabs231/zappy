/*
** file_descriptor_functions.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 18:36:19 2013 Sergio Baez
** Last update Sat Jul 13 15:48:05 2013 Sergio Baez
*/

#include	"server_structure.h"
#include	"my_functions.h"
#include	"teams.h"
#include	"list.h"

void            set_fd_players(t_server *server, int *fd_max)
{
  t_link        *curr_client;
  t_link        *curr_team;
  t_client      *player;

  if (!server->teams)
    return ;
  curr_team = server->teams->first;
  while (curr_team)
  {
    curr_client = ((t_teams *)curr_team->data)->players->first;
    while (curr_client)
    {
      player = (t_client *)curr_client->data;
      set_fds(server, player->cs);
      if (player->cs > *fd_max)
        *fd_max = player->cs;
      curr_client = curr_client->next;
    }
    curr_team = curr_team->next;
  }
}

int		check_clients_fd(t_server *ser)
{
  int		ret;
  t_link	*tmp;
  t_client	*client;

  ret = 0;
  if (!ser->new_clients)
    return (0);
  tmp = ser->new_clients->first;
  while (tmp)
    {
      client = (t_client *)tmp->data;
      if (FD_ISSET(client->cs, &ser->fd_read))
	{
	  if ((ret = client->client_function(ser, client)) == -1)
	    return (-1);
	  if (ret == 1)
	    return (0);
	}
      tmp = tmp->next;
    }
  return (0);
}

int		check_players_fd(t_server *ser)
{
  t_link        *current_team;
  t_link        *current_player;

  if (!ser->teams)
    return (0);
  current_team = ser->teams->first;
  while (current_team)
  {
    current_player = ((t_teams *)current_team->data)->players->first;
    while (current_player)
    {
      if (FD_ISSET(((t_client *)current_player->data)->cs, &ser->fd_read))
        return (launch_player_func((t_client *)current_player->data, ser));
      current_player = current_player->next;
    }
    current_team = current_team->next;
  }
  return (0);
}

void		set_fd_graph_clients(t_server *server, int *fd_max)
{
  t_link	*current_client;

  if (!server->graphic_clients)
    return ;
  current_client = server->graphic_clients->first;
  while (current_client != NULL)
  {
    set_fds(server, ((t_client *)current_client->data)->cs);
    if (((t_client *)current_client->data)->cs > *fd_max)
      *fd_max = ((t_client *)current_client->data)->cs;
    current_client = current_client->next;
  }
}

int		check_graph_clients_fd(t_server *server)
{
  int		ret;
  t_link	*tmp;
  t_client	*client;

  ret = 0;
  if (!server->graphic_clients)
    return (0);
  tmp = server->graphic_clients->first;
  while (tmp)
  {
    client = (t_client *)tmp->data;
    if (FD_ISSET(client->cs, &server->fd_read))
    {
      if ((ret = client->client_function(server, client)) == -1)
        return (-1);
      if (ret == 1)
        return (0);
    }
    tmp = tmp->next;
  }
  return (0);
}
