/*
** insert_in_list.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Thu May 09 13:32:22 2013 Sergio Baez
*/

#include	"list.h"

int		delete_element(t_list *list, void *data)
{
  t_link	*tmp;
  t_link	*prev;

  if (list == NULL || list->first == NULL || data == NULL)
    return (1);
  prev = list->first;
  tmp = prev->next;
  if (prev->data == data)
  {
    list->first = prev->next;
    free(prev);
    return (0);
  }
  while (tmp != NULL)
  {
    if (tmp->data == data)
    {
      prev->next = tmp->next;
      free(tmp);
      return (0);
    }
    tmp = tmp->next;
    prev = prev->next;
  }
  return (1);
}
