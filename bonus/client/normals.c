/*
** normals.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Fri Feb 10 22:55:04 2017 Nicolas Polomack
** Last update Wed Feb 22 01:41:09 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"
#include "sfcaster.h"

void	get_cone_normal(t_thread *t)
{
  if (t->params->objs[t->idx].type == 'u' &&
      roundf(t->normal.z) == (-t->params->objs[t->idx].height))
    {
      t->normal.x = 0;
      t->normal.y = 0;
      t->normal.z = -100;
      return ;
    }
  t->normal.z *= -tanr(t->params->objs[t->idx].aper);
}

void	get_cylinder_normal(t_thread *t)
{
  if (t->params->objs[t->idx].type == 'h' &&
      roundf(powf(t->normal.x, 2) + powf(t->normal.y, 2) -
	     powf(t->params->objs[t->idx].rad, 2)) != 0)
    {
      if (roundf(t->normal.z) == (t->params->objs[t->idx].height / 2))
	{
	  t->normal.x = 0;
	  t->normal.y = 0;
	  t->normal.z = 100;
	  return ;
	}
      else if (roundf(t->normal.z) == -(t->params->objs[t->idx].height / 2))
	{
	  t->normal.x = 0;
	  t->normal.y = 0;
	  t->normal.z = -100;
	  return ;
	}
    }
  t->normal.z = 0;
}
