##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Sun Feb 12 18:36:33 2017 Nicolas Polomack
##

MAKE2	=	make --no-print-directory -C ../lib/my

MAKE1	=	make --no-print-directory -C ../lib/mycsfml

SRC	=	window.c			\
		calc.c				\
		events.c			\
		angles.c			\
		lights.c			\
		multi_lights.c			\
		load.c				\
		free.c				\
		parse/parse.c			\
		parse/check.c			\
		parse/util.c			\
		normals.c			\
		rotation.c			\
		anti_rotation.c			\
		intersect/intersect_sphere.c	\
		intersect/intersect_cyl.c	\
		intersect/intersect_disk.c	\
		intersect/intersect_cone.c	\
		intersect/intersect_plane.c	\
		calc_dir_vector.c		\
		get_next_line.c			\
		load_bmp.c			\
		save_bmp.c

OBJ	=	$(SRC:.c=.o)

FLAGS	=	-lm -L../lib/my -lmy -L../lib/mycsfml -lmycsfml -lc_graph_prog $(CFLAGS) -ansi

CFLAGS	=	-Iinclude -I../include -Ofast -march=native -W -Wall -Wextra -Werror -pedantic

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
