/*
** cell_structure.h for includes in /home/baezse_s/zappy/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed Jun 12 11:12:53 2013 Sergio Baez
** Last update Mon Jun 24 16:07:59 2013 Sergio Baez
*/

#ifndef CELL_STRUCTURE_H_
# define CELL_STRUCTURE_H_

# include		"list.h"

typedef unsigned int	u_int;

typedef struct		s_cell
{
  int			id_cell;
  t_list		*players;
  t_list		*minerals;
  u_int			food;
  u_int			x;
  u_int			y;
  u_int			debug;
}			t_cell;

#endif /* !CELL_STRUCTURE_H_ */
