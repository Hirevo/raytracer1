/*
** ssaa.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 26 14:19:17 2017 Nicolas Polomack
** Last update Fri Mar 17 11:41:04 2017 Nicolas Polomack
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

void	render_pixel(t_thread *t, sfVector2f v, int i, sfVector2f f)
{
  if (t->params->depth_rays > 1)
    t->col[i] = dof(t, v.x, v.y);
  else
    {
      t->ray = t->params->ray;
      t->ray.dir = calc_dir_vector(t->params->screen_size,
				   v.x + f.x, v.y + f.y, t->params->fov);
      rotation_t_eye(t);
      t->can_reflect = (t->is_primary = 1) * 0;
      t->col[i] = gather_color(t);
    }
}

sfColor		ssaa(t_thread *t, float x, float y)
{
  float		ssaa_offs;
  int		i;
  sfVector2f	v;
  sfVector2f	f;

  i = 0;
  f.x = -0.5F;
  ssaa_offs = 1.0F / fmax((sqrtf((float)(t->params->ssaa)) - 1.0F), 1);
  while (f.x <= 0.5F)
    {
      f.y = -0.5F;
      while (f.y <= 0.5F)
        {
	  v.x = x;
	  v.y = y;
	  render_pixel(t, v, i, f);
          i += 1;
          f.y += ssaa_offs;
        }
      f.x += ssaa_offs;
    }
  return (aver_col(t->col, t->params->ssaa));
}

sfColor		no_ssaa(t_thread *t, int x, int y)
{
  sfColor	col;

  if (t->params->depth_rays > 1)
    col = dof(t, x, y);
  else
    {
      t->ray = t->params->ray;
      t->ray.dir = calc_dir_vector(t->params->screen_size,
				   x, y, t->params->fov);
      rotation_t_eye(t);
      t->is_primary = 1;
      t->can_reflect = 0;
      col = gather_color(t);
    }
  return (col);
}
