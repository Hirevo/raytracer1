/*
** my_strdup.c for my_strdup in /home/nicolas.polomack/CPool_Day08
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Wed Oct 12 09:23:05 2016 Nicolas POLOMACK
** Last update Sat Jan 14 14:33:06 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *src)
{
  char	*resp;
  int	count;

  count = 0;
  if ((resp = malloc(sizeof(char) * (my_strlen(src) + 1))) == NULL)
    return (NULL);
  while (src[count] != '\0')
    {
      resp[count] = src[count];
      count = count + 1;
    }
  resp[count] = '\0';
  return (resp);
}
