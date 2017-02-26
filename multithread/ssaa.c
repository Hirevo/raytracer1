/*
** ssaa.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 26 14:19:17 2017 Nicolas Polomack
** Last update Sun Feb 26 14:22:35 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

sfColor		aver_col(sfColor *col, int ssaa)
{
  int		i;
  float		f[3];
  sfColor	fin;

  i = -1;
  f[0] = 0;
  f[1] = 0;
  f[2] = 0;
  while (++i < ssaa)
    {
      f[0] += col[i].r;
      f[1] += col[i].g;
      f[2] += col[i].b;
    }
  f[0] = roundf(((float)f[0]) / ((float)ssaa));
  f[1] = roundf(((float)f[1]) / ((float)ssaa));
  f[2] = roundf(((float)f[2]) / ((float)ssaa));
  fin.r = (f[0] > 255) ? 255 : f[0];
  fin.g = (f[1] > 255) ? 255 : f[1];
  fin.b = (f[2] > 255) ? 255 : f[2];
  fin.a = 255;
  return (fin);
}

sfColor		ssaa(t_thread *t, float x, float y, sfColor *col)
{
  float		fx;
  float		fy;
  float		ssaa_offs;
  int		i;

  i = 0;
  fx = -0.5F;
  ssaa_offs = 1.0F / fmax((sqrtf((float)(t->params->ssaa)) - 1.0F), 1);
  while (fx <= 0.5F)
    {
      fy = -0.5F;
      while (fy <= 0.5F)
        {
          t->ray = t->params->ray;
          t->ray.dir = calc_dir_vector(t->params->screen_size,
                                       x + fx, y + fx, t->params->fov);
          rotation_t_eye(t);
          t->can_reflect = 0;
          col[i] = gather_color(t);
          i += 1;
          fy += ssaa_offs;
        }
      fx += ssaa_offs;
    }
  return (aver_col(col, t->params->ssaa));
}
