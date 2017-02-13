/*
** calc.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 23:10:06 2017 Nicolas Polomack
** Last update Mon Feb 13 00:40:02 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <float.h>
#include "sfcaster.h"
#include "raytracer.h"
#include "my.h"

void	sub_coords(t_thread *t, t_obj *obj)
{
  t->ray.orig.x -= obj->pos.x;
  t->ray.orig.y -= obj->pos.y;
  t->ray.orig.z -= obj->pos.z;
  anti_rotation(&t->ray.orig, &t->ray.dir, obj);
}

void	add_coords(t_thread *t, t_obj *obj)
{
  rotation(&t->ray.orig, &t->ray.dir, obj);
  t->ray.orig.x += obj->pos.x;
  t->ray.orig.y += obj->pos.y;
  t->ray.orig.z += obj->pos.z;
}

float	gather_distances(t_thread *t, int i)
{
  float	f;

  sub_coords(t, &(t->params->objs[i]));
  f = ((t->params->objs[i].type == 's') ?
       intersect_sphere(&t->ray.orig, &t->ray.dir,
                        t->params->objs[i].rad) :
       ((t->params->objs[i].type == 'p') ?
        intersect_plane(&t->ray.orig, &t->ray.dir) :
	((t->params->objs[i].type == 'c' || t->params->objs[i].type == 'h') ?
         intersect_cyl(&t->ray.orig, &t->ray.dir,
		       &(t->params->objs[i])) :
	 ((t->params->objs[i].type == 'o' || t->params->objs[i].type == 'x' ||
	   t->params->objs[i].type == 'u') ?
	  intersect_cone(&t->ray.orig, &t->ray.dir,
			 &(t->params->objs[i])) :
	  FLT_MAX))));
  add_coords(t, &(t->params->objs[i]));
  return (f);
}

void		render_frame(t_window *w, t_params *params)
{
  int	i;

  i = -1;
  clear_pixels(w->buffer);
  pthread_mutex_init(&w->mutex, NULL);
  while (++i < (params->proc_count * 2))
    {
      init_thread(i, params, w);
      pthread_create(&(params->tid[i]), NULL,
		     thread_handler, params->t + i);
    }
  i = -1;
  while (++i < (params->proc_count * 2))
    {
      pthread_join(params->tid[i], NULL);
      my_printf("Thread %d joined !\n", i);
    }
}
