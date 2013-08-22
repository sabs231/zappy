/*
** get_direction.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 11:42:04 2013 Sergio Baez
** Last update Fri Jun 28 15:40:51 2013 Sergio Baez
*/

#ifndef GET_DIRECTION_H_
# define GET_DIRECTION_H_

# define MAX(a, b)	((a > b)?a:b)

# include		"server_structure.h"
# include		"cell_structure.h"
# include		"my_functions.h"
# include		<string.h>

typedef struct		s_counters
{
  int			i;
  int			j;
  int			save_i;
  int			save_j;
  int			min;
}			t_counters;

int			g_map[9];
void			get_good_tab(int map[9], t_client *player);
int			best_direction(int tab[9], int map[9]);
void			free_map(int **world, t_server *server);
int			get_direction(t_client *player, t_client *from,
					t_server *server);

#endif /* !GET_DIRECTION_H_ */
