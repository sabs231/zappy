/*
** minerals.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed Jun 12 16:11:21 2013 Sergio Baez
** Last update Fri Jul 12 15:21:53 2013 fabien massaro
*/

#include	<math.h>
#include	<string.h>
#include	"server_error_functions.h"
#include	"server_structure.h"
#include	"get_direction.h"
#include	"minerals.h"
#include	"my_functions.h"
#include	"list.h"

int		init_minerals(t_server *server)
{
  server->max_num_minerals = ceil((server->width * server->height) /
				  (NUM_MIN));
  memset(server->current_num_minerals, 0, (NUM_MIN * sizeof(int)));
  server->generation_interval =  server->max_num_minerals / 3;
  server->minerals_consumed = 0;
  return (0);
}

int		add_stone(t_mineral type, t_server *server)
{
  u_int		x;
  u_int		y;
  t_mineral	*mineral;

  if ((mineral = (t_mineral *)my_malloc(sizeof(t_mineral), MIN)) == NULL)
    return (-1);
  x = rand() % server->width;
  y = rand() % server->height;
  *mineral = type;
  if (insert_in_list(&server->world[x][y].minerals, mineral) == -1)
    return (-1);
  return (0);
}

int		generate_minerals(t_server *s)
{
  t_counters	count;

  count.i = -1;
  count.save_j = 0;
  s->minerals_consumed = 0;
  while (++count.i < NUM_MIN)
    {
      count.save_i = s->max_num_minerals - s->current_num_minerals[count.i];
      if (count.save_i > 0)
	{
	  count.save_j = 1;
	  count.j = -1;
	  while (++count.j < count.save_i)
	    {
	      if (add_stone(count.i, s) == -1)
		return (-1);
	      s->current_num_minerals[count.i]++;
	    }
	}
    }
  if (count.save_j != 0)
    update_map(s);
  return (0);
}

int		cnt_min(t_cell *cell, t_mineral mineral)
{
  t_link	*tmp;
  int		result;

  result = 0;
  tmp = cell->minerals->first;
  while (tmp)
    {
      if ((*(t_mineral *)tmp->data) == mineral)
	result++;
      tmp = tmp->next;
    }
  return (result);
}

int		delete_mineral(t_cell *cell, t_mineral mineral)
{
  t_link	*tmp;
  t_minerals	*min;

  tmp = cell->minerals->first;
  while (tmp)
    {
      min = (t_minerals *)(tmp->data);
      if (min->value == mineral)
	return (delete_element(cell->minerals, tmp->data));
      tmp = tmp->next;
    }
  return (-1);
}
