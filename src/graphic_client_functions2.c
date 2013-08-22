/*
** graphic_client_functions2.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Fri Jul 05 16:02:55 2013 Sergio Baez
** Last update Fri Jul 12 15:13:47 2013 fabien massaro
*/

#include	<string.h>
#include	"graph_commands.h"
#include	"server_structure.h"
#include	"client_structure.h"

int		check_graph_commands(t_server *server, t_client *g_cli, char *msg)
{
  int		i;
  char		*word1;
  char		*word2;

  i = 0;
  word1 = strtok(msg, " \t\n\r");
  if (word1 != NULL)
    {
      word2 = msg + strlen(word1) + 1;
      while (i < GRAPH_COMM)
	{
	  if (strcmp(g_cli->graph_commands[i].cmd, word1) == 0)
	    {
	      if (g_cli->graph_commands[i].fc(server, g_cli, word2) == -1)
		return (-1);
	      return (0);
	    }
	  i++;
	}
      if (write_client(server, g_cli, "suc\n", strlen("suc\n")) == -1)
	return (-1);
      fprintf(stdout, "Message to graph client %d: suc\n", g_cli->cs);
    }
  return (0);
}

int		send_other_info(t_server *s, t_client *pl)
{
  char		buff1[128];
  char		buff2[64];

  memset(buff1, '\0', 128);
  memset(buff2, '\0', 64);
  sprintf(buff1, "pin #%d %d %d %d %d %d %d %d %d %d\n",
	  pl->cs, pl->my_cell->x, pl->my_cell->y, pl->inventory[FOOD],
	  pl->inventory[LINEMATE], pl->inventory[DERAUMERE],
	  pl->inventory[SIBUR], pl->inventory[MENDIANE],
	  pl->inventory[PHIRAS], pl->inventory[THYSTAME]);
  sprintf(buff2, "bct %d %d %d %d %d %d %d %d %d\n",
	  pl->my_cell->x, pl->my_cell->y, cnt_min(pl->my_cell, FOOD),
	  cnt_min(pl->my_cell, LINEMATE), cnt_min(pl->my_cell, DERAUMERE),
	  cnt_min(pl->my_cell, SIBUR), cnt_min(pl->my_cell, MENDIANE),
	  cnt_min(pl->my_cell, PHIRAS), cnt_min(pl->my_cell, THYSTAME));
  strcat(buff1, buff2);
  if (write_graphic_clients(s, buff1, strlen(buff1)) == -1)
    return (-1);
  fprintf(stdout, "Message to all graph clients: %s\n", buff1);
  return (0);
}

void		prepare_graph_commands(t_client *client)
{
  strncpy(client->graph_commands[0].cmd, "msz", strlen("msz"));
  client->graph_commands[0].fc = &map_size;
  strncpy(client->graph_commands[1].cmd, "bct", strlen("bct"));
  client->graph_commands[1].fc = &cell_content;
  strncpy(client->graph_commands[2].cmd, "mct", strlen("mct"));
  client->graph_commands[2].fc = &world_content;
  strncpy(client->graph_commands[3].cmd, "tna", strlen("tna"));
  client->graph_commands[3].fc = &team_names;
  strncpy(client->graph_commands[4].cmd, "ppo", strlen("ppo"));
  client->graph_commands[4].fc = &player_position;
  strncpy(client->graph_commands[5].cmd, "plv", strlen("plv"));
  client->graph_commands[5].fc = &player_level;
  strncpy(client->graph_commands[6].cmd, "pin", strlen("pin"));
  client->graph_commands[6].fc = &player_inventory;
  strncpy(client->graph_commands[7].cmd, "sgt", strlen("sgt"));
  client->graph_commands[7].fc = &time_unit;
  strncpy(client->graph_commands[8].cmd, "sst", strlen("sst"));
  client->graph_commands[8].fc = &set_time_unit;
}

int		graph_directions(cardinal_dir dir)
{
  return (((int)dir) + 1);
}

int		ready_to_write(t_client *client)
{
  client->ready = 1;
  return (0);
}
