/*
** depth_of_field.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar  2 18:49:13 2017 Nicolas Polomack
** Last update Fri Mar 17 11:12:37 2017 Nicolas Polomack
*/

#include <float.h>
#include <limits.h>
#include "raytracer.h"

void		calc_focal_vector(t_thread *t, float x, float y)
{
  sfVector3f	aim;
  float		dx;
  float		dy;

  t->ray.orig = t->start;
  t->ray.dir = calc_dir_vector(t->params->screen_size,
			       x, y, t->params->fov);
  rotation_t_eye(t);
  aim.x = t->ray.orig.x + t->ray.dir.x * t->focal_dist;
  aim.y = t->ray.orig.y + t->ray.dir.y * t->focal_dist;
  aim.z = t->ray.orig.z + t->ray.dir.z * t->focal_dist;
  dx = ((float)my_rand(t->params->seed)) / (((float)(INT_MAX) + 1.0F));
  dy = ((float)my_rand(t->params->seed)) / (((float)(INT_MAX) + 1.0F));
  t->ray.orig.y += dx;
  t->ray.orig.z += dy;
  t->ray.dir.x = aim.x - t->ray.orig.x;
  t->ray.dir.y = aim.y - t->ray.orig.y;
  t->ray.dir.z = aim.z - t->ray.orig.z;
}

void	set_focal_dist(t_thread *t)
{
  int	i;

  t->ray.dir = calc_dir_vector(t->params->screen_size,
                               t->params->screen_size.x / 2 + 300,
                               t->params->screen_size.y - 200,
                               t->params->fov);
  rotation_t_eye(t);
  i = -1;
  while (++i < t->params->nb_obj)
    t->dist[i] = gather_distances(t->params->objs, t->ray, i);
  t->focal_dist = FLT_MAX;
  i = -1;
  while (++i < t->params->nb_obj)
    if (t->dist[i] < t->focal_dist && t->dist[i] > 0)
      t->focal_dist = t->dist[i];
}

sfColor		dof(t_thread *t, float x, float y)
{
  float		i;
  float		j;
  sfColor	col;

  i = -1;
  while (++i < t->params->depth_rays)
    {
      j = -1;
      while (++j < t->params->depth_rays)
	{
          calc_focal_vector(t, x + (j / t->params->depth_rays),
			    y + (i / t->params->depth_rays));
          t->can_reflect = (t->is_primary = 1) * 0;
          t->depth_col[(int)((i * t->params->depth_rays) + j)] =
	    gather_color(t);
        }
    }
  col = aver_col(t->depth_col,
		 t->params->depth_rays * t->params->depth_rays);
  return (col);
}
