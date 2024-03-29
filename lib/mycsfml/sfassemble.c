/*
** sfassemble.c for mycsfml in /home/nicolaspolomack/graphical/raytracer1/bonus/server
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Feb 17 17:31:45 2017 Nicolas Polomack
** Last update Wed Feb 22 02:39:56 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include <SFML/Graphics.h>

t_my_framebuffer	*assemble_texture(sfTexture **tex, sfSprite **spr,
                                          int width, int height)
{
  t_my_framebuffer	*buffer;

  *tex = sfTexture_create(width, height);
  *spr = sfSprite_create();
  if (!*tex || !*spr)
    return (NULL);
  sfSprite_setTexture(*spr, *tex, sfTrue);
  buffer = my_framebuffer_create(width, height);
  return (buffer);
}
