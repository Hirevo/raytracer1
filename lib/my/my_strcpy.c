/*
** my_strcpy.c for my_strcpy in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Oct 10 09:09:04 2016 Nicolas POLOMACK
** Last update Mon Oct 10 19:01:53 2016 Nicolas POLOMACK
*/

char	*my_strcpy(char *dest, char *src)
{
  int	count;

  count = 0;
  while (*src != '\0')
    {
      *(dest + count) = *src;
      count = count + 1;
      src = src + 1;
    }
  return (dest);
}
