/*
** server_structure.h for includes in /home/baezse_s/zappy_julien/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 11:42:04 2013 Sergio Baez
** Last update Sat Jul 13 18:23:35 2013 Sergio Baez
*/

#ifndef SERVER_STRUCTURE_H_
# define SERVER_STRUCTURE_H_

# include			<sys/types.h>
# include			<sys/socket.h>
# include			<netinet/in.h>
# include			<sys/time.h>
# include			<sys/select.h>
# include			<sys/types.h>
# include			<unistd.h>
# include			<stdio.h>
# include			"client_structure.h"
# include			"parameter_structure.h"
# include			"cell_structure.h"
# include			"minerals.h"
# include			"list.h"
# define SELECT_WAIT		5
# define MAX_LVL		8
# define CLI_NUM		100
# define MAX_FD			100
# define FD_FREE		0
# define FD_SERV		1
# define FD_CLI			2
# define NUM_CMDS		12
# define GRAPHIC		"GRAPHIC"

typedef unsigned int		u_int;
typedef int			(*funct)();
typedef struct sockaddr_in	t_sock;

typedef struct			s_egg
{
  int				id;
  int				x;
  int				y;
  int                           pl_cs;
}				t_egg;

typedef struct			s_command
{
  char				*cmd;
  funct				fc;
  double			delay;
}				t_command;

typedef struct			s_server
{
  int				sfd;
  struct timeval		tv;
  u_int				port;
  u_int				width;
  u_int				height;
  u_int				num_clients;
  t_list			*teams;
  t_list			*new_clients;
  t_list			*graphic_clients;
  double			time_delay;
  int				fd_type[MAX_FD];
  funct				serv_function;
  t_command			commands[NUM_CMDS];
  t_cell			**world;
  u_int				max_num_minerals;
  u_int				current_num_minerals[NUM_MIN];
  u_int				generation_interval;
  u_int				minerals_consumed;
  char				msg[4096];
  fd_set			fd_read;
  fd_set			fd_write;
}				t_server;

int				usleep(u_int usec);
int				prepare_server(t_server *);
int				run_server(t_server *);
int				add_client(t_server *, int);
void				display_teams(t_server *);
int				prepare_commands(t_server *server);
int				start_main_cicle(t_server *server);
int				init_world(t_server *server);
int				prepare_socket(t_server *);
void				put_server_info(struct sockaddr_in *, t_server *);
int				wait_for_select(t_server *);
int				check_fd(t_server *);
int				init_clients(t_server *);
int				read_for_client(t_server *, t_client *);
int				close_connection(t_client *, t_list *);
int				delete_rest(t_list *list, t_client *client);
int				delete_client(t_list *list, t_client *client);
int				write_client(t_server *, t_client *, char *, int);
int				write_graphic_clients(t_server *, char *, int);
int				graphic_protocol(t_server *, t_client *, char *);
int				client_protocol(t_server *, t_client *, char *);
int				check_add_players(t_server *, t_client *, char *);
int				read_for_player(t_server *server, t_client *client);
int				check_clients_fd(t_server *ser);
int				check_players_fd(t_server *ser);
void				set_fd_players(t_server *r, int *);
void				set_fd_graph_clients(t_server *, int *);
void                            set_fd_clients(t_server *, int *);
int				check_graph_clients_fd(t_server *);
int				get_parameters(int , char **, t_server *);
int				parse_port(t_server *, int, char **, int);
int				parse_width(t_server *,int, char **, int);
int				parse_height(t_server *, int, char **, int);
int				parse_teams(t_server *, int, char **, int);
int				get_unique_id(t_server *server);
void				get_my_egg(t_egg *egg, t_server *server, t_client *player);
int				check_for_egg(t_server *server, t_teams *team, u_int *x, u_int *y);
int                             launch_player_func(t_client *, t_server *);
int				parse_clients(t_server *, int, char **, int);
int				parse_time(t_server *, int, char **, int);
int				test_parameters(t_server *params);
void				free_world(t_server *server);
int				init_cells(t_server *server);
int				init_minerals(t_server *server);
int                             send_egg_info(t_server *, char *);
int                             send_complete_info(t_server *, t_client *, char *);
int				add_stone(t_mineral type, t_server *server);
int				generate_minerals(t_server *server);
void				set_fds(t_server *, int);
int				cnt_min(t_cell *, t_mineral);
int				send_graph_info(t_server *, int, char *);
int				insert_graph_client(t_server *, t_link *);
int				move_to_graph_clients(t_server *, t_client *);
int				read_for_graph_client(t_server *, t_client *);
int				check_graph_commands(t_server *, t_client *, char *);
int				send_other_info(t_server *, t_client *);
void				prepare_graph_commands(t_client *);
int				graph_directions(cardinal_dir dir);
void				fill_inv_buff(char *, t_client *, int);
int				send_graph_inst(t_server *server, t_client *player, char *cmd);
int				update_map(t_server *server);
int				prepare_socket(t_server *);
void				put_server_info(struct sockaddr_in *, t_server *);
int				init_clients(t_server *);
int				read_for_client(t_server *, t_client *);
int				close_connection(t_client *, t_list *);
int				delete_rest(t_list *list, t_client *client);
int				delete_client(t_list *list, t_client *client);
int				write_graphic_clients(t_server *, char *, int);
int				graphic_protocol(t_server *, t_client *, char *);
int				client_protocol(t_server *, t_client *, char *);
int				check_add_players(t_server *, t_client *, char *);
int				read_for_player(t_server *server, t_client *client);
int				check_clients_fd(t_server *ser);
int				get_parameters(int , char **, t_server *);
int				parse_port(t_server *, int, char **, int);
int				parse_width(t_server *,int, char **, int);
int				parse_height(t_server *, int, char **, int);
int				parse_teams(t_server *, int, char **, int);
int				parse_clients(t_server *, int, char **, int);
int				parse_time(t_server *, int, char **, int);
int				test_parameters(t_server *params);
void				free_world(t_server *server);
int				init_cells(t_server *server);
int				init_minerals(t_server *server);
int				add_stone(t_mineral type, t_server *server);
int				generate_minerals(t_server *server);
int				cnt_min(t_cell *, t_mineral);
int				insert_graph_client(t_server *, t_link *);
int				move_to_graph_clients(t_server *, t_client *);
int				read_for_graph_client(t_server *, t_client *);
int                             send_players_info(t_server *, char *);
int				send_team_names(t_server *, t_client *, char *);
int				send_other_info(t_server *, t_client *);
void				prepare_graph_commands(t_client *);
int				graph_directions(cardinal_dir dir);
void				fill_inv_buff(char *, t_client *, int);
void				free_everything(t_server *server);
void				free_commands(t_server *server);
int				ready_to_write(t_client *client);
void				free_teams(t_server *server);
int				send_prend_client(t_server *ser, t_client *pl);
int				send_pose_client(t_server *server, t_client *player);
int				check_end_game(t_server *server, int max_lvl);

#endif /* !SERVER_STRUCTURE_H_ */
