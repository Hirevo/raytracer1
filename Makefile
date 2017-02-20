##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Mon Feb 20 12:11:26 2017 Nicolas Polomack
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
	ln -s singlethread/raytracer raytracer_st
	ln -s multithread/raytracer raytracer_mt
	ln -s bonus/client/raytracer raytracer_client
	ln -s bonus/server/raytracer raytracer_server

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
	rm -f raytracer_st
	rm -f raytracer_mt
	rm -f raytracer_client
	rm -f raytracer_server

re:	fclean all
