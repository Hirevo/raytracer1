##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Thu Feb  9 21:57:33 2017 Nicolas Polomack
##

MAKE2	=	make --no-print-directory -C lib/my

MAKE1	=	make --no-print-directory -C lib/mycsfml

SRC	=	window.c		\
		calc.c			\
		events.c		\
		angles.c		\
		lights.c		\
		multi_lights.c		\
		parse.c			\
		check.c			\
		util.c			\
		rotation.c		\
		anti_rotation.c		\
		intersect_sphere.c	\
		intersect_cyl.c		\
		intersect_cone.c	\
		intersect_plane.c	\
		calc_dir_vector.c	\
		get_next_line.c		\
		load_bmp.c		\
		save_bmp.c

OBJ	=	$(SRC:.c=.o)

FLAGS	=	-lm -Llib/my -lmy -Llib/mycsfml -lmycsfml -lc_graph_prog $(CFLAGS) -ansi

CFLAGS	=	-Iinclude -Ofast -march=native -W -Wall -Wextra -Werror -pedantic

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

test:	$(OBJ)
	cc $(CFLAGS)   -c -o print_raycast.o print_raycast.c
	@$(MAKE1)
	@$(MAKE2)
	gcc -o $(NAME) $(OBJ) print_raycast.o $(FLAGS) $(CFLAGS)

fclean:	clean
	rm -f $(NAME)
	@$(MAKE1) fclean
	@$(MAKE2) fclean

re:	fclean all
