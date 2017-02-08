/*
** intersect_sphere.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:30:22 2017 Nicolas Polomack
** Last update Wed Feb  8 17:08:47 2017 Nicolas Polomack
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

static float	ret_value(sfVector3f eye_pos, sfVector3f dir_vector,
			  float val, float height)
{
  float	zval;

  if (val == -1)
    return (val);
  zval = eye_pos.z + dir_vector.z * val;
  if (zval < (height/2) && zval > -(height/2))
      return (val);
  return (-1);
}

float		intersect_cone(sfVector3f eye_pos, sfVector3f dir_vector,
			       t_obj obj)
{
  float		a;
  float		b;
  float		c;
  float		delta;
  float		root[2];
  sfVector3f	imp;

  a = powf(dir_vector.x, 2) + powf(dir_vector.y, 2) -
    powf(dir_vector.z, 2) * pow(tanr(obj.aper), 2);
  b = (2 * eye_pos.x * dir_vector.x + 2 * eye_pos.y * dir_vector.y -
       2 * eye_pos.z * dir_vector.z * pow(tanr(obj.aper), 2));
  c = (powf(eye_pos.x, 2) + powf(eye_pos.y, 2) -
       powf(eye_pos.z, 2) * pow(tanr(obj.aper), 2));
  delta = b * b - 4 * a * c;
  if (delta < 0)
    return (-1.0F);
  else
    if (delta)
      {
	root[0] = (-b - sqrtf(delta)) / (2 * a);
	root[1] = (-b + sqrtf(delta)) / (2 * a);
	root[1] = get_value(root);
	if (root[1] == -1 ||
	    ((eye_pos.z + dir_vector.z * root[1]) > 0 && obj.type == 'o'))
	  return (-1);
	return (root[1]);
      }
    else
      return (-b / (2 * a));
}
