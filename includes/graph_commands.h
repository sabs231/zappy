/*
** graph_commands.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Sat Jul 06 14:34:30 2013 Sergio Baez
** Last update Sat Jul 06 16:05:45 2013 Sergio Baez
*/

#ifndef GRAPH_COMMANDS_H_
# define GRAPH_COMMANDS_H_

# include	"server_structure.h"
# include	"client_structure.h"

int		map_size(t_server *, t_client *, char *);
int		cell_content(t_server *, t_client *, char *);
int		world_content(t_server *, t_client *, char *);
int		team_names(t_server *, t_client *, char *);
int		player_position(t_server *, t_client *, char *);
int		player_level(t_server *, t_client *, char *);
int		player_inventory(t_server *, t_client *, char *);
int		time_unit(t_server *, t_client *, char *);
int		set_time_unit(t_server *, t_client *, char *);
t_client	*get_player(t_server *server, int p_num);

#endif /* !GRAPH_COMMANDS_H_ */
