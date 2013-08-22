/*
** parameter_structure.h for includes in /home/baezse_s/zappy/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 11:53:19 2013 Sergio Baez
** Last update Tue Jun 11 00:11:07 2013 Sergio Baez
*/

#ifndef PARAMETER_STRUCTURE_H_
# define PARAMETER_STRUCTURE_H_

# include	"list.h"
# include	"server_structure.h"

typedef struct	s_cmd
{
  char		*cmd;
  funct		fc;
}		t_cmd;

#endif /* !PARAMETER_STRUCTURE_H_ */
