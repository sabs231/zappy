/*
** client_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 04 18:30:20 2013 Sergio Baez
** Last update Fri Jul 12 17:11:16 2013 fabien massaro
*/

#include	"client_structure.h"
#include	"server_structure.h"
#include	"my_functions.h"
#include	"teams.h"
#include	"list.h"

int		init_clients(t_server *ser)
{
  t_link	*tmp;

  tmp = NULL;
  if (ser->teams)
    tmp = ser->teams->first;
  if ((ser->new_clients = new_list()) == NULL)
    return (-1);
  if ((ser->graphic_clients = new_list()) == NULL)
    return (-1);
  while (tmp)
    {
      ((t_teams *)tmp->data)->num_players = ser->num_clients;
      if ((((t_teams *)tmp->data)->players = new_list()) == NULL)
	return (-1);
      if ((((t_teams *)tmp->data)->eggs = new_list()) == NULL)
	return (-1);
      tmp = tmp->next;
    }
  return (0);
}

int		read_for_client(t_server *server, t_client *client)
{
  char		buff[4096];
  int		r;

  if ((r = recv(client->cs, buff, 4096, 0)) > 0)
    {
      buff[r] = '\0';
      fprintf(stdout, "Receive message from client %d: %s", client->cs, buff);
      if (client_protocol(server, client, buff) == -1)
	return (-1);
    }
  else if (r != 0)
    perror("read");
  else
    {
      if (close_connection(client, server->new_clients) == -1)
	return (-1);
      return (1);
    }
  return (0);
}

int		close_connection(t_client *client, t_list *list)
{
  if (close(client->cs) == -1)
    {
      perror("close");
      return (-1);
    }
  if (client->my_team != NULL)
    ((t_teams *)client->my_team)->num_players++;
  if (delete_client(list, client) == 1)
    {
      fprintf(stderr, "The client inside teams list could no be found\n");
      return (-1);
    }
  if (client->my_cell != NULL &&
	delete_client(client->my_cell->players, client) == -1)
    {
      fprintf(stderr, "Client inside cell players list could no be found\n");
      return (-1);
    }
  fprintf(stdout, "Closed connection with number %d client\n", client->cs);
  return (0);
}

int		delete_rest(t_list *list, t_client *client)
{
  t_link	*tmp;
  t_link	*prev;

  prev = list->first;
  tmp = list->first->next;
  if ((t_client *)prev->data == client)
    {
      list->first = tmp;
      free(prev);
      return (0);
    }
  while (tmp)
    {
      if ((t_client *)tmp->data == client)
	{
	  prev->next = tmp->next;
	  free(tmp);
	  return (0);
	}
      prev = prev->next;
      tmp = tmp->next;
    }
  return (1);
}

int		delete_client(t_list *list, t_client *client)
{
  t_link	*tmp;

  if (list == NULL)
    return (0);
  tmp = list->first;
  if (tmp->next == NULL && (t_client *)tmp->data == client)
    {
      free(tmp);
      list->first = NULL;
      list = NULL;
      return (0);
    }
  else
    return (delete_rest(list, client));
}
