/*
** my_put_nbr.c for my_put_nbr in /home/nicolas.polomack/CPool_Day03
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Wed Oct  5 14:49:19 2016 Nicolas POLOMACK
** Last update Sat Jan 14 14:30:59 2017 Nicolas Polomack
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

void	my_put_nbr_base(int n, int base, t_flags *flags, int *count)
{
  int	nbr;

  if (n < 0)
    {
      my_putchar_printf('-', count);
      n *= -1;
    }
  if (n >= 0)
    {
      if (n >= base)
	{
	  nbr = (n % base);
	  n = (n - nbr) / base;
	  my_put_nbr_base(n, base, flags, count);
	  if (nbr < 10)
	    my_putchar_printf('0' + n, count);
	  else
	    my_putchar_printf((flags->format == 'X' ? 'A' : 'a') + n - 10, count);
	}
    }
  else
    if (n < 10)
      my_putchar_printf('0' + n, count);
    else
      my_putchar_printf((flags->format == 'X' ? 'A' : 'a') + n - 10, count);
}

void	my_put_nbr(int n)
{
  int	nbr;

  if (n < 0)
    {
      my_putchar('-');
      n *= -1;
    }
  if (n >= 0)
    {
      if (n >= 10)
	{
	  nbr = (n % 10);
	  n = (n - nbr) / 10;
	  my_put_nbr(n);
	  my_putchar('0' + nbr);
	}
      else
	my_putchar('0' + n);
    }
  else
    my_putchar('0' + n);
}

char	*my_int_to_char(int i)
{
  char	*resp;
  char	isNegative;
  int	n;
  int	size;

  (i < 0) ? isNegative = '-' + ((i *= -1) * 0) : 0;
  n = i;
  size = 0;
  while (n > 0)
    n /= 10 + ((size += 1) * 0);
  size += 2;
  if ((resp = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  resp[size--] = 0;
  if (i == 0)
    resp[size--] = '0';
  else
    while (i > 0)
      {
	resp[size--] = i % 10 + '0';
	i /= 10;
      }
  resp[size--] = '0';
  (isNegative == '-') ? resp[size--] = isNegative : 0;
  return ((resp[size + 2] == 0) ? resp + size + 1 : resp + size + 2);
}

char	*my_long_to_char(long i)
{
  char	*resp;
  char	isNegative;
  long	n;
  long	size;

  (i < 0) ? isNegative = '-' + ((i *= -1) * 0) : 0;
  n = i;
  size = 0;
  while (n > 0)
    n /= 10 + ((size += 1) * 0);
  size += 2;
  if ((resp = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  resp[size--] = 0;
  if (i == 0)
    resp[size--] = '0';
  else
    while (i > 0)
      {
	resp[size--] = i % 10 + '0';
	i /= 10;
      }
  (isNegative == '-') ? resp[size--] = isNegative : 0;
  return (resp + size + 1);
}

char	*my_unsigned_to_char(unsigned int i)
{
  char	*resp;
  unsigned int	n;
  unsigned int	size;

  n = i;
  size = 0;
  while (n > 0)
    n /= 10 + ((size += 1) * 0);
  size += 2;
  if ((resp = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  resp[size--] = 0;
  if (i == 0)
    resp[size--] = '0';
  else
    while (i > 0)
      {
	resp[size--] = i % 10 + '0';
	i /= 10;
      }
  return (resp + size + 1);
}
