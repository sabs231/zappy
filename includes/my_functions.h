/*
** my_functions.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:43:35 2013 Sergio Baez
** Last update Wed Jul 10 14:14:18 2013 Sergio Baez
*/

#ifndef MY_FUNCTIONS_H_
# define MY_FUNCTIONS_H_

#include	<stdlib.h>
#include	"server_structure.h"

void		*my_malloc(size_t, int);
int		my_modulo(int a, int b);
time_t		my_time(time_t *t);
int		str_is_nbr(char *);
void		free_server(t_server *);
void		free_list(t_list **list);
void		clean_str(char *str);
int		name_exist(t_list **teams, char *name);

#endif /* !MY_FUNCTIONS_H_ */
