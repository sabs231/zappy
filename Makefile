##
## Makefile for zappy in /home/baezse_s/zappy_julien/zappy
##
## Made by Sergio Baez
## Login   <baezse_s@epitech.net>
##
## Started on  Thu May 02 19:46:57 2013 Sergio Baez
## Last update Sat Jul 13 19:38:05 2013 Sergio Baez
##

SERVER_SRC 		= 	src_list/apply_in_list.c 		\
				src_list/clear_list.c 			\
				src_list/delete_first.c			\
				src_list/get_last_link.c		\
				src_list/insert_in_list.c		\
				src_list/is_empty_list.c		\
				src_list/new_link.c			\
				src_list/new_list.c			\
				src_list/size_list.c			\
				src_list/delete_element.c		\
				src/server_errors.c 			\
				src/my_functions.c 			\
				src/extra_functions.c 			\
				src/handle_parameters.c 		\
				src/handle_parameters1.c	 	\
				src/teams_functions.c 			\
				src/client_functions.c 			\
				src/sockets_functions.c 		\
				src/server_functions.c 			\
				src/server_functions2.c 		\
				src/communication.c 			\
				src/players_functions.c 		\
				src/file_descriptor_functions.c 	\
				src/file_descriptor_functions2.c 	\
				src/check_commands.c 			\
				src/move_commands.c 			\
				src/special_commands.c 			\
				src/get_direction.c 			\
				src/get_direction2.c 			\
				src/take_commands.c 			\
				src/take_commands2.c 			\
				src/vision_commands.c 			\
				src/world_functions.c 			\
				src/minerals.c 				\
				src/incantation.c 			\
				src/check_egg.c 			\
				src/end_game.c 				\
				src/vision_subcommands.c 		\
				src/move_subcommands.c 			\
				src/players_functions2.c 		\
				src/graphic_client_functions.c 		\
				src/graphic_client_functions2.c 	\
				src/graphic_client_functions3.c 	\
				src/graphic_client_commands.c 		\
				src/graphic_client_commands2.c 		\
				src/graphic_client_commands3.c 		\
				src/server_main.c

SERVER_OBJS 		= 	$(SERVER_SRC:.c=.o)

SERVER_NAME 		= 	server

CFLAGS 			+= 	-lm -I./includes
CFLAGS 			+= 	-W -Wall -Wextra -Werror

GCC 			= 	gcc

all: 				$(SERVER_NAME)
				cd graphics; make

$(SERVER_NAME): 		$(SERVER_OBJS)
				$(GCC) $(CFLAGS) -o $@ $^
				cp ./client/client.rb .

clean:
				rm -f $(SERVER_OBJS)
				cd graphics; make clean

fclean: 			clean
				rm -f $(SERVER_NAME)
				rm -f client.rb
				cd graphics; make fclean

re: 				fclean all

.PHONY: 			all clean fclean re
