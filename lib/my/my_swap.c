/*
** my_swap.c for my_swap in /home/nicolas.polomack/CPool_Day04
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Oct  6 09:03:28 2016 Nicolas POLOMACK
** Last update Sat Jan  7 04:19:07 2017 Nicolas Polomack
*/

int	my_swap(int *a, int *b)
{
  int	temp;

  temp = *a;
  *a = *b;
  *b = temp;
  return (0);
}
