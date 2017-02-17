/*
** sfraytracer.c for mycsfml in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:33:15 2017 Nicolas Polomack
** Last update Thu Feb 16 14:59:56 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

float	norm(sfVector3f v1)
{
  return (sqrtf(powf(v1.x,2) + powf(v1.y,2) + powf(v1.z,2)));
}

float	dot(sfVector3f v1, sfVector3f v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
