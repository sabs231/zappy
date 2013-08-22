/*
** server_error_functions.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Wed May 08 12:10:27 2013 Sergio Baez
** Last update Fri Jul 12 16:59:40 2013 fabien massaro
*/

#ifndef SERVER_ERROR_FUNCTIONS_H_
# define SERVER_ERROR_FUNCTIONS_H_

# define NUM_ERR	8

typedef enum		errors
{
  NEW_CLIENT,
  NEW_TEAM,
  TEAM_NAME,
  SER_CMD,
  CELL,
  MIN,
  MSG,
  EGG
}			ser_errors;

typedef struct		s_err_msg
{
  ser_errors		num_err;
  char			msg[64];
}			t_err_msg;

int			incorrect_param_number(char **argv);
int			parameters_error(char *msg);
void			print_error(int err);

#endif /* !SERVER_ERROR_FUNCTIONS_H_ */
