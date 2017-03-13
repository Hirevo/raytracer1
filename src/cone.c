/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Thu Mar  9 18:58:47 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdlib.h>
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

float		intersect_cone(sfVector3f eye_pos, sfVector3f dir_vector,
			       float semiangle)
{
  float		abcd[4];
  float		root[2];

  if (abs(fmodf(semiangle, 180)) == 90)
    return (-1);
  abcd[0] = powf(dir_vector.x, 2) + powf(dir_vector.y, 2) -
    powf(dir_vector.z, 2) * pow(tan(semiangle * M_PI / 180.0F), 2);
  abcd[1] = (2 * eye_pos.x * dir_vector.x + 2 * eye_pos.y * dir_vector.y -
             2 * eye_pos.z * dir_vector.z *
	     pow(tan(semiangle * M_PI / 180.0F), 2));
  abcd[2] = (powf(eye_pos.x, 2) + powf(eye_pos.y, 2) -
             powf(eye_pos.z, 2) * pow(tan(semiangle * M_PI / 180.0F), 2));
  abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
  if (abcd[3] < 0)
    return (-1.0F);
  else if (abcd[3])
    {
      root[0] = (-abcd[1] - sqrtf(abcd[3])) / (2 * abcd[0]);
      root[1] = (-abcd[1] + sqrtf(abcd[3])) / (2 * abcd[0]);
      return (get_value(root));
    }
  else if (!(abcd[3]))
    return (-abcd[1] / (2 * abcd[0]));
  return (-1);
}

sfVector3f	get_normal_cone(sfVector3f imp, float semiangle)
{
  if (abs(fmodf(semiangle, 180)) == 90)
    return (imp);
  imp.z *= tan(semiangle * M_PI / 180.0F);
  return (imp);
}
