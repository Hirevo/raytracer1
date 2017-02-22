/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Tue Feb 21 11:59:13 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sfcaster.h"
#include "raytracer.h"
#include "bmp.h"
#include "my.h"

sfColor		evaluate_luminosity(float *dist, t_thread *t,
				    sfColor col, sfVector2i idxs)
{
  col = set_luminosity((t->params->objs[idxs.x].type == 's') ?
		       get_cos_angle_s(dist[idxs.x], t, idxs) :
		       (t->params->objs[idxs.x].type == 'p') ?
		       get_cos_angle_p(dist[idxs.x], t, idxs) :
		       (t->params->objs[idxs.x].type == 'c' ||
			t->params->objs[idxs.x].type == 'h') ?
		       get_cos_angle_c(dist[idxs.x], t, idxs) :
		       (t->params->objs[idxs.x].type == 'u' ||
			t->params->objs[idxs.x].type == 'o' ||
			t->params->objs[idxs.x].type == 'x') ?
		       get_cos_angle_o(dist[idxs.x], t, idxs) : 1,
		       col, t->params->light[idxs.y].ambient);
  return (col);
}

sfColor		color_stuff(float *dist, t_thread *t)
{
  sfColor       col;
  float         record;
  int           i;

  record = FLT_MAX;
  i = -1;
  while (++i < t->params->nb_obj)
    if (dist[i] < record && dist[i] > 0)
      record = dist[i];
  i = -1;
  t->can_reflect = 0;
  while (++i < t->params->nb_obj)
    if (dist[i] == record)
      {
        col = seek_lights(dist, t, i);
        break;
      }
  if (i == t->params->nb_obj)
    col = BLACK;
  if ((col.r || col.g || col.b))
    {
      t->idx = i;
      t->can_reflect = 1;
    }
  return (col);
}

int	init(t_params *params, t_window *w)
{
  params->ray.dir.x = 0;
  params->ray.dir.y = 0;
  params->ray.dir.z = 0;
  params->progress = 0;
  if (params->t_count == 'x')
    params->t_count = get_core_count() * 2;
  pthread_mutex_init(&w->mutex, NULL);
  pthread_cond_init(&params->cond, NULL);
  pthread_cond_init(&params->start, NULL);
  clear_pixels(w->buffer);
  return (0);
}
