/*
** my_strncpy.c for my_strncpy in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Oct 10 09:22:36 2016 Nicolas POLOMACK
** Last update Tue Oct 11 17:14:17 2016 Nicolas POLOMACK
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	count;

  count = 0;
  while (n > 0)
    {
      *(dest + count) = *src;
      count = count + 1;
      src = src + 1;
      n = n - 1;
    }
  return (dest);
}
