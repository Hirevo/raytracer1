/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Thu Feb  9 02:50:07 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"

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

void	calc_abcd(float *abcd, sfVector3f *eye_pos, sfVector3f *dir_vector,
		  t_obj *obj)
{
  abcd[0] = powf(dir_vector->x, 2) + powf(dir_vector->y, 2) -
    powf(dir_vector->z, 2) * pow(tanr(obj->aper), 2);
  abcd[1] = (2 * eye_pos->x * dir_vector->x + 2 * eye_pos->y * dir_vector->y -
             2 * eye_pos->z * dir_vector->z * pow(tanr(obj->aper), 2));
  abcd[2] = (powf(eye_pos->x, 2) + powf(eye_pos->y, 2) -
             powf(eye_pos->z, 2) * pow(tanr(obj->aper), 2));
  abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
}

float		intersect_cone(sfVector3f *eye_pos, sfVector3f *dir_vector,
			       t_obj *obj)
{
  float		abcd[4];
  float		root[2];

  calc_abcd(abcd, eye_pos, dir_vector, obj);
  if (abcd[3] < 0)
    return (-1.0F);
  else
    if (abcd[3])
      {
	root[0] = (-abcd[1] - sqrtf(abcd[3])) / (2 * abcd[0]);
	root[1] = (-abcd[1] + sqrtf(abcd[3])) / (2 * abcd[0]);
	root[1] = get_value(root);
      }
    else
      root[1] = (-abcd[1] / (2 * abcd[0]));
  if (root[1] == -1 ||
      ((eye_pos->z + dir_vector->z * root[1]) > 0 && obj->type == 'o'))
    return (-1);
  return (root[1]);
}
