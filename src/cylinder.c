/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Thu Mar 16 10:22:49 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

static float	get_value(float root[2])
{
  if (root[0] > 0)
    if (root[1] > 0)
      return ((root[0] > root[1]) ? root[1] : root[0]);
    else
      return (root[0]);
  else if (root[1] < 0)
    return (-1);
  return (root[1]);
}

float		intersect_cylinder(sfVector3f eye_pos, sfVector3f dir_vector,
				   float radius)
{
  float		a;
  float		b;
  float		c;
  float		delta;
  float		root[2];

  if ((a = powf(dir_vector.x, 2) + powf(dir_vector.y, 2)) == 0)
    return (-1);
  b = (2 * eye_pos.x * dir_vector.x + 2 * eye_pos.y * dir_vector.y);
  c = (powf(eye_pos.x, 2) + powf(eye_pos.y, 2) - powf(radius, 2));
  delta = b * b - 4 * a * c;
  if (delta < 0)
    return (-1.0F);
  else if (delta)
    {
      delta = sqrtf(delta);
      root[0] = (-b - delta) / (2 * a);
      root[1] = (-b + delta) / (2 * a);
      return (get_value(root));
    }
  else if (!delta)
    return (((-b / (2 * a)) < 0) ? -1 : -b / (2 * a));
  return (-1);
}

sfVector3f	get_normal_cylinder(sfVector3f imp)
{
  imp.z = 0;
  return (imp);
}
