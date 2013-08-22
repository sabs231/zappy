/*
** new_list.c for src_list in /home/baezse_s/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed Jul 10 13:37:31 2013 Sergio Baez
*/

#include	<stdio.h>
#include	"list.h"

t_list		*new_list(void)
{
  t_list	*list;

  if ((list = malloc(sizeof(t_list))) == NULL)
  {
    fprintf(stderr, "List memory allocation failed.\n");
    return (NULL);
  }
  list->first = NULL;
  return (list);
}
