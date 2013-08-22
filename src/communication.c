/*
** communication.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Fri Jun 07 16:38:48 2013 Sergio Baez
** Last update Sat Jul 13 15:33:29 2013 Sergio Baez
*/

#include	<errno.h>
#include	<string.h>
#include	"server_structure.h"
#include	"my_functions.h"
#include	"list.h"

int		write_client(t_server *ser, t_client *client, char *msg, int size)
{
  if (FD_ISSET(client->cs, &ser->fd_write))
    {
      if (send(client->cs, msg, size, MSG_NOSIGNAL) == -1)
	return (0);
    }
  return (0);
}

int		write_graphic_clients(t_server *server, char *msg, int size)
{
  t_link	*tmp;

  tmp = server->graphic_clients->first;
  while (tmp)
    {
      if (write_client(server, (t_client *)tmp->data, msg, size) == -1)
	return (-1);
      ((t_client *)tmp->data)->ready = 0;
      tmp = tmp->next;
    }
  return (0);
}

int		client_protocol(t_server *server, t_client *client, char *msg)
{
  int		ret;

  if (strcmp(msg, GRAPHIC) == 0)
    return (0);
  clean_str(msg);
  if ((ret = check_add_players(server, client, msg)) != 0)
    {
      if (ret == 2)
	{
	  if (graphic_protocol(server, client, msg) == -1)
	    return (-1);
	  return (0);
	}
    }
  return (0);
}

int		graphic_protocol(t_server *server, t_client *client, char *msg)
{
  if (strcmp(msg, GRAPHIC) != 0)
    {
      if (write_client(server, client, "team name or GRAPHIC\n",
		       strlen("team name or GRAPHIC\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to client %d: team name or GRAPHIC\n",
	      client->cs);
    }
  else
    {
      if (move_to_graph_clients(server, client) == -1)
	return (-1);
    }
  return (0);
}
