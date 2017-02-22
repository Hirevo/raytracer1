/*
** compense.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 13:15:36 2017 Nicolas Polomack
** Last update Wed Feb 22 02:40:29 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include "raytracer.h"

void	anti_rotation(sfVector3f *restrict imp,
		      sfVector3f *restrict dir, t_obj *obj)
{
  rz(imp, -obj->rz);
  ry(imp, -obj->ry);
  rx(imp, -obj->rx);
  if (dir)
    {
      rz(dir, -obj->rz);
      ry(dir, -obj->ry);
      rx(dir, -obj->rx);
    }
}

void	anti_rotation_eye(t_thread *t)
{
  rz(&t->ray.orig, -t->ray.rz);
  ry(&t->ray.orig, -t->ray.ry);
  rx(&t->ray.orig, -t->ray.rx);
}
