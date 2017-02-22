/*
** reflect.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Feb 22 02:28:54 2017 Nicolas Polomack
** Last update Wed Feb 22 02:40:11 2017 Nicolas Polomack
*/

#include <float.h>
#include "raytracer.h"
#include "sfcaster.h"

void		prepare_reflect(t_thread *t)
{
  float		norme;

  add_coords_vect(&t->normal, NULL, &(t->params->objs[t->idx]));
  t->ray.orig.x = t->ray.orig.x + t->ray.dir.x * t->dist[t->idx];
  t->ray.orig.y = t->ray.orig.y + t->ray.dir.y * t->dist[t->idx];
  t->ray.orig.z = t->ray.orig.z + t->ray.dir.z * t->dist[t->idx];
  norme = norm(t->normal);
  t->normal.x /= norme;
  t->normal.y /= norme;
  t->normal.z /= norme;
  norme = -2.0F * dot(t->normal, t->ray.dir);
  t->ray.dir.x = t->ray.dir.x + (t->normal.x * norme);
  t->ray.dir.y = t->ray.dir.y + (t->normal.y * norme);
  t->ray.dir.z = t->ray.dir.z + (t->normal.z * norme);
}

sfColor		apply_reflect(t_thread *t, sfColor col)
{
  sfColor	reflect;
  int		i;
  int		idx;

  i = -1;
  prepare_reflect(t);
  idx = t->idx;
  t->dist[t->idx] = FLT_MAX;
  while (++i < t->params->nb_obj)
    if (i != t->idx)
      t->dist[i] = gather_distances(t->params->objs, t->ray, i);
  reflect = color_stuff(t->dist, t);
  col.r = ((float)reflect.r) * t->params->objs[idx].reflect +
    ((float)col.r) * (1.0F - t->params->objs[idx].reflect);
  col.g = ((float)reflect.g) * t->params->objs[idx].reflect +
    ((float)col.g) * (1.0F - t->params->objs[idx].reflect);
  col.b = ((float)reflect.b) * t->params->objs[idx].reflect +
    ((float)col.b) * (1.0F - t->params->objs[idx].reflect);
  col.a = 255;
  return (col);
}

void	get_normal(t_thread *t)
{
  char	type;

  type = t->params->objs[t->idx].type;
  if (type == 'p')
    {
      t->normal.x = 0;
      t->normal.y = 0;
      t->normal.z = 1;
      return ;
    }
  t->normal = t->imp;
  if (type == 'c' || type == 'h')
    get_cylinder_normal(t);
  else if (type == 'x' || type == 'o' || type == 'u')
    get_cone_normal(t);
}

void	get_impact(t_thread *t, float dist)
{
  sub_coords_vect(&t->ray.orig, &t->ray.dir,
                  &(t->params->objs[t->idx]));
  t->imp.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->imp.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->imp.z = t->ray.orig.z + t->ray.dir.z * dist;
  add_coords_vect(&t->ray.orig, &t->ray.dir,
                  &(t->params->objs[t->idx]));
}

