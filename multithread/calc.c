/*
** calc.c for raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 23:10:06 2017 Nicolas Polomack
** Last update Fri Mar 17 11:09:55 2017 Nicolas Polomack
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

float	gather_distances(t_obj *objs, t_ray ray, int i)
{
  float	f;

  sub_coords_vect(&ray.orig, &ray.dir, &(objs[i]));
  f = ((objs[i].type == 's') ?
       intersect_sphere(&ray.orig, &ray.dir,
                        objs[i].rad) :
       ((objs[i].type == 'p') ?
        intersect_plane(&ray.orig, &ray.dir) :
	((objs[i].type == 'c' || objs[i].type == 'h') ?
         intersect_cyl(&ray.orig, &ray.dir,
		       &(objs[i])) :
	 ((objs[i].type == 'o' || objs[i].type == 'x' ||
	   objs[i].type == 'u') ?
	  intersect_cone(&ray.orig, &ray.dir,
			 &(objs[i])) :
	  FLT_MAX))));
  return (f);
}

void	render_frame(t_window *w, t_params *params)
{
  int	i;

  i = -1;
  while (++i < (params->t_count))
    {
      pthread_mutex_lock(&w->mutex);
      init_thread(i, params, w);
      pthread_create(&(params->tid[i]), NULL,
		     thread_handler, params->t + i);
      pthread_cond_wait(&params->cond, &w->mutex);
      pthread_mutex_unlock(&w->mutex);
    }
  pthread_mutex_lock(&w->mutex);
  my_printf("Broadcasting start signal to every thread !\n");
  pthread_mutex_unlock(&w->mutex);
  pthread_cond_broadcast(&params->start);
  i = -1;
  while (++i < (params->t_count))
    {
      pthread_join(params->tid[i], NULL);
      my_printf("Thread %d joined !\n", i);
    }
}
