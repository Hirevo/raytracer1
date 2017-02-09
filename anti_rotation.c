/*
** compense.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 13:15:36 2017 Nicolas Polomack
** Last update Thu Feb  9 17:53:47 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include "raytracer.h"

void		anti_rx(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  sfVector3f	tmp;

  if (obj->rx)
    {
      tmp.x = imp->x;
      tmp.y = imp->y * cosr(-obj->rx) - imp->z * sinr(-obj->rx);
      tmp.z = imp->y * sinr(-obj->rx) + imp->z * cosr(-obj->rx);
      *imp = tmp;
      if (dir)
        {
          tmp.x = dir->x;
          tmp.y = dir->y * cosr(-obj->rx) - dir->z * sinr(-obj->rx);
          tmp.z = dir->y * sinr(-obj->rx) + dir->z * cosr(-obj->rx);
          *dir = tmp;
        }
    }
}

void		anti_ry(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  sfVector3f	tmp;

  if (obj->ry)
    {
      tmp.y = imp->y;
      tmp.x = imp->x * cosr(-obj->ry) + imp->z * sinr(-obj->ry);
      tmp.z = imp->z * cosr(-obj->ry) - imp->x * sinr(-obj->ry);
      *imp = tmp;
      if (dir)
        {
	  tmp.y = dir->y;
	  tmp.x = dir->x * cosr(-obj->ry) + dir->z * sinr(-obj->ry);
	  tmp.z = dir->z * cosr(-obj->ry) - dir->x * sinr(-obj->ry);
          *dir = tmp;
        }
    }
}

void		anti_rz(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  sfVector3f	tmp;

  if (obj->rz)
    {
      tmp.z = imp->z;
      tmp.x = imp->x * cosr(-obj->rz) - imp->y * sinr(-obj->rz);
      tmp.y = imp->x * sinr(-obj->rz) + imp->y * cosr(-obj->rz);
      *imp = tmp;
      if (dir)
        {
          tmp.z = dir->z;
	  tmp.x = dir->x * cosr(-obj->rz) - dir->y * sinr(-obj->rz);
	  tmp.y = dir->x * sinr(-obj->rz) + dir->y * cosr(-obj->rz);
	  *dir = tmp;
        }
    }
}

void	anti_rotation(sfVector3f *imp, sfVector3f *dir, t_obj *obj)
{
  anti_rz(imp, dir, obj);
  anti_ry(imp, dir, obj);
  anti_rx(imp, dir, obj);
}
