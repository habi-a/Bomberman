##
## ETNA PROJECT, 10/02/2020 by habi_a
## c:\Users\habiy\Documents\bomberman\sdl
## File description:
##      Makefile
##

CC		= 	gcc
CFLAGS	+= 	-Wall -Wextra -Werror -Wpedantic
LDFLAGS	=	-lSDL2 -lSDL2main

NAME	=	bomberman

SRC		=	main.c \
			game.c

OBJ		= 	$(SRC:.c=.o)

RM		= 	rm -f


all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: 	clean
	$(RM) $(NAME)

re:			fclean all

.PHONY	= 	all $(NAME) clean fclean re
