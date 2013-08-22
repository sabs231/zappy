/*
** size_list.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:16 2013 Sergio Baez
*/

#include	"list.h"

int		size_list(t_list *list)
{
  int		size;
  t_link	*tmp;

  size = 0;
  if (list == NULL || list->first == NULL)
    return (size);
  tmp = list->first;
  while (tmp != NULL)
  {
    size = size + 1;
    tmp = tmp->next;
  }
  return (size);
}
