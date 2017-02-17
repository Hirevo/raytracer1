/*
** intersect_plane.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:31:08 2017 Nicolas Polomack
** Last update Tue Feb 14 18:42:29 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include <SFML/Graphics.h>

float	dep_intersect_plane(sfVector3f *eye_pos, sfVector3f *dir_vector)
{
  float	k;

  if (!(dir_vector->z))
    if (eye_pos->z != 0)
      return (-1);
    else
      return (0);
  else
    {
      k = (-eye_pos->z / dir_vector->z);
      return ((k < 0) ? -1 : k);
    }
}

float		intersect_plane(sfVector3f *eye_pos, sfVector3f *dir_vector)
{
  float		k;
  float		dot_ln;
  sfVector3f	normal;
  sfVector3f	oppose;

  normal.x = 0;
  normal.y = 0;
  normal.z = 1;
  dot_ln = dot(normal, *dir_vector);
  if (!(dot_ln))
    if (eye_pos->z != 0)
      return (-1);
    else
      return (0);
  else
    {
      oppose.x = -eye_pos->x;
      oppose.y = -eye_pos->y;
      oppose.z = -eye_pos->z;
      k = dot(normal, oppose) / dot_ln;
      return (k);
    }
}
