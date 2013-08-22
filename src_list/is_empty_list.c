/*
** is_empty_list.c for src_list in /home/baezse_s/zappy/zappy/src_list
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 16:33:00 2013 Sergio Baez
** Last update Wed May 08 16:55:57 2013 Sergio Baez
*/

#include	"list.h"

int		is_empty_list(t_list *list)
{
  return (!size_list(list));
}
