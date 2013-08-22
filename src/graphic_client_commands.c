/*
** graphic_client_commands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Sat Jul 06 14:33:53 2013 Sergio Baez
** Last update Fri Jul 12 15:12:19 2013 fabien massaro
*/

#include	<string.h>
#include	"graph_commands.h"
#include	"list.h"

int		map_size(t_server *server, t_client *client, char *arg)
{
  char		buff[32];

  (void) arg;
  memset(buff, '\0', 32);
  sprintf(buff, "msz %d %d\n", server->width, server->height);
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

int		cell_content(t_server *server, t_client *client, char *arg)
{
  char		buff[32];
  int		x;
  int		y;
  t_cell	*c;

  x = atoi(strtok(arg, " \t\n\r"));
  y = atoi(strtok(NULL, " \t\n\r"));
  memset(buff, '\0', 32);
  if ((x > (int)server->width || y > (int)server->height) ||
      (x < 0 || y < 0))
    {
      if (write_client(server, client, "sbp\n", strlen("sbp\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: sbp\n", client->cs);
      return (0);
    }
  c = &server->world[x][y];
  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y, cnt_min(c, FOOD),
	  cnt_min(c, LINEMATE), cnt_min(c, DERAUMERE), cnt_min(c, SIBUR),
	  cnt_min(c, MENDIANE), cnt_min(c, PHIRAS), cnt_min(c, THYSTAME));
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}

int		world_content(t_server *server, t_client *client, char *arg)
{
  char		buff[32];
  t_link	*link;

  (void) arg;
  if ((link = new_link(client)) == NULL)
    return (-1);
  memset(buff, '\0', 32);
  if (send_graph_info(server, ((t_client *)link->data)->cs, &buff[0]) == -1)
    return (-1);
  free(link);
  return (0);
}

int		team_names(t_server *server, t_client *client, char *arg)
{
  char		buff[32];

  (void) arg;
  memset(buff, '\0', 32);
  if (send_team_names(server, client, &buff[0]) == -1)
    return (-1);
  return (0);
}

int		player_position(t_server *server, t_client *client, char *arg)
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
      return (0);
    }
  memset(buff, '\0', 32);
  sprintf(buff, "ppo #%d %d %d %d\n", p_num, pl->my_cell->x, pl->my_cell->y,
	  graph_directions(pl->direction.front));
  if (write_client(server, client, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to graph client %d: %s\n", client->cs, buff);
  return (0);
}
