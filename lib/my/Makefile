##
## Makefile for Makefile in /home/nicolas/libraries/lib_backup
##
## Made by Nicolas POLOMACK
## Login   <nicolas@epitech.eu>
##
## Started on  Tue Nov  1 12:04:24 2016 Nicolas POLOMACK
## Last update Fri Jan 20 11:59:17 2017 Nicolas Polomack
##

SRC	=	my_putstr.c	\
		my_putchar.c	\
		my_put_nbr.c	\
		my_strcmp.c	\
		my_strstr.c	\
		my_strlen.c	\
		my_strcpy.c	\
		my_strcat.c	\
		my_strncat.c	\
		my_strncpy.c	\
		my_strncmp.c	\
		my_revstr.c	\
		my_getnbr.c	\
		my_find_prime_sup.c	\
		my_is_prime.c	\
		my_isneg.c	\
		my_power_rec.c	\
                my_showmem.c	\
                my_showstr.c	\
		my_sort_int_table.c	\
		my_square_root.c	\
		my_str_isalpha.c	\
		my_str_islower.c	\
		my_str_isprintable.c	\
		my_str_isnum.c	\
		my_str_isupper.c	\
		my_strcapitalize.c	\
		my_strlowcase.c	\
		my_strupcase.c	\
		my_swap.c	\
		my_strdup.c	\
		my_printf.c	\
		parsing.c	\
		my_strdup.c	\
		convert_base.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I../../include

NAME	=	libmy.a

all:	$(NAME)

$(NAME):$(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all
