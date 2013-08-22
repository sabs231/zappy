/*
** my_functions.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:43:17 2013 Sergio Baez
** Last update Fri Jul 12 15:28:09 2013 fabien massaro
*/

#include	<stdio.h>
#include	<time.h>
#include	"my_functions.h"
#include	"server_error_functions.h"

t_err_msg	g_err[NUM_ERR] =
{
  {NEW_CLIENT, "Could not allocate memory for client"},
  {NEW_TEAM, "Could not allocate memory for team"},
  {TEAM_NAME, "Could not allocate memory for team name"},
  {SER_CMD, "Could not allocate memory for the server commands"},
  {CELL, "Coudl not allocate memory for the world"},
  {MIN, "Could not allocate memory for minerals"},
  {MSG, "Could not allocate memory for the message"},
  {EGG, "Could not allocate memory for the egg"},
};

void		*my_malloc(size_t size, int err)
{
  void		*structure;

  if ((structure = malloc(size)) == NULL)
    {
      perror("malloc");
      print_error(err);
      return (NULL);
    }
  return (structure);
}

int		my_modulo(int a, int b)
{
  while (a < 0)
    a += b;
  while (a >= b)
    a -= b;
  return (a);
}

time_t		my_time(time_t *t)
{
  time_t	ret;

  if ((ret = time(t)) == (time_t)-1)
    {
      perror("time");
      return ((time_t)-1);
    }
  return (ret);
}

void		print_error(int err)
{
  int		i;

  i = 0;
  while (i < NUM_ERR)
    {
      if ((int) g_err[i].num_err == err)
	fprintf(stderr, "%s\n", g_err[i].msg);
      i++;
    }
}
