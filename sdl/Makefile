##
## ETNA PROJECT, 10/02/2020 by habi_a
## c:\Users\habiy\Documents\bomberman\sdl
## File description:
##      Makefile
##

CC		= 	gcc
CFLAGS	+= 	-Wall -Wextra -Werror -Wpedantic
LDFLAGS	=	-lSDL2 -lSDL2main -lSDL2_image

NAME	=	bomberman

SRC		=	main.c \
			action.c \
			app.c \
			bag.c \
			bomb.c \
			check_move.c \
			game.c \
			move.c \
			player.c

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
