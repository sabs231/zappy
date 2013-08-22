/*
** delete_first.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:38 2013 Sergio Baez
*/

#include	"list.h"

void		*delete_first(t_list *list)
{
  void		*data;
  t_link	*tmp;

  if (list == NULL || list->first == NULL)
    return (NULL);
  tmp = list->first->next;
  data = list->first->data;
  free(list->first);
  list->first = tmp;
  return (data);
}
