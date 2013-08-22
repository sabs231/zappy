/*
** get_last_link.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:44 2013 Sergio Baez
*/

#include	"list.h"

t_link		*get_last_link(t_list *list)
{
  t_link	*tmp;

  if (list == NULL)
    return (NULL);
  tmp = list->first;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp);
}
