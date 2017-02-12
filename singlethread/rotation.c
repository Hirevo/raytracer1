/*
** compense.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Feb  9 13:15:36 2017 Nicolas Polomack
** Last update Sat Feb 11 19:43:18 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include "raytracer.h"

void		rx(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.x = imp->x;
      tmp.y = imp->y * cosr(r) - imp->z * sinr(r);
      tmp.z = imp->y * sinr(r) + imp->z * cosr(r);
      *imp = tmp;
    }
}

void		ry(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.y = imp->y;
      tmp.x = imp->x * cosr(r) + imp->z * sinr(r);
      tmp.z = imp->z * cosr(r) - imp->x * sinr(r);
      *imp = tmp;
    }
}

void		rz(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.z = imp->z;
      tmp.x = imp->x * cosr(r) - imp->y * sinr(r);
      tmp.y = imp->x * sinr(r) + imp->y * cosr(r);
      *imp = tmp;
    }
}

void	rotation(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  rx(imp, obj->rx);
  ry(imp, obj->ry);
  rz(imp, obj->rz);
  if (dir)
    {
      rx(dir, obj->rx);
      ry(dir, obj->ry);
      rz(dir, obj->rz);
    }
}

void	rotation_eye(t_params *params, int i)
{
  if (i < 2)
    {
      rx(&params->ray.orig, params->ray.rx);
      ry(&params->ray.orig, params->ray.ry);
      rz(&params->ray.orig, params->ray.rz);
    }
  if (i > 0)
    {
      rx(&params->ray.dir, params->ray.rx);
      ry(&params->ray.dir, params->ray.ry);
      rz(&params->ray.dir, params->ray.rz);
    }
}
