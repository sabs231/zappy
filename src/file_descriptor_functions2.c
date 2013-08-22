/*
** file_descriptor_functions2.c for src in /home/baezse_s/zappy_julien/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Thu Jul 11 14:47:19 2013 Sergio Baez
** Last update Sat Jul 13 15:33:42 2013 Sergio Baez
*/

#include	"server_structure.h"
#include	"my_functions.h"
#include	"teams.h"
#include	"list.h"

void	set_fds(t_server *server, int fd)
{
  FD_SET(fd, &server->fd_read);
  FD_SET(fd, &server->fd_write);
}

int             launch_player_func(t_client *player, t_server *ser)
{
  if (player->client_function(ser, player) == -1)
    return (-1);
  return (0);
}

void            set_fd_clients(t_server *server, int *fd_max)
{
  t_link        *curr_client;
  t_client      *client;

  if (!server->new_clients)
    return ;
  curr_client = server->new_clients->first;
  while (curr_client)
  {
    client = (t_client *)curr_client->data;
    set_fds(server, client->cs);
    if (client->cs > *fd_max)
      *fd_max = client->cs;
    curr_client = curr_client->next;
  }
}
