/*
** lights.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Feb  7 00:16:08 2017 Nicolas Polomack
** Last update Thu Feb  9 21:26:56 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include "raytracer.h"
#include "sfcaster.h"

void	sub_coords_vect(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  imp->x -= obj->pos.x;
  imp->y -= obj->pos.y;
  imp->z -= obj->pos.z;
  anti_rotation(imp, dir, obj);
}

void	add_coords_vect(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  rotation(imp, dir, obj);
  imp->x += obj->pos.x;
  imp->y += obj->pos.y;
  imp->z += obj->pos.z;
}

float		check_distance(t_params *params, sfVector3f *imp,
			       sfVector3f *dir, int n)
{
  float		d;

  sub_coords_vect(imp, dir, &(params->objs[n]));
  d = (params->objs[n].type == 's') ?
    intersect_sphere(imp, dir, params->objs[n].rad) :
    (params->objs[n].type == 'p') ? intersect_plane(imp, dir) :
    (params->objs[n].type == 'c') ?
    intersect_cyl(imp, dir, &(params->objs[n])) :
    (params->objs[n].type == 'o' || params->objs[n].type == 'x') ?
    intersect_cone(imp, dir, &(params->objs[n])) :
    2;
  add_coords_vect(imp, dir, &(params->objs[n]));
  return (d);
}

float		intersect_light(float dist, t_params *params, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;
  float		d;
  int		n;

  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = params->ray.orig.z + params->ray.dir.z * dist;
  dir.x = params->light[idxs.y].pos.x - imp.x;
  dir.y = params->light[idxs.y].pos.y - imp.y;
  dir.z = params->light[idxs.y].pos.z - imp.z;
  n = -1;
  while (++n < params->nb_obj)
    {
      if (idxs.x == n)
	continue;
      d = check_distance(params, &imp, &dir, n);
      if ((0 < d) && (d < 1))
	return (0);
    }
  return (1);
}

sfColor		set_luminosity(float coef, sfColor col, float ambient)
{
  if (coef < 0)
    coef = 0;
  else
    coef = ambient + coef;
  if (coef > 1.0F)
    coef = 1.0F;
  if (coef < 0)
    coef = 0;
  col.r = roundf(((float)col.r) * coef);
  col.g = roundf(((float)col.g) * coef);
  col.b = roundf(((float)col.b) * coef);
  col.a = 255;
  return (col);
}
