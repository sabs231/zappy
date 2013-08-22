/*
** minerals.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 11:38:28 2013 Sergio Baez
** Last update Fri Jul 05 12:11:23 2013 Sergio Baez
*/

#ifndef MINERALS_H_
# define MINERALS_H_

# define NUM_MIN	7
# define MIN_SIZE	16

typedef enum		e_mineral
{
  FOOD,
  LINEMATE,
  DERAUMERE,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME
}			t_mineral;

typedef struct		s_minerals
{
  t_mineral		value;
  char			name[MIN_SIZE];
}			t_minerals;

double			ceil(double x);
int			delete_mineral(t_cell *cell, t_mineral mineral);

#endif /* !MINERALS_H_ */
