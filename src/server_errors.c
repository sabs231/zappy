/*
** server_errors.c for src in /home/baezse_s/zappy/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:09:09 2013 Sergio Baez
** Last update Fri Jul 12 16:36:55 2013 fabien massaro
*/

#include	<stdio.h>
#include	"server_error_functions.h"

int		incorrect_param_number(char **argv)
{
  fprintf(stderr, "usage: %s [-p port] [-x width] [-y height]", argv[0]);
  fprintf(stderr, " [-n name_team1 name_team2 ...] [-c client number]");
  fprintf(stderr, " [-t time delay]\n");
  return (-1);
}

int		parameters_error(char *msg)
{
  fprintf(stderr, "Error: there is no %s\n", msg);
  return (-1);
}
