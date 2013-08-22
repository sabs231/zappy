/*
** commands.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Mon Jun 10 23:12:52 2013 Sergio Baez
** Last update Sat Jul 06 12:33:48 2013 Sergio Baez
*/

#ifndef COMMANDS_H_
# define COMMANDS_H_

# include	"server_structure.h"

typedef struct	s_direction
{
  cardinal_dir	dir;
  funct		function;
}		t_direction;

void		move_player(t_client *player, t_list *src, t_list *dest);
int		move_north(t_server *server, t_client *player);
int		move_south(t_server *server, t_client *player);
int		move_east(t_server *server, t_client *player);
int		move_west(t_server *server, t_client *player);
int		advance(t_server *, t_client *, char *);
int		rigth(t_server *, t_client *, char *);
int		left(t_server *, t_client *, char *);
int		see(t_server *, t_client *, char *);
int		inventory(t_server *, t_client *, char *);
int		do_the_pick(t_server *, t_client *, char *);
int		pick_object(t_server *, t_client *, char *);
int		do_the_drop(t_server *, t_client *, int);
int		drop_object(t_server *, t_client *, char *);
int		expel(t_server *, t_client *, char *);
int		do_the_broadcast(t_server *, t_client *, char *);
int		broadcast(t_server *, t_client *, char *);
int		incantation(t_server *, t_client *, char *);
int		player_fork(t_server *, t_client *, char *);
int		number_slots(t_server *, t_client *, char *);
int		die(t_server *, t_client *);
int		check_command(t_server *, t_client *, char *);
double		get_time_delay(t_server *, t_client *, int);
void		realocate_requests(t_client *, int);
int		handle_request(t_server *, t_client *);
int		check_requests(t_server *);
void		check_space(int *flag, char *stuff);
void		show_cell_content(t_server *, t_client *, int , int);
int		view_north(t_server *, t_client *);
int		view_south(t_server *, t_client *);
int		view_east(t_server *, t_client *);
int		view_west(t_server *, t_client *);

#endif /* !COMMANDS_H_ */
