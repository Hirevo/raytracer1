/*
** reflect.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Feb 22 02:28:54 2017 Nicolas Polomack
** Last update Sun Feb 26 14:11:44 2017 Nicolas Polomack
*/

#include <math.h>
#include <float.h>
#include "raytracer.h"
#include "sfcaster.h"

void		prepare_reflect(t_thread *t)
{
  float		norme;

  rotation(&t->normal, NULL, &(t->params->objs[t->idx]));
  t->ray.orig.x = t->ray.orig.x + t->ray.dir.x * t->dist[t->idx];
  t->ray.orig.y = t->ray.orig.y + t->ray.dir.y * t->dist[t->idx];
  t->ray.orig.z = t->ray.orig.z + t->ray.dir.z * t->dist[t->idx];
  t->normal = normalize(t->normal);
  t->ray.dir = normalize(t->ray.dir);
  norme = -dot(t->normal, t->ray.dir);
  t->ray.dir.x = t->ray.dir.x + (2.0F * t->normal.x * norme);
  t->ray.dir.y = t->ray.dir.y + (2.0F * t->normal.y * norme);
  t->ray.dir.z = t->ray.dir.z + (2.0F * t->normal.z * norme);
}

float		get_specular_coef(t_thread *t, int l)
{
  float		norme;
  sfVector3f	n;
  sfVector3f	reflect;

  n = t->normal;
  rotation(&n, NULL, &(t->params->objs[t->idx]));
  add_coords_vect(&t->imp, NULL, &(t->params->objs[t->idx]));
  n = normalize(n);
  reflect = t->imp;
  reflect.x -= t->params->light[l].pos.x;
  reflect.y -= t->params->light[l].pos.y;
  reflect.z -= t->params->light[l].pos.z;
  norme = -dot(n, reflect);
  reflect.x = reflect.x + (2.0F * n.x * norme);
  reflect.y = reflect.y + (2.0F * n.y * norme);
  reflect.z = reflect.z + (2.0F * n.z * norme);
  n = t->ray.orig;
  n.x -= t->imp.x;
  n.y -= t->imp.y;
  n.z -= t->imp.z;
  n = normalize(n);
  reflect = normalize(reflect);
  sub_coords_vect(&t->imp, NULL, &(t->params->objs[t->idx]));
  return (powf(dot(reflect, n), 50));
}

sfColor		set_specular_shade(sfColor col, t_thread *t, int l)
{
  float		coef;
  int		i[3];

  coef = get_specular_coef(t, l);
  i[0] = (((float)col.r) + 255.0F * fmax(0, coef));
  i[1] = (((float)col.g) + 255.0F * fmax(0, coef));
  i[2] = (((float)col.b) + 255.0F * fmax(0, coef));
  if (i[0] > 255)
    i[0] = 255;
  if (i[1] > 255)
    i[1] = 255;
  if (i[2] > 255)
    i[2] = 255;
  col.r = i[0];
  col.g = i[1];
  col.b = i[2];
  col.a = 255;
  return (col);
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
