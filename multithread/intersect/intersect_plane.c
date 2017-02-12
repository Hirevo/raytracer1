/*
** intersect_plane.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:31:08 2017 Nicolas Polomack
** Last update Fri Feb 10 17:32:59 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>

float	intersect_plane(sfVector3f *eye_pos, sfVector3f *dir_vector)
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
