/*
** my_getnbr.c for my_getnbr in /home/nicolas.polomack/CPool_Day04
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Oct  6 17:52:30 2016 Nicolas POLOMACK
** Last update Sat Jan  7 04:12:20 2017 Nicolas Polomack
*/

#include "my.h"

int	get_nbr_len(char *arr, int count)
{
  int	nbr_len;
  int	total;

  total = 0;
  nbr_len = 1;
  while (*(arr + count) >= 48 && *(arr + count) <= 57)
    {
      nbr_len *= 10;
      total += *(arr + count) - 48;
      count += 1;
    }
  if (my_strlen(arr) >= 9 && total > 46)
      nbr_len = 0;
  return (nbr_len);
}

int	my_getnbr(char *arr)
{
  int	resp;
  int	count;
  int	isNegative;
  int	nbr_len;

  resp = 0;
  count = 0;
  while (!(*(arr + count) >= 48 && *(arr + count) <= 57))
    count = count + 1;
  if (*(arr + count - 1) == '-')
    isNegative = (-1);
  else
    isNegative = 1;
  nbr_len = get_nbr_len(arr, count);
  nbr_len = nbr_len / 10;
  while (*(arr + count) >=  48 && *(arr + count) <= 57)
    {
      resp += (*(arr + count) - 48) * (nbr_len);
      count = count + 1;
      nbr_len = nbr_len / 10;
    }
  return (resp * isNegative);
}
