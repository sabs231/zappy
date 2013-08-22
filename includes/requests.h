/*
** requests.h for includes in /home/baezse_s/zappy/includes
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Fri Jun 28 16:39:44 2013 Sergio Baez
** Last update Sat Jun 29 13:04:40 2013 Sergio Baez
*/

#ifndef REQUESTS_H_
# define REQUESTS_H_

# include			<sys/time.h>

typedef struct s_client		t_client;

typedef int			(*funct)();

typedef struct			s_request
{
  int				called;
  funct				fc;
  t_client			*player;
  char				*arg;
  struct timeval		call_time;
}				t_request;

#endif /* !REQUESTS_H_ */
