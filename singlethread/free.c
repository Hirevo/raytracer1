/*
** free.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 12 18:02:21 2017 Nicolas Polomack
** Last update Sun Feb 12 18:37:52 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"

int	free_all(t_params *params, t_window *w)
{
  free(params->dist);
  free(params->light);
  free(params->objs);
  free(w->buffer->pixels);
  free(w->buffer);
  if (!params->bmp)
    {
      free(w->save->pixels);
      free(w->save);
      sfTexture_destroy(w->texture);
      sfTexture_destroy(w->save_t);
      sfSprite_destroy(w->save_s);
      sfSprite_destroy(w->sprite);
      sfRenderWindow_destroy(w->window);
    }
  return (0);
}
