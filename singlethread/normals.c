/*
** normals.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Feb 10 22:55:04 2017 Nicolas Polomack
** Last update Sat Feb 11 13:46:01 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"
#include "sfcaster.h"

void	get_cone_normal(t_params *params, sfVector2i idxs,
			sfVector3f *imp, float dist)
{
  if (params->objs[idxs.x].type == 'u' &&
      imp->z == -params->objs[idxs.x].height &&
      powf(imp->x, 2) + powf(imp->y, 2) - powf(imp->z, 2) *
      powf(tanr(params->objs[idxs.x].aper), 2) != 0)
    {
      imp->x = 0;
      imp->y = 0;
      imp->z = -100;
      return ;
    }
  imp->x = params->ray.orig.x + params->ray.dir.x * dist;
  imp->y = params->ray.orig.y + params->ray.dir.y * dist;
  imp->z = params->ray.orig.z + params->ray.dir.z * dist;
  if (!roundf(imp->z))
    imp->z = -1;
  imp->z *= -tanr(params->objs[idxs.x].aper);
}

void	get_cylinder_normal(t_params *params, sfVector2i idxs,
			    sfVector3f *imp, float dist)
{
  if (params->objs[idxs.x].type == 'h' &&
      roundf(powf(imp->x, 2) + powf(imp->y, 2)) -
      powf(params->objs[idxs.x].rad, 2) != 0)
    {
      if (roundf(imp->z) == (params->objs[idxs.x].height / 2))
	{
	  imp->x = 0;
	  imp->y = 0;
	  imp->z = 100;
	  return ;
	}
      else if (roundf(imp->z) == -(params->objs[idxs.x].height / 2))
	{
	  imp->x = 0;
	  imp->y = 0;
	  imp->z = -100;
	  return ;
	}
    }
  imp->x = params->ray.orig.x + params->ray.dir.x * dist;
  imp->y = params->ray.orig.y + params->ray.dir.y * dist;
  imp->z = 0;
}
