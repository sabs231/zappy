/*
** take_commands2.c for src in /home/baezse_s/zappy/src
** 
** Made by Sergio Baez
** Login   <baezse_s@epitech.net>
** 
** Started on  Tue Jun 11 00:00:16 2013 Sergio Baez
** Last update Sat Jul 13 15:31:08 2013 fabien massaro
*/

#include	<stdio.h>
#include	<string.h>
#include	"commands.h"
#include	"list.h"
#include       	"my_functions.h"
#include	"server_error_functions.h"

int		send_prend_client(t_server *ser, t_client *pl)
{
  if (write_client(ser, pl, "ko\n", strlen("ko\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [prend]=>ko\n", pl->cs);
  return (0);
}

int		send_pose_client(t_server *server, t_client *player)
{
  if (write_client(server, player, "ko\n", strlen("ko\n")) == -1)
    return (-1);
  fprintf(stdout, "Message to player %d: [pose]=>ko\n", player->cs);
  return (1);
}
