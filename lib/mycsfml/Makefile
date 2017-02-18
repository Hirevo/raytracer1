##
## Makefile for Makefile in /home/nicolas/libraries/lib_backup
##
## Made by Nicolas POLOMACK
## Login   <nicolas@epitech.eu>
##
## Started on  Tue Nov  1 12:04:24 2016 Nicolas POLOMACK
## Last update Fri Feb 17 17:35:59 2017 Nicolas Polomack
##

SRC	=	sfcaster.c	\
		sfpixel.c	\
		sfcreator.c	\
		sfcolor.c	\
		sfraytracer.c	\
		sftrig.c

SRC2	=	sfassemble.c

OBJ	=	$(SRC:.c=.o)

OBJ2	=	$(SRC2:.c=.o)

NAME	=	libmycsfml.a

NAME2    =       libmycsfml-sa.a

CFLAGS	=	-I../../include -W -Wall -Werror -Wextra -pedantic

all:	$(NAME)

$(NAME):$(OBJ) $(OBJ2)
	@ar rc $(NAME) $(OBJ) $(OBJ2)
	@ar rc $(NAME2) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all
