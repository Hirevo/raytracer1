/*
** thread.c for raytracer in /home/nicolaspolomack/threads/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 12 03:09:48 2017 Nicolas Polomack
** Last update Tue Feb 21 12:01:56 2017 Nicolas Polomack
*/

#include <float.h>
#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

void            prepare_reflect(t_thread *t)
{
  float         norme;

  add_coords_vect(&t->normal, NULL, &(t->params->objs[t->idx]));
  t->ray.orig.x = t->ray.orig.x + t->ray.dir.x * t->dist[t->idx];
  t->ray.orig.y = t->ray.orig.y + t->ray.dir.y * t->dist[t->idx];
  t->ray.orig.z = t->ray.orig.z + t->ray.dir.z * t->dist[t->idx];
  norme = norm(t->normal);
  t->normal.x /= norme;
  t->normal.y /= norme;
  t->normal.z /= norme;
  norme = -dot(t->normal, t->ray.dir);
  t->ray.dir.x = t->ray.dir.x + (2.0F * t->normal.x * norme);
  t->ray.dir.y = t->ray.dir.y + (2.0F * t->normal.y * norme);
  t->ray.dir.z = t->ray.dir.z + (2.0F * t->normal.z * norme);
}

sfColor         apply_reflect(t_thread *t, sfColor col)
{
  sfColor       reflect;
  int           i;

  i = -1;
  prepare_reflect(t);
  t->dist[t->idx] = FLT_MAX;
  while (++i < t->params->nb_obj)
    if (i != t->idx)
      t->dist[i] = gather_distances(t->params->objs, t->ray, i);
  reflect = color_stuff(t->dist, t);
  reflect.r = reflect.r * 0.25F +//t->params->objs[t->idx].reflect +
    col.r * (1 - 0.25F);//t->params->objs[t->idx]reflect);
  reflect.g = reflect.g * 0.25F +//t->params->objs[t->idx].reflect +
    col.g * (1 - 0.25F);//t->params->objs[t->idx]reflect);
  reflect.b = reflect.b * 0.25F +//t->params->objs[t->idx].reflect +
    col.b * (1 - 0.25F);//t->params->objs[t->idx]reflect);
  reflect.a = 255;
  return (reflect);
}

void		render_rect(t_thread *t)
{
  int		x;
  int		y;
  int		i;
  sfColor	col;

  x = t->offs.x - 1;
  while (++x < t->end.x)
    {
      y = t->offs.y - 1;
      while (++y < t->end.y)
        {
	  t->ray = t->params->ray;
          t->ray.dir = calc_dir_vector(t->params->screen_size,
                                       x, y, t->params->fov);
          rotation_t_eye(t);
	  t->can_reflect = 0;
	  i = -1;
	  while (++i < t->params->nb_obj)
	    t->dist[i] = gather_distances(t->params->objs, t->ray, i);
          col = color_stuff(t->dist, t);
	  for (int i = 3; i; i--)
	    if (t->can_reflect)
	      col = apply_reflect(t, col);
	  //pthread_mutex_lock(&t->w->mutex);
	  put_pixel(t->w->buffer, x, y, col);
	  //pthread_mutex_unlock(&t->w->mutex);
        }
    }
}

void		*thread_handler(void *arg)
{
  t_thread	*t;

  t = (t_thread *)arg;
  pthread_mutex_lock(&t->w->mutex);
  my_printf("Thread %d draws from (%d,%d) to (%d,%d), %s\n", t->id,
	    t->offs.x, t->offs.y,
	    t->end.x,t->end.y, "waiting for start signal...");
  pthread_cond_signal(&t->params->cond);
  pthread_cond_wait(&t->params->start, &t->w->mutex);
  pthread_mutex_unlock(&t->w->mutex);
  render_rect(t);
  free(t->dist);
  pthread_mutex_lock(&t->w->mutex);
  my_printf("Thread %d finished, waiting to be joined !\n", t->id);
  pthread_mutex_unlock(&t->w->mutex);
  return (NULL);
}

void	init_thread(int i, t_params *params, t_window *w)
{
  params->t[i].id = i;
  params->t[i].ray = params->ray;
  params->t[i].dist = malloc(sizeof(float) * params->nb_obj);
  if (!(i % 2))
    {
      params->t[i].offs.x = ((params->s.end.x - params->s.offs.x) /
			     (params->t_count / 2)) * (i / 2);
      params->t[i].offs.y = params->s.offs.y;
    }
  else
    {
      params->t[i].offs.x = ((params->s.end.x - params->s.offs.x) /
			     (params->t_count / 2)) * ((i - 1) / 2);
      params->t[i].offs.y = params->s.offs.y + ((params->s.end.y - params->s.offs.y) / 2);
    }
  params->t[i].end.x = (params->t[i].offs.x + ((params->s.end.x - params->s.offs.x) /
					       (params->t_count / 2)));
  params->t[i].end.y = (params->t[i].offs.y + ((params->s.end.y - params->s.offs.y) / 2));
  if (i >= (params->t_count - 2) && params->t[i].end.x < params->s.end.x)
    params->t[i].end.x += (params->s.end.x - params->s.offs.x) % (params->t_count / 2);
  params->t[i].w = w;
  params->t[i].params = params;
}
