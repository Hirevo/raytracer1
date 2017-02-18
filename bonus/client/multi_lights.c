/*
** multi_lights.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 21:56:13 2017 Nicolas Polomack
** Last update Sat Feb 18 23:34:28 2017 Nicolas Polomack
*/

#include "raytracer.h"

sfColor		average_colors(sfColor *col, int nb_l)
{
  sfColor	final;
  int		rgb[3];
  int		i;

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  i = -1;
  while (++i < nb_l)
    {
      rgb[0] += col[i].r;
      rgb[1] += col[i].g;
      rgb[2] += col[i].b;
    }
  final.r = rgb[0] / nb_l;
  final.g = rgb[1] / nb_l;
  final.b = rgb[2] / nb_l;
  final.a = 255;
  return (final);
}

sfColor		seek_lights(float *dist, t_thread *t, int i)
{
  sfColor	col[t->params->nb_lights];
  int		l;
  sfVector2i	idxs;

  l = -1;
  idxs.x = i;
  while (++l < t->params->nb_lights)
    {
      idxs.y = l;
      col[l] = intersect_light(dist[i], t, idxs) ?
	t->params->objs[i].col : TRANSPARENT;
      if (col[l].a)
        col[l] = evaluate_luminosity(dist, t, col[l], idxs);
    }
  return (average_colors(col, t->params->nb_lights));
}
