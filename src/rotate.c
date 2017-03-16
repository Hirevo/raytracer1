/*
** translate.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 21:07:05 2017 Nicolas Polomack
** Last update Thu Mar 16 09:06:44 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

void		rx(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.x = imp->x;
      tmp.y = imp->y * cos(r) - imp->z * sin(r);
      tmp.z = imp->y * sin(r) + imp->z * cos(r);
      *imp = tmp;
    }
}

void		ry(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.y = imp->y;
      tmp.x = imp->x * cos(r) + imp->z * sin(r);
      tmp.z = imp->z * cos(r) - imp->x * sin(r);
      *imp = tmp;
    }
}

void		rz(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.z = imp->z;
      tmp.x = imp->x * cos(r) - imp->y * sin(r);
      tmp.y = imp->x * sin(r) + imp->y * cos(r);
      *imp = tmp;
    }
}

sfVector3f	rotate_xyz(sfVector3f imp, sfVector3f r)
{
  rx(&imp, r.x * M_PI / 180.0F);
  ry(&imp, r.y * M_PI / 180.0F);
  rz(&imp, r.z * M_PI / 180.0F);
  return (imp);
}

sfVector3f	rotate_zyx(sfVector3f imp, sfVector3f r)
{
  rz(&imp, r.z * M_PI / 180.0F);
  ry(&imp, r.y * M_PI / 180.0F);
  rx(&imp, r.x * M_PI / 180.0F);
  return (imp);
}
