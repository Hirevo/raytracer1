/*
** compense.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 13:15:36 2017 Nicolas Polomack
** Last update Sat Feb 11 02:47:01 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include "raytracer.h"

void	anti_rotation(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
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

void	anti_rotation_eye(t_params *params)
{
  rz(&params->ray.orig, -params->ray.rz);
  ry(&params->ray.orig, -params->ray.ry);
  rx(&params->ray.orig, -params->ray.rx);
}
