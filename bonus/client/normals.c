/*
** normals.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Feb 10 22:55:04 2017 Nicolas Polomack
** Last update Sun Feb 12 02:47:38 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"
#include "sfcaster.h"

void	get_cone_normal(t_thread *t, sfVector2i idxs,
			sfVector3f *imp, float dist)
{
  if (t->params->objs[idxs.x].type == 'u' &&
      imp->z == -t->params->objs[idxs.x].height &&
      powf(imp->x, 2) + powf(imp->y, 2) - powf(imp->z, 2) *
      powf(tanr(t->params->objs[idxs.x].aper), 2) != 0)
    {
      imp->x = 0;
      imp->y = 0;
      imp->z = -100;
      return ;
    }
  imp->x = t->ray.orig.x + t->ray.dir.x * dist;
  imp->y = t->ray.orig.y + t->ray.dir.y * dist;
  imp->z = t->ray.orig.z + t->ray.dir.z * dist;
  if (!roundf(imp->z))
    imp->z = -1;
  imp->z *= -tanr(t->params->objs[idxs.x].aper);
}

void	get_cylinder_normal(t_thread *t, sfVector2i idxs,
			    sfVector3f *imp, float dist)
{
  if (t->params->objs[idxs.x].type == 'h' &&
      roundf(powf(imp->x, 2) + powf(imp->y, 2)) -
      powf(t->params->objs[idxs.x].rad, 2) != 0)
    {
      if (roundf(imp->z) == (t->params->objs[idxs.x].height / 2))
	{
	  imp->x = 0;
	  imp->y = 0;
	  imp->z = 100;
	  return ;
	}
      else if (roundf(imp->z) == -(t->params->objs[idxs.x].height / 2))
	{
	  imp->x = 0;
	  imp->y = 0;
	  imp->z = -100;
	  return ;
	}
    }
  imp->x = t->ray.orig.x + t->ray.dir.x * dist;
  imp->y = t->ray.orig.y + t->ray.dir.y * dist;
  imp->z = 0;
}
