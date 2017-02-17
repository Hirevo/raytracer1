##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Fri Feb 17 12:13:17 2017 Nicolas Polomack
##

MAKE2	=	make --no-print-directory -C ../../lib/my

MAKE1	=	make --no-print-directory -C ../../lib/mycsfml

SRC	=	window.c			\
		events.c			\
		socket.c			\
		launch.c			\
		load.c				\
		free.c				\
		parse/parse.c			\
		parse/check.c			\
		parse/util.c			\
		parse/proc.c			\
		get_next_line.c			\
		load_bmp.c			\
		save_bmp.c

OBJ	=	$(SRC:.c=.o)

FLAGS	=	-lm -L../../lib/my -lmy -L../../lib/mycsfml -lmycsfml -lc_graph_prog $(CFLAGS) -ansi

CFLAGS	=	-Iinclude -I../../include -W -Wall -Wextra -Werror -pedantic -pthread -Ofast -march=native

NAME	=	raytracer

all:	$(NAME)

$(NAME):$(OBJ)
	@$(MAKE1)
	@$(MAKE2)
	gcc -o $(NAME) $(OBJ) $(FLAGS)

clean:
	rm -f $(OBJ)
	@$(MAKE1) clean
	@$(MAKE2) clean

fclean:	clean
	rm -f $(NAME)
	@$(MAKE1) fclean
	@$(MAKE2) fclean

re:	fclean all
