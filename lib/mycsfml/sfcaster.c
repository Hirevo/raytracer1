/*
** sfcaster.c for sfcaster.c in /home/nicolaspolomack/mylibcsfml/
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Nov 18 18:50:32 2016 Nicolas Polomack
** Last update Sat Jan 14 17:12:20 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include "sfcaster.h"

t_my_framebuffer	*assemble_texture(sfTexture **tex, sfSprite **spr,
					  int width, int height)
{
  t_my_framebuffer	*buffer;

  *tex = sfTexture_create(width, height);
  *spr = sfSprite_create();
  sfSprite_setTexture(*spr, *tex, sfTrue);
  buffer = my_framebuffer_create(width, height);
  return (buffer);
}

t_my_framebuffer	*my_framebuffer_create(int width, int height)
{
  sfUint8		*pixels;
  t_my_framebuffer	*framebuffer;
  int			i;

  framebuffer = malloc(sizeof(t_my_framebuffer));
  pixels = malloc(sizeof(sfUint8) * width * height * 4);
  if (pixels == NULL || framebuffer == NULL)
    return (NULL);
  framebuffer->pixels = pixels;
  framebuffer->width = width;
  framebuffer->height = height;
  i = 0;
  while (i < width * height * 4)
    {
      pixels[i] = 0;
      i = i + 1;
    }
  return (framebuffer);
}

void	clear_pixels(t_my_framebuffer *buffer)
{
  int	i;

  i = 0;
  while (i < buffer->width * buffer->height * 4)
    {
      buffer->pixels[i] = 0;
      i = i + 1;
    }
}
