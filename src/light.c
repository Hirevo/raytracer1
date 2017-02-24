/*
** get_light_coef.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 20:54:49 2017 Nicolas Polomack
** Last update Mon Feb 13 21:41:14 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

static float	norm(sfVector3f v)
{
  return (sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2)));
}

static float	dot(sfVector3f v1, sfVector3f v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	get_light_coef(sfVector3f light, sfVector3f imp)
{
  float	coef;

  coef = dot(light, imp) / (norm(light) * norm(imp));
  if (coef < 0)
    coef = 0;
  return (coef);
}
