/*
** thread.c for raytracer in /home/nicolaspolomack/threads/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Feb 12 03:09:48 2017 Nicolas Polomack
** Last update Mon Feb 13 09:18:43 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static void		update_color(t_thread *t)
{
  pthread_mutex_lock(&t->w->mutex);
  sfTexture_updateFromPixels(t->w->texture, t->w->buffer->pixels,
			     t->w->buffer->width, t->w->buffer->height, 0, 0);
  sfRenderWindow_drawSprite(t->w->window, t->w->sprite, NULL);
  sfRenderWindow_display(t->w->window);
  pthread_mutex_unlock(&t->w->mutex);
}

void		render_rect(t_thread *t)
{
  int		x;
  int		y;
  int		i;
  sfColor	col;

  x = t->offs.x - 1;
  while (++x < (t->offs.x + (t->w->buffer->width / (t->params->proc_count))))
    {
      y = t->offs.y - 1;
      while (++y < (t->offs.y + (t->w->buffer->height / 2)))
        {
          t->ray.dir = calc_dir_vector(t->params->screen_size,
                                       x, y, t->params->fov);
          rotation_t_eye(t);
          i = -1;
          while (++i < t->params->nb_obj)
            t->dist[i] = gather_distances(t, i);
          col = color_stuff(t->dist, t);
          pthread_mutex_lock(&t->w->mutex);
	  put_pixel(t->w->buffer, x, y, col);
	  pthread_mutex_unlock(&t->w->mutex);
        }
      if (t->params->live && !t->params->bmp)
	update_color(t);
    }
}

void		*thread_handler(void *arg)
{
  t_thread	*t;

  t = (t_thread *)arg;
  pthread_mutex_lock(&t->w->mutex);
  my_printf("Thread %d draws from (%d,%d) to (%d,%d)\n", t->id,
	    t->offs.x, t->offs.y,
	    t->offs.x + (t->w->buffer->width / (t->params->proc_count)),
	    t->offs.y + (t->w->buffer->height / 2));
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
      params->t[i].offs.x = (params->screen_size.x /
			     (params->proc_count)) * (i / 2);
      params->t[i].offs.y = 0;
    }
  else
    {
      params->t[i].offs.x = (params->screen_size.x /
			     (params->proc_count)) * ((i - 1) / 2);
      params->t[i].offs.y = (params->screen_size.y / 2);
    }
  params->t[i].w = w;
  params->t[i].params = params;
}
