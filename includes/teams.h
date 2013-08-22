/*
** teams.h for includes in /home/baezse_s/zappy_julien/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Thu May 09 11:07:18 2013 Sergio Baez
** Last update Sat Jul 13 18:00:37 2013 Sergio Baez
*/

#ifndef TEAMS_H_
# define TEAMS_H_

# include	"list.h"
# include	"server_structure.h"

typedef struct	s_teams
{
  u_int		id;
  u_int		num_players;
  char		*name;
  t_list	*players;
  t_list	*eggs;
}		t_teams;

int		add_team_name(t_list **teams, char *name, int id);
int		check_add_players(t_server *, t_client *, char *);
int		move_to_players(t_teams *, t_list *, t_client *, t_server *);
int		insert_player(t_teams *, t_link *, t_server *);
int		send_info(t_teams *team, t_link *client, t_server *server);
int		init_player_data(t_teams *, t_link *, t_server *);
int		put_player_info(t_teams *, t_link *);
int		handle_life(t_server *server, t_client *player);
int		check_life_players(t_server *server);
int		get_direction(t_client *player, t_client *from, t_server *server);
int		get_broadcast_msg(char *msg, t_client *player,
				t_client *from, t_server *server);

#endif /* !TEAMS_H_ */
