/*
** my_strcpy.c for my_strcpy in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:09:04 2016 Nicolas POLOMACK
** Last update Wed Mar  1 10:53:45 2017 Nicolas Polomack
*/

void	my_memcpy(void *ptr, void *ptr2, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    *((char *)ptr) = *((char *)ptr2);
}

char	*my_memset(char *buffer, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    buffer[i] = 0;
  return (buffer);
}

char	*my_strcpy(char *dest, char *src)
{
  int	count;

  count = -1;
  while (src[++count])
    dest[count] = src[count];
  dest[count] = 0;
  return (dest);
}
