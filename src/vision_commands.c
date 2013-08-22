/*
** vision_commands.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 23:56:14 2013 Sergio Baez
** Last update Fri Jul 12 16:53:06 2013 fabien massaro
*/

#include		<stdio.h>
#include		<string.h>
#include		"commands.h"
#include		"teams.h"
#include		"client_structure.h"
#include		"server_structure.h"

extern t_minerals	g_min[];

int			see(t_server * server, t_client *player, char *word)
{
  int			i;
  t_direction		view_directions[] =
    {
      {NORTH, &view_north},
      {SOUTH, &view_south},
      {EAST, &view_east},
      {WEST, &view_west},
      {99, NULL}
    };

  (void)word;
  i = 0;
  while (view_directions[i].dir != 99)
    {
      if (player->direction.front == view_directions[i].dir)
	{
	  if (view_directions[i].function(server, player) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}

int			inventory(t_server *server, t_client * player, char *word)
{
  int			i;
  char			buff[(14 + MIN_SIZE) * NUM_MIN];
  char			number[32];

  (void)word;
  (void)server;
  i = 0;
  memset(buff, '\0', ((14 + MIN_SIZE) * NUM_MIN));
  memset(number, '\0', 32);
  strcat(buff, "{");
  while (i < NUM_MIN)
    {
      strcat(buff, g_min[i].name);
      strcat(buff, " ");
      sprintf(number, "%d", player->inventory[i]);
      strcat(buff, number);
      if (i < NUM_MIN - 1)
	strcat(buff, ", ");
      i++;
    }
  strcat(buff, "}\n");
  if (write_client(server, player, buff, ((14 + MIN_SIZE) * NUM_MIN)) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, buff);
  return (0);
}

int			number_slots(t_server *server, t_client *player,
				     char *word)
{
  char			buff[13];

  (void)word;
  (void)server;
  memset(buff, '\0', 13);
  sprintf(buff, "%d\n", ((t_teams *)player->my_team)->num_players);
  if (write_client(server, player, buff, strlen(buff)) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: %s\n", player->cs, buff);
  return (0);
}
