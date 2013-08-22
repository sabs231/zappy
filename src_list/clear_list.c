/*
** clear_list.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:29 2013 Sergio Baez
*/

#include	"list.h"

void		clear_list(t_list **list)
{
  t_link	*tmp;

  if (list == NULL || *list == NULL)
    return ;
  if ((*list)->first == NULL)
  {
    free(*list);
    *list = NULL;
    return ;
  }
  while ((*list)->first != NULL)
  {
    tmp = (*list)->first->next;
    free((*list)->first);
    (*list)->first = tmp;
  }
  free(*list);
  *list = NULL;
}
