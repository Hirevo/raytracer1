##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Fri Mar 17 13:36:30 2017 Nicolas Polomack
##

MAKE1	=	make --no-print-directory -sC lib/my

MAKE2	=	make --no-print-directory -sC lib/mycsfml

MAKE_S	=	make --no-print-directory -sC bonus/server

MAKE_C	=	make --no-print-directory -sC bonus/client

MAKE_MT	=	make --no-print-directory -sC multithread

all:
	@echo -n "Compilation libmy... "
	@$(MAKE1)
	@echo "OK"
	@echo -n "Compilation libmycsfml... "
	@$(MAKE2)
	@echo "OK"
	@echo -n "Compilation raytracer multithread... "
	@$(MAKE_MT)
	@echo "OK"
	@echo "Compilation raytracer clusterisé:"
	@echo -n "Compilation client... "
	@$(MAKE_C)
	@echo "OK"
	@echo -n "Compilation serveur... "
	@$(MAKE_S)
	@echo "OK"

mt:
	@$(MAKE_MT)

clean:
	@$(MAKE1) clean
	@$(MAKE2) clean
	@$(MAKE_MT) clean
	@$(MAKE_C) clean
	@$(MAKE_S) clean

fclean:	clean
	@$(MAKE1) fclean
	@$(MAKE2) fclean
	@$(MAKE_MT) fclean
	@$(MAKE_C) fclean
	@$(MAKE_S) fclean

re:	fclean all
