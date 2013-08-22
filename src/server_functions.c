/*
** server_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 04 14:56:23 2013 Sergio Baez
** Last update Sat Jul 13 15:29:42 2013 fabien massaro
*/

#include	<string.h>
#include	"server_error_functions.h"
#include	"server_structure.h"
#include	"cell_structure.h"
#include	"my_functions.h"
#include	"commands.h"
#include	"list.h"
#include	"teams.h"

int		start_main_cicle(t_server *server)
{
  while (1)
    {
      if (wait_for_select(server) == -1)
	return (-1);
      if (check_fd(server) == -1)
	return (-1);
      if (server->minerals_consumed >= server->generation_interval)
	{
	  if (generate_minerals(server) == -1)
	    return (-1);
	}
      if (check_requests(server) == -1)
	return (-1);
      if (check_life_players(server) == -1)
	return (-1);
      if (check_end_game(server, MAX_LVL) == -1)
	{
	  printf("Fin de partie\n");
	  return (-1);
	}
    }
  return (0);
}

int		add_client(t_server *server, int fd)
{
  t_client	*client;
  t_sock	client_sin;
  socklen_t	client_sin_len;

  if ((client = (t_client *)my_malloc(sizeof(t_client), NEW_CLIENT)) == NULL)
    return (0);
  client_sin_len = (socklen_t)sizeof(client_sin);
  if ((client->cs = accept(fd, (struct sockaddr *)&client_sin,
			   &client_sin_len)) == -1)
    {
      perror("accept");
      return (-1);
    }
  client->fd_type = FD_CLI;
  client->client_function = read_for_client;
  client->my_team = NULL;
  client->my_cell = NULL;
  if (insert_in_list(&server->new_clients, client) == -1)
    return (-1);
  if (write(client->cs, "BIENVENUE\n", strlen("BIENVENUE\n")) == -1)
    {
      perror("write");
      return (-1);
    }
  return (0);
}

int		prepare_next_commands(t_server *server)
{
  strncpy(server->commands[4].cmd, "inventaire", strlen("inventaire"));
  server->commands[4].fc = &inventory;
  server->commands[4].delay = 1.0 / server->time_delay;
  strncpy(server->commands[5].cmd, "prend", strlen("prend"));
  server->commands[5].fc = &pick_object;
  server->commands[5].delay = 7.0 / server->time_delay;
  strncpy(server->commands[6].cmd, "pose", strlen("pose"));
  server->commands[6].fc = &drop_object;
  server->commands[6].delay = 7.0 / server->time_delay;
  strncpy(server->commands[7].cmd, "expulse", strlen("expulse"));
  server->commands[7].fc = &expel;
  server->commands[7].delay = 7.0 / server->time_delay;
  strncpy(server->commands[8].cmd, "broadcast", strlen("broadcast"));
  server->commands[8].fc = &broadcast;
  server->commands[8].delay = 7.0 / server->time_delay;
  strncpy(server->commands[9].cmd, "incantation", strlen("incantation"));
  server->commands[9].fc = &incantation;
  server->commands[9].delay = 300.0 / server->time_delay;
  strncpy(server->commands[10].cmd, "fork", strlen("fork"));
  server->commands[10].fc = &player_fork;
  server->commands[10].delay = 42.0 / server->time_delay;
  strncpy(server->commands[11].cmd, "connect_nbr", strlen("connect_nbr"));
  server->commands[11].fc = &number_slots;
  server->commands[11].delay = 0.0;
  return (0);
}

int		prepare_commands(t_server *server)
{
  int		i;

  i = 0;
  while (i < NUM_CMDS)
    {
      if ((server->commands[i].cmd = (char *)my_malloc(64, SER_CMD)) == NULL)
	return (-1);
      memset(server->commands[i].cmd, '\0', 64);
      i++;
    }
  strncpy(server->commands[0].cmd, "avance", strlen("avance"));
  server->commands[0].fc = &advance;
  server->commands[0].delay = 7.0 / server->time_delay;
  strncpy(server->commands[1].cmd, "droite", strlen("droite"));
  server->commands[1].fc = &rigth;
  server->commands[1].delay = 7.0 / server->time_delay;
  strncpy(server->commands[2].cmd, "gauche", strlen("gauche"));
  server->commands[2].fc = &left;
  server->commands[2].delay = 7.0 / server->time_delay;
  strncpy(server->commands[3].cmd, "voir", strlen("voir"));
  server->commands[3].fc = &see;
  server->commands[3].delay = 7.0 / server->time_delay;
  return (prepare_next_commands(server));
}

int		init_world(t_server *server)
{
  u_int		i;

  i = 0;
  fprintf(stdout, "Initializing world...\n");
  if ((server->world = (t_cell **)my_malloc(server->width *
					sizeof(t_cell *), CELL)) == NULL)
    return (-1);
  while (i < server->width)
    {
      if ((server->world[i] = (t_cell *)my_malloc(server->height *
						sizeof(t_cell), CELL)) == NULL)
	return (-1);
      i++;
    }
  if (init_cells(server) == -1)
    return (-1);
  fprintf(stdout, "World initialized\n");
  return (0);
}
