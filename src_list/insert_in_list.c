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

int		insert_in_list(t_list **list, void *data)
{
  t_link	*link;
  t_link	*tmp;

  if ((*list) == NULL || data == NULL)
    return (-1);
  if ((link = new_link(data)) == NULL)
    return (-1);
  if ((*list)->first == NULL)
  {
    (*list)->first = link;
  }
  else
  {
    tmp = (*list)->first;
    while (tmp->next != NULL)
    {
      tmp = tmp->next;
    }
    tmp->next = link;
  }
  return (0);
}
