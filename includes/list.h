/*
** list.h for includes in /home/baezse_s/zappy/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed Jun 12 17:04:37 2013 Sergio Baez
*/

#ifndef LIST_H_
# define LIST_H_

# include	<stdlib.h>

typedef struct	s_link
{
  void		*data;
  struct s_link	*next;
}		t_link;

typedef struct	s_list
{
  t_link	*first;
}		t_list;

t_list		*new_list(void);
t_link		*new_link(void *data);
int		insert_in_list(t_list **list, void *data);
void		*delete_first(t_list *list);
t_link		*get_last_link(t_list *list);
int		size_list(t_list *list);
int		is_empty_list(t_list *list);
void		apply_in_list(t_list *list, void (*f)(void *));
void		clear_list(t_list **list);
int		delete_element(t_list *list, void *data);

#endif /* !LIST_H_ */
