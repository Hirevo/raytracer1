##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Mon Feb 20 14:15:47 2017 Nicolas Polomack
##

MAKE1	=	make --no-print-directory -C lib/my

MAKE2	=	make --no-print-directory -C lib/mycsfml

MAKE_S	=	make --no-print-directory -C bonus/server

MAKE_C	=	make --no-print-directory -C bonus/client

MAKE_ST	=	make --no-print-directory -C singlethread

MAKE_MT	=	make --no-print-directory -C multithread

all:
	@$(MAKE1)
	@$(MAKE2)
	@$(MAKE_ST)
	@$(MAKE_MT)
	@$(MAKE_C)
	@$(MAKE_S)

clean:
	@$(MAKE1) clean
	@$(MAKE2) clean
	@$(MAKE_ST) clean
	@$(MAKE_MT) clean
	@$(MAKE_C) clean
	@$(MAKE_S) clean

fclean:	clean
	@$(MAKE1) fclean
	@$(MAKE2) fclean
	@$(MAKE_ST) fclean
	@$(MAKE_MT) fclean
	@$(MAKE_C) fclean
	@$(MAKE_S) fclean

re:	fclean all
