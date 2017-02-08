/*
** calc.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 23:10:06 2017 Nicolas Polomack
** Last update Wed Feb  8 01:48:50 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <float.h>
#include "sfcaster.h"
#include "raytracer.h"

void	sub_coords(t_params *params, t_obj *obj)
{
  params->ray.orig.x -= obj->pos.x;
  params->ray.orig.y -= obj->pos.y;
  params->ray.orig.z -= obj->pos.z;
}

void	add_coords(t_params *params, t_obj *obj)
{
  params->ray.orig.x += obj->pos.x;
  params->ray.orig.y += obj->pos.y;
  params->ray.orig.z += obj->pos.z;
}

float	gather_distances(t_params *params, int i)
{
  float	f;

  sub_coords(params, &(params->objs[i]));
  f = ((params->objs[i].type == 's') ?
       intersect_sphere(params->ray.orig, params->ray.dir,
                        params->objs[i].rad) :
       ((params->objs[i].type == 'p') ?
        intersect_plane(params->ray.orig, params->ray.dir) :
        ((params->objs[i].type == 'c') ?
         intersect_cyl(params->ray.orig, params->ray.dir,
                       params->objs[i]) :
         ((params->objs[i].type == 'o') ?
          intersect_cone(params->ray.orig, params->ray.dir,
                         params->objs[i]) :
          FLT_MAX))));
  add_coords(params, &(params->objs[i]));
  return (f);
}

void		render_frame(t_my_framebuffer *buffer, t_params *params)
{
  int		x;
  int		y;
  float		*dist;
  int		i;

  dist = malloc(sizeof(float) * params->nb_obj);
  x = -1;
  while (++x < buffer->width)
    {
      y = -1;
      while (++y < buffer->height)
        {
          params->screen_pos.x = x;
          params->screen_pos.y = y;
	  params->ray.dir = calc_dir_vector(params->screen_size,
                                    params->screen_pos);
          i = -1;
          while (++i < params->nb_obj)
            {
              dist[i] = gather_distances(params, i);
            }
          put_pixel(buffer, x, y, color_stuff(dist, params));
        }
    }
}
