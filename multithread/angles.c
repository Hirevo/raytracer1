/*
** angles.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Feb  7 23:16:29 2017 Nicolas Polomack
** Last update Fri Mar 17 11:08:27 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"

float		get_cos_angle_s(t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  dir.x = light.x - t->imp.x;
  dir.y = light.y - t->imp.y;
  dir.z = light.z - t->imp.z;
  return (dot(t->normal,dir) / (norm(t->normal) * norm(dir)));
}

float		get_cos_angle_p(t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&light, NULL, &(t->params->objs[t->idx]));
  dir.x = light.x - t->imp.x;
  dir.y = light.y - t->imp.y;
  dir.z = light.z - t->imp.z;
  return (dot(t->normal,dir) / (norm(t->normal) * norm(dir)));
}

float		get_cos_angle_c(t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  dir.x = light.x - t->imp.x;
  dir.y = light.y - t->imp.y;
  dir.z = light.z - t->imp.z;
  return (dot(t->normal,dir) / (norm(t->normal) * norm(dir)));
}

float		get_cos_angle_o(t_thread *t, sfVector2i idxs)
{
  sfVector3f	dir;
  sfVector3f	light;

  light = t->params->light[idxs.y].pos;
  sub_coords_vect(&light, NULL,
		  &(t->params->objs[idxs.x]));
  dir.x = light.x - t->imp.x;
  dir.y = light.y - t->imp.y;
  dir.z = light.z - t->imp.z;
  return (dot(t->normal,dir) / (norm(t->normal) * norm(dir)));
}
