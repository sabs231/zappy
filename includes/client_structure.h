/*
** client_structure.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 04 18:06:57 2013 Sergio Baez
** Last update Tue Jul 09 11:22:59 2013 Sergio Baez
*/

#ifndef CLIENT_STRUCTURE_H_
# define CLIENT_STRUCTURE_H_

# include		<time.h>
# include		"requests.h"
# include		"cell_structure.h"
# include		"minerals.h"
# define DIR_NUM	4
# define REQ_NUM	10
# define LIFE_NUM	126.0
# define GRAPH_COMM	9

typedef int		(*funct)();

typedef enum		dir
{
  NORTH = 0,
  EAST,
  SOUTH,
  WEST
}			cardinal_dir;

typedef struct s_teams	t_teams;

typedef struct		s_compass
{
  cardinal_dir		front;
}			t_compass;

typedef struct		s_gcommand
{
  char			cmd[255];
  funct			fc;
}			t_gcommand;

typedef struct		s_client
{
  int			cs;
  int			fd_type;
  funct			client_function;
  void			*my_team;
  t_cell		*my_cell;
  int			level;
  t_compass		direction;
  int			inventory[NUM_MIN];
  t_request		requests[REQ_NUM];
  time_t		life_time;
  int			ready;
  t_gcommand		graph_commands[GRAPH_COMM];
}			t_client;

#endif /* !CLIENT_STRUCTURE_H_ */
