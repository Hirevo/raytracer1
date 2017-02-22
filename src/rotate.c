/*
** translate.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 21:07:05 2017 Nicolas Polomack
** Last update Wed Feb 22 02:45:07 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

sfVector3f	rx(sfVector3f imp, float r)
{
  sfVector3f	tmp;

  tmp.x = imp.x;
  tmp.y = imp.y * cos(r) - imp.z * sin(r);
  tmp.z = imp.y * sin(r) + imp.z * cos(r);
  return (tmp);
}

sfVector3f	ry(sfVector3f imp, float r)
{
  sfVector3f	tmp;

  tmp.y = imp.y;
  tmp.x = imp.x * cos(r) + imp.z * sin(r);
  tmp.z = imp.z * cos(r) - imp.x * sin(r);
  return (tmp);
}

sfVector3f	rz(sfVector3f imp, float r)
{
  sfVector3f	tmp;

  tmp.z = imp.z;
  tmp.x = imp.x * cos(r) - imp.y * sin(r);
  tmp.y = imp.x * sin(r) + imp.y * cos(r);
  return (tmp);
}

sfVector3f	rotation_xyz(sfVector3f imp, sfVector3f r)
{
  rx(imp, r.x * M_PI / 180.0F);
  ry(imp, r.y * M_PI / 180.0F);
  rz(imp, r.z * M_PI / 180.0F);
  return (imp);
}

sfVector3f	rotation_zyx(sfVector3f imp, sfVector3f r)
{
  rz(imp, r.z * M_PI / 180.0F);
  ry(imp, r.y * M_PI / 180.0F);
  rx(imp, r.x * M_PI / 180.0F);
  return (imp);
}
