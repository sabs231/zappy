##
## Makefile for machina_virtual in /home/brunie_j/local/machina_virtual
##
## Made by Brunier Jean
## Login   <brunie_j@epitech.net>
##
## Started on  Wed Feb 13 15:57:38 2013 Brunier Jean
## Last update Tue Feb 19 10:31:53 2013 Brunier Jean
##

CXX	= g++

NAME	= ../graphic

DOBJ	= obj
DSRC	= .
DINC	= ../include			\
		  .

SRCS	= Map.cpp				\
		  Socket.cpp			\
		  Graphics.cpp			\
		  main.cpp

INCLUDE = $(addprefix -I $(DSRC)/, $(DINC))

OBJS	= $(addprefix $(DOBJ)/, $(SRCS:.cpp=.o))

CXXFLAGS	= $(INCLUDE) -Wall -Wextra -g

LDXFLAGS = -lpthread -lm -lsfml-window -lsfml-graphics -lsfml-system


all: $(NAME)

$(NAME):  $(OBJS)
	$(CXX) $^ -o $@ $(LDXFLAGS)

$(DOBJ)/%.o: $(DSRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $^ -c -o $@ $(CXXFLAGS)

clean:
	rm -Rf $(DOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
