/*
** take_commands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 11 00:00:16 2013 Sergio Baez
** Last update Fri Jul 12 16:49:45 2013 fabien massaro
*/

#include		<stdio.h>
#include		<string.h>
#include		"commands.h"
#include		"list.h"
#include		"my_functions.h"
#include		"server_error_functions.h"

extern t_minerals	g_min[];

static int		take_min(t_server *s, t_client *pl, t_link *min, int i)
{
  char			buff[32];

  memset(buff, '\0', 32);
  if (delete_element(pl->my_cell->minerals, min->data) == 0)
    {
      pl->inventory[i]++;
      s->minerals_consumed++;
      s->current_num_minerals[i]--;
      if (write_client(s, pl, "ok\n", strlen("ok\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to player %d: [prend]=>ok\n", pl->cs);
      sprintf(buff, "pgt #%d %d\n", pl->cs, i);
      if (write_graphic_clients(s, buff, strlen(buff)) == -1)
	return (-1);
      fprintf(stdout, "Message to all graph clients: %s\n", buff);
      if (send_other_info(s, pl) == -1)
	return (-1);
      return (0);
    }
  if (write_client(s, pl, "ko\n", strlen("ko\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [prend]=>ko\n", pl->cs);
  return (1);
}

int			do_the_pick(t_server *ser, t_client *pl, char *w)
{
  t_mineral		target;
  t_link		*temp;
  int			i;

  i = 0;
  while (i < NUM_MIN)
    {
      if ((strncmp(g_min[i].name, w, strlen(g_min[i].name)) == 0) &&
	  (strlen(g_min[i].name) == (strlen(w) - 1)))
	{
	  target = g_min[i].value;
	  temp = pl->my_cell->minerals->first;
	  while (temp)
	    {
	      if ((*((t_mineral *)temp->data)) == target)
		{
		  printf("take mineral\n");
		  return (take_min(ser, pl, temp, i));
		}
	      temp = temp->next;
	    }
	}
      i++;
    }
  return (send_prend_client(ser, pl));
}

int			pick_object(t_server *server, t_client *player, char *w)
{
  if (w == NULL)
    {
      if (write_client(server, player, "ko\n", strlen("ko\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to player %d: [prend]=>ko\n", player->cs);
      return (0);
    }
  if (do_the_pick(server, player, w) == -1)
    return (-1);
  return (0);
}

int			do_the_drop(t_server *server, t_client *player, int i)
{
  t_mineral		*min;
  char			buff[32];

  memset(buff, '\0', 32);
  if ((min = (t_mineral *)my_malloc(sizeof(t_mineral), MIN)) != NULL)
    {
      *min = g_min[i].value;
      if (insert_in_list(&(player->my_cell->minerals), min) == -1)
	return (-1);
      player->inventory[i]--;
      server->minerals_consumed--;
      server->current_num_minerals[i]++;
      if (write_client(server, player, "ok\n", strlen("ok\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to player %d: [pose]=>ok\n", player->cs);
      sprintf(buff, "pdr #%d %d\n", player->cs, i);
      if (write_graphic_clients(server, buff, strlen(buff)) == -1)
	return (-1);
      fprintf(stdout, "Message to all graph clients: %s\n", buff);
      if (send_other_info(server, player) == -1)
	return (-1);
      return (1);
    }
  return (send_pose_client(server, player));
}

int			drop_object(t_server *ser, t_client *player, char *w)
{
  int			i;

  (void)ser;
  i = 0;
  if (w == NULL)
    {
    if (write_client(ser, player, "ko\n", strlen("ko\n")) == -1)
      return (-1);
    fprintf(stdout, "Message to player %d: [prend]=>ok\n", player->cs);
    return (1);
    }
  while (i < NUM_MIN)
    {
      if ((strncmp(g_min[i].name, w, strlen(g_min[i].name)) == 0) &&
	  (strlen(g_min[i].name) == (strlen(w) - 1)) &&
	  (player->inventory[i] >= 1))
	return (do_the_drop(ser, player, i));
      i++;
    }
  if (write_client(ser, player, "ko\n", strlen("ko\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [pose]=>ok\n", player->cs);
  return (1);
}
