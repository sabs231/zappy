/*
** sockets_functions.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 04 15:00:43 2013 Sergio Baez
** Last update Sat Jul 13 15:42:32 2013 Sergio Baez
*/

#include	<errno.h>
#include	<signal.h>
#include	"server_structure.h"
#include	"my_functions.h"
#include	"list.h"

void		put_server_info(struct sockaddr_in *sin, t_server *ser)
{
  sin->sin_family = AF_INET;
  sin->sin_port = htons(ser->port);
  sin->sin_addr.s_addr = INADDR_ANY;
  ser->tv.tv_sec = SELECT_WAIT;
  ser->tv.tv_usec = 0;
}

int		prepare_socket(t_server *server)
{
  t_sock	sin;
  int		i;

  if ((server->sfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      return (-1);
    }
  put_server_info(&sin, server);
  i = 1;
  setsockopt(server->sfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
  if (bind(server->sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      perror("bind");
      return (-1);
    }
  if (listen(server->sfd, server->num_clients) == -1)
    {
      perror("listen");
      return (-1);
    }
  server->serv_function = add_client;
  server->fd_type[server->sfd] = FD_SERV;
  return (0);
}

int		wait_for_select(t_server *server)
{
  int		fd_max;

  fd_max = server->sfd;
  FD_ZERO(&server->fd_read);
  FD_ZERO(&server->fd_write);
  FD_SET(server->sfd, &server->fd_read);
  FD_SET(server->sfd, &server->fd_write);
  set_fd_clients(server, &fd_max);
  set_fd_players(server, &fd_max);
  set_fd_graph_clients(server, &fd_max);
  if (select(fd_max + 1, &server->fd_read, &server->fd_write,
	     NULL, &(server->tv)) == -1)
    {
      perror("select");
      return (-1);
    }
  return (0);
}

int		check_fd(t_server *ser)
{
  if (FD_ISSET(ser->sfd, &ser->fd_read))
    {
      if (ser->serv_function(ser, ser->sfd) == -1)
	return (-1);
    }
  else
    {
      if (check_players_fd(ser) == -1)
	return (-1);
      if (check_clients_fd(ser) == -1)
	return (-1);
      if (check_graph_clients_fd(ser) == -1)
	return (-1);
    }
  return (0);
}
