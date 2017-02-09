/*
** my_put_pixel.c for wireframe in /home/nicolaspolomack/mylibcsfml/
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Nov 18 19:24:57 2016 Nicolas Polomack
** Last update Tue Jan 10 16:17:58 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "src.h"

void	my_put_pixel(t_my_framebuffer *buffer, int x,
		     int y, sfColor color)
{
  if (x < 0 || x >= buffer->width || y < 0 || y >= buffer->height)
    return ;
  buffer->pixels[(buffer->width * y + x) * 4] = color.r;
  buffer->pixels[(buffer->width * y + x) * 4 + 1] = color.g;
  buffer->pixels[(buffer->width * y + x) * 4 + 2] = color.b;
  buffer->pixels[(buffer->width * y + x) * 4 + 3] = color.a;
}
