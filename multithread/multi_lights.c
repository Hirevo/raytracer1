/*
** multi_lights.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 21:56:13 2017 Nicolas Polomack
** Last update Mon Mar  6 10:23:23 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdlib.h>
#include "sfcaster.h"
#include "raytracer.h"

sfColor		get_shadow_color(t_thread *t,  int idx)
{
  sfColor	col;
  float		coef;

  coef = t->params->ambient;
  col.r = t->params->objs[idx].col.r * coef;
  col.g = t->params->objs[idx].col.g * coef;
  col.b = t->params->objs[idx].col.b * coef;
  col.a = 255;
  t->can_reflect = (t->params->ambient != 0);
  return (col);
}

sfColor		average_colors(sfColor *col, int nb_l,
			       t_thread *t, int idx)
{
  sfColor	final;
  int		rgb[3];
  int		i;
  int		s;

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  i = -1;
  s = 1;
  while (++i < nb_l)
    {
      if (col[i].r || col[i].g || col[i].b)
	s = 0;
      rgb[0] += col[i].r;
      rgb[1] += col[i].g;
      rgb[2] += col[i].b;
    }
  if (s == 1)
    return (get_shadow_color(t, idx));
  final.r = rgb[0] / nb_l;
  final.g = rgb[1] / nb_l;
  final.b = rgb[2] / nb_l;
  final.a = 255;
  return (final);
}

sfVector3f	get_shadow_ray(t_thread *t,
                               sfVector2i idxs, sfVector3f imp)
{
  sfVector3f	to_light;

  to_light = t->params->light[idxs.y].pos;
  to_light.x = (to_light.x + ((t->params->shadow_rays > 1 &&
                               t->is_primary == 1) ?
                              ((fmodf((float)my_rand(t->params->seed),
                                      100.0F)) / 10.0F) : 0)) - imp.x;
  to_light.y = (to_light.y + ((t->params->shadow_rays > 1 &&
                               t->is_primary == 1) ?
                              ((fmodf((float)my_rand(t->params->seed),
                                      100.0F)) / 10.0F) : 0)) - imp.y;
  to_light.z = to_light.z - imp.z;
  return (to_light);
}

sfColor		shadow_raytrace(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	to_light;
  sfVector3f	imp;
  sfColor	col[t->params->shadow_rays];
  int		x;

  imp.x = t->ray.orig.x + t->ray.dir.x * dist;
  imp.y = t->ray.orig.y + t->ray.dir.y * dist;
  imp.z = t->ray.orig.z + t->ray.dir.z * dist;
  x = -1;
  while ((++x < t->params->shadow_rays && t->is_primary) ||
	 (!(t->is_primary) && x == 0))
    {
      to_light = get_shadow_ray(t, idxs, imp);
      col[x] = (intersect_light(dist, t, imp, to_light)) ?
	t->params->objs[idxs.x].col : get_shadow_color(t, idxs.x);
    }
  t->can_reflect = 1;
  return (average_colors(col, (t->is_primary) ?
			 t->params->shadow_rays : 1, t, idxs.x));
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
      col[l] = shadow_raytrace(dist[i], t, idxs);
      if (col[l].a != sfTransparent.a)
        col[l] = evaluate_luminosity(t, col[l], idxs);
    }
  return (average_colors(col, t->params->nb_lights, t, idxs.x));
}
