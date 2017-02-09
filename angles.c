/*
** angles.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Feb  7 23:16:29 2017 Nicolas Polomack
** Last update Thu Feb  9 21:50:02 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"

float		get_cos_angle_s(float dist, t_params *params, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  sub_coords_vect(&params->light[idxs.y].pos, NULL,
		  &(params->objs[idxs.x]));
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = params->ray.orig.z + params->ray.dir.z * dist;
  dir.x = params->light[idxs.y].pos.x - imp.x;
  dir.y = params->light[idxs.y].pos.y - imp.y;
  dir.z = params->light[idxs.y].pos.z - imp.z;
  add_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  add_coords_vect(&params->light[idxs.y].pos, NULL,
		  &(params->objs[idxs.x]));
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_p(float dist, t_params *params, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  sub_coords_vect(&params->light[idxs.y].pos, NULL, &(params->objs[idxs.x]));
  imp.x = 0;
  imp.y = 0;
  imp.z = 100;
  dir.x = params->light[idxs.y].pos.x -
    (params->ray.orig.x + params->ray.dir.x * dist);
  dir.y = params->light[idxs.y].pos.y -
    (params->ray.orig.y + params->ray.dir.y * dist);
  dir.z = params->light[idxs.y].pos.z -
    (params->ray.orig.z + params->ray.dir.z * dist);
  add_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  add_coords_vect(&params->light[idxs.y].pos, NULL,
		  &(params->objs[idxs.x]));
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_c(float dist, t_params *params, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  sub_coords_vect(&params->light[idxs.y].pos, NULL,
		  &(params->objs[idxs.x]));
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = 0;
  dir.x = params->light[idxs.y].pos.x - imp.x;
  dir.y = params->light[idxs.y].pos.y - imp.y;
  dir.z = params->light[idxs.y].pos.z -
    (params->ray.orig.z + params->ray.dir.z * dist);
  add_coords_vect(&params->ray.orig, &params->ray.dir,
		  &(params->objs[idxs.x]));
  add_coords_vect(&params->light[idxs.y].pos, NULL,
		  &(params->objs[idxs.x]));
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}

float		get_cos_angle_o(float dist, t_params *params,
				float aper, sfVector2i idxs)
{
  sfVector3f	imp;
  sfVector3f	dir;

  sub_coords_vect(&params->ray.orig, &params->ray.dir, &(params->objs[idxs.x]));
  sub_coords_vect(&params->light[idxs.y].pos, NULL, &(params->objs[idxs.x]));
  imp.x = params->ray.orig.x + params->ray.dir.x * dist;
  imp.y = params->ray.orig.y + params->ray.dir.y * dist;
  imp.z = params->ray.orig.y + params->ray.dir.y * dist;
  dir.x = params->light[idxs.y].pos.x - imp.x;
  dir.y = params->light[idxs.y].pos.y - imp.y;
  dir.z = params->light[idxs.y].pos.z - imp.z;
  imp.z *= (-tanr(aper));
  add_coords_vect(&params->ray.orig, &params->ray.dir, &(params->objs[idxs.x]));
  add_coords_vect(&params->light[idxs.y].pos, NULL, &(params->objs[idxs.x]));
  return (dot(imp,dir)/(norm(imp)*norm(dir)));
}
