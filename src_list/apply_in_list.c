/*
** apply_in_list.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:23 2013 Sergio Baez
*/

#include	"list.h"

void		apply_in_list(t_list *list, void (*f)(void *))
{
  t_link	*tmp;

  if (list == NULL || list->first == NULL || f == NULL)
    return ;
  tmp = list->first;
  while (tmp != NULL)
  {
    (*f)(tmp->data);
    tmp = tmp->next;
  }
}
