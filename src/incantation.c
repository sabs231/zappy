/*
** incantation.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 11 00:00:16 2013 Sergio Baez
** Last update Fri Jul 12 15:20:13 2013 fabien massaro
*/

#include	<string.h>
#include	"incantation.h"

int		g_incant[][NUM_MIN] =
{
  {1, 1, 0, 0, 0, 0, 0},
  {2, 1, 1, 1, 0, 0, 0},
  {2, 2, 0, 1, 0, 2, 0},
  {4, 1, 1, 2, 0, 1, 0},
  {4, 1, 2, 1, 3, 0, 0},
  {6, 1, 2, 3, 0, 1, 0},
  {6, 2, 2, 2, 2, 2, 1}
};

static int	check_nb_players(t_client *player, int line)
{
  t_link	*current;
  t_client	*curr_pl;
  int		need_players;
  int		nb_players;

  need_players = g_incant[line][0];
  nb_players = 0;
  current = player->my_cell->players->first;
  while (current != NULL)
    {
      curr_pl = ((t_client *)current->data);
      if (curr_pl->level == line + 1)
	nb_players++;
      current = current->next;
    }
  if (nb_players >= need_players)
    return (0);
  return (-1);
}

static int	check_minerals(t_client *player, int line)
{
  int		type_min;

  type_min = 1;
  while (type_min < NUM_MIN)
    {
      if (cnt_min(player->my_cell, type_min) <
	  (g_incant[line][type_min] * g_incant[line][0]))
	return (-1);
      type_min++;
    }
  return (0);
}

static int	consume_minerals(t_server *server, t_client *player, int line)
{
  int		type_min;
  int		need_min;

  type_min = 1;
  while (type_min < NUM_MIN)
    {
      need_min = g_incant[line][type_min];
      while (need_min > 0)
	{
	  if (delete_mineral(player->my_cell, type_min) != 0)
	    return (-1);
	  server->minerals_consumed++;
	  server->current_num_minerals[type_min]--;
	  need_min--;
	}
      type_min++;
    }
  return (0);
}

void		level_up_players(t_server *server, t_client *player, int line)
{
  t_link	*current;
  t_client	*curr_pl;
  int		need_players;
  int		nb_players;
  char		buff[32];

  need_players = g_incant[line][0];
  nb_players = 0;
  current = player->my_cell->players->first;
  while (current != NULL)
    {
      curr_pl = ((t_client *)current->data);
      if (curr_pl->level == line + 1)
	{
	  nb_players++;
	  curr_pl->level++;
	  sprintf(buff, "plv #%d %d\n", curr_pl->cs, curr_pl->level);
	  write_graphic_clients(server, buff, strlen(buff));
	  if (nb_players >= need_players)
	    return ;
	}
      current = current->next;
    }
}

int		incantation(t_server *server, t_client *player, char *word)
{
  int		line_incant;
  char		buff[64];

  (void)word;
  line_incant = player->level - 1;
  if ((check_nb_players(player, line_incant) == -1) ||
      (check_minerals(player, line_incant) == -1) ||
      (consume_minerals(server, player, line_incant) == -1))
    {
      write_client(server, player, "ko\n", strlen("ko\n"));
      sprintf(buff, "pie %d %d ko\n", player->my_cell->x, player->my_cell->y);
      if (write_graphic_clients(server, buff, strlen(buff)) == -1)
	return (-1);
      return (0);
    }
  sprintf(buff, "pie %d %d ok\n", player->my_cell->x, player->my_cell->y);
  write_graphic_clients(server, buff, strlen(buff));
  level_up_players(server, player, line_incant);
  generate_minerals(server);
  sprintf(buff, "niveau actuel : %d\n", player->level);
  if (write_client(server, player, buff, strlen(buff)) == -1)
    return (-1);
  return (0);
}
