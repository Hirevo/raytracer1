/*
** sftrig.c for mycsfml in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Dec 23 15:12:35 2016 Nicolas Polomack
** Last update Sat Jan 14 17:15:21 2017 Nicolas Polomack
*/

#include <math.h>
#include "sfcaster.h"

float	cosr(float angle)
{
  return (cos(angle * M_PI / 180.0F));
}

float	sinr(float angle)
{
  return (sin(angle * M_PI / 180.0F));
}

float	tanr(float angle)
{
  return (tan(angle * M_PI / 180.0F));
}
