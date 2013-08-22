/*
** new_link.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:51:06 2013 Sergio Baez
*/

#include	<stdio.h>
#include	"list.h"

t_link		*new_link(void *data)
{
  t_link	*link;

  if ((link = malloc(sizeof(t_link))) == NULL)
  {
    fprintf(stderr, "Memory allocation failed.\n");
    return (NULL);
  }
  link->data = data;
  link->next = NULL;
  return (link);
}
