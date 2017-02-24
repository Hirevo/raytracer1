/*
** lights.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Feb  7 00:16:08 2017 Nicolas Polomack
** Last update Fri Feb 24 09:36:42 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"

void	sub_coords_vect(sfVector3f *restrict imp,
			sfVector3f *restrict dir, t_obj *obj)
{
  imp->x -= obj->pos.x;
  imp->y -= obj->pos.y;
  imp->z -= obj->pos.z;
  anti_rotation(imp, dir, obj);
}

void	add_coords_vect(sfVector3f *restrict imp,
			sfVector3f *restrict dir, t_obj *obj)
{
  rotation(imp, dir, obj);
  imp->x += obj->pos.x;
  imp->y += obj->pos.y;
  imp->z += obj->pos.z;
}

float		check_distance(t_thread *t, sfVector3f *restrict imp,
			       sfVector3f *restrict dir, int n)
{
  float		d;

  sub_coords_vect(imp, dir, &(t->params->objs[n]));
  d = (t->params->objs[n].type == 's') ?
    intersect_sphere(imp, dir, t->params->objs[n].rad) :
    (t->params->objs[n].type == 'p') ? intersect_plane(imp, dir) :
    (t->params->objs[n].type == 'c' || t->params->objs[n].type == 'h') ?
    intersect_cyl(imp, dir, &(t->params->objs[n])) :
    (t->params->objs[n].type == 'o' || t->params->objs[n].type == 'x' ||
     t->params->objs[n].type == 'u') ?
    intersect_cone(imp, dir, &(t->params->objs[n])) : 2;
  add_coords_vect(imp, dir, &(t->params->objs[n]));
  return (d);
}

float		intersect_light(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;
  float		d;
  int		n;

  imp.x = t->ray.orig.x + t->ray.dir.x * dist;
  imp.y = t->ray.orig.y + t->ray.dir.y * dist;
  imp.z = t->ray.orig.z + t->ray.dir.z * dist;
  dir.x = t->params->light[idxs.y].pos.x - imp.x;
  dir.y = t->params->light[idxs.y].pos.y - imp.y;
  dir.z = t->params->light[idxs.y].pos.z - imp.z;
  n = -1;
  while (++n < t->params->nb_obj)
    {
      if (idxs.x == n)
	continue;
      d = check_distance(t, &imp, &dir, n);
      if ((0 < d) && (d < 1))
	return (0);
    }
  return (1);
}

sfColor		set_luminosity(float coef, sfColor col, t_thread *t, int l)
{
  if (coef < 0)
    coef = t->params->ambient;
  else
    coef += t->params->ambient;
  if (coef > 1.0F)
    coef = 1.0F;
  if (coef < 0)
    coef = 0;
  col.r = roundf(((float)col.r) * coef);
  col.g = roundf(((float)col.g) * coef);
  col.b = roundf(((float)col.b) * coef);
  col.a = 255;
  if (coef > t->params->ambient)
    col = set_specular_shade(col, t, l);
  return (col);
}
