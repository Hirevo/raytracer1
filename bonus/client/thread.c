/*
** thread.c for raytracer in /home/nicolaspolomack/threads/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 12 03:09:48 2017 Nicolas Polomack
** Last update Sat Feb 18 23:30:37 2017 Nicolas Polomack
*/

#include <float.h>
#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

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
          t->ray.dir = calc_dir_vector(t->params->screen_size,
                                       x, y, t->params->fov);
          rotation_t_eye(t);
	  t->can_reflect = 0;
	  i = -1;
	  while (++i < t->params->nb_obj)
	    t->dist[i] = gather_distances(t->params->objs, t->ray, i);
          col = color_stuff(t->dist, t);
	  //if (t->can_reflect && t->params->objs[t->idx].type == 's')
	  //col = apply_reflect(t, col);
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