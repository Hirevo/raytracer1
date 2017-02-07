##
## Makefile for Makefile in /home/nicolas/libraries/lib_backup
##
## Made by Nicolas POLOMACK
## Login   <nicolas@epitech.eu>
##
## Started on  Tue Nov  1 12:04:24 2016 Nicolas POLOMACK
## Last update Tue Feb  7 00:13:20 2017 Nicolas Polomack
##

SRC	=	sfcaster.c	\
		sfpixel.c	\
		sfcreator.c	\
		sfcolor.c	\
		sfraytracer.c	\
		sftrig.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmycsfml.a

CFLAGS	=	-I../../include -W -Wall -Werror -Wextra -pedantic -Ofast -march=native

all:	$(NAME)

$(NAME):$(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all
