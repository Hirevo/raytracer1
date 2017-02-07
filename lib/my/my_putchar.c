/*
** my_putchar.c for my_putchar in /home/nicolas.polomack/libraries/lib_backup
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Oct 14 10:44:55 2016 Nicolas POLOMACK
** Last update Tue Nov 22 16:52:12 2016 Nicolas Polomack
*/

#include <unistd.h>

void	my_putchar_printf(char c, int *count)
{
  *count += 1;
  write(1, &c , 1);
}

void	my_putchar(char c)
{
  write(1, &c , 1);
}
