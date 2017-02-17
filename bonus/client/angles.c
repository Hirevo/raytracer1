/*
** angles.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Feb  7 23:16:29 2017 Nicolas Polomack
** Last update Mon Feb 13 23:29:01 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"

float		get_cos_angle_s(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  t->normal.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->normal.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->normal.z = t->ray.orig.z + t->ray.dir.z * dist;
  dir.x = light.x - t->normal.x;
  dir.y = light.y - t->normal.y;
  dir.z = light.z - t->normal.z;
  add_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  add_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  return (dot(t->normal,dir)/(norm(t->normal)*norm(dir)));
}

float		get_cos_angle_p(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  sub_coords_vect(&light, NULL, &(t->params->objs[idxs.x]));
  t->normal.x = 0;
  t->normal.y = 0;
  t->normal.z = 100;
  dir.x = light.x -
    (t->ray.orig.x + t->ray.dir.x * dist);
  dir.y = light.y -
    (t->ray.orig.y + t->ray.dir.y * dist);
  dir.z = light.z -
    (t->ray.orig.z + t->ray.dir.z * dist);
  add_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  add_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  return (dot(t->normal,dir)/(norm(t->normal)*norm(dir)));
}

float		get_cos_angle_c(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  t->normal.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->normal.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->normal.z = t->ray.orig.z + t->ray.dir.z * dist;
  dir.x = light.x - t->normal.x;
  dir.y = light.y - t->normal.y;
  dir.z = light.z - t->normal.z;
  get_cylinder_normal(t, idxs, &(t->normal), dist);
  add_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  add_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  return (dot(t->normal,dir)/(norm(t->normal)*norm(dir)));
}

float		get_cos_angle_o(float dist, t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  t->normal.x = t->ray.orig.x + t->ray.dir.x * dist;
  t->normal.y = t->ray.orig.y + t->ray.dir.y * dist;
  t->normal.z = t->ray.orig.z + t->ray.dir.z * dist;
  dir.x = light.x - t->normal.x;
  dir.y = light.y - t->normal.y;
  dir.z = light.z - t->normal.z;
  get_cone_normal(t, idxs, &t->normal, dist);
  add_coords_vect(&t->ray.orig, &t->ray.dir,
		  &(t->params->objs[idxs.x]));
  add_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  return (dot(t->normal,dir)/(norm(t->normal)*norm(dir)));
}
