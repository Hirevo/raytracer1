/*
** angles.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 23:16:29 2017 Nicolas Polomack
** Last update Tue Feb  7 23:19:03 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"

float		get_cos_angle_s(float dist, t_params *params, int i)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, params->objs[i]);
  sub_coords_vect(&params->light, params->objs[i]);
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = params->ray.orig.z + params->ray.dir.z * dist;
  dir.x = params->light.x - imp.x;
  dir.y = params->light.y - imp.y;
  dir.z = params->light.z - imp.z;
  add_coords_vect(&params->ray.orig, params->objs[i]);
  add_coords_vect(&params->light, params->objs[i]);
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_p(float dist, t_params *params, int i)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, params->objs[i]);
  sub_coords_vect(&params->light, params->objs[i]);
  imp.x = 0;
  imp.y = 0;
  imp.z = 100;
  dir.x = params->light.x - (params->ray.orig.x + params->ray.dir.x * dist);
  dir.y = params->light.y - (params->ray.orig.y + params->ray.dir.y * dist);
  dir.z = params->light.z - (params->ray.orig.z + params->ray.dir.z * dist);
  add_coords_vect(&params->ray.orig, params->objs[i]);
  add_coords_vect(&params->light, params->objs[i]);
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_c(float dist, t_params *params, int i)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, params->objs[i]);
  sub_coords_vect(&params->light, params->objs[i]);
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = 0;
  dir.x = params->light.x - (params->ray.orig.x + params->ray.dir.x * dist);
  dir.y = params->light.y - (params->ray.orig.y + params->ray.dir.y * dist);
  dir.z = params->light.z - (params->ray.orig.z + params->ray.dir.z * dist);
  add_coords_vect(&params->ray.orig, params->objs[i]);
  add_coords_vect(&params->light, params->objs[i]);
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_o(float dist, t_params *params, float aper, int i)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, params->objs[i]);
  sub_coords_vect(&params->light, params->objs[i]);
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = params->ray.orig.y + params->ray.dir.y * dist;
  dir.x = params->light.x - (params->ray.orig.x + params->ray.dir.x * dist);
  dir.y = params->light.y - (params->ray.orig.y + params->ray.dir.y * dist);
  dir.z = params->light.z - (params->ray.orig.z + params->ray.dir.z * dist);
  imp.z *= (-tanr(aper));
  add_coords_vect(&params->ray.orig, params->objs[i]);
  add_coords_vect(&params->light, params->objs[i]);
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

