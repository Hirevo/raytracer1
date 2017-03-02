/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Tue Feb 28 15:33:48 2017 Nicolas Polomack
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

int		create_window(sfRenderWindow **w, char *name, sfVector2i screen_size)
{
  sfVideoMode	mode;

  mode.width = screen_size.x;
  mode.height = screen_size.y;
  mode.bitsPerPixel = 32;
  *w = sfRenderWindow_create(mode, name, sfClose, NULL);
  if (*w == NULL)
    return (-1);
  return (0);
}

sfColor		evaluate_luminosity(t_thread *t,
				    sfColor col, sfVector2i idxs)
{
  col = set_luminosity((t->params->objs[idxs.x].type == 's') ?
		       get_cos_angle_s(t, idxs) :
		       (t->params->objs[idxs.x].type == 'p') ?
		       get_cos_angle_p(t, idxs) :
		       (t->params->objs[idxs.x].type == 'c' ||
			t->params->objs[idxs.x].type == 'h') ?
		       get_cos_angle_c(t, idxs) :
		       (t->params->objs[idxs.x].type == 'u' ||
			t->params->objs[idxs.x].type == 'o' ||
			t->params->objs[idxs.x].type == 'x') ?
		       get_cos_angle_o(t, idxs) : 1,
		       col, t, idxs.y);
  return (col);
}

sfColor		color_stuff(float *dist, t_thread *t)
{
  sfColor	col;
  float		record;
  int		i;

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
	t->can_reflect = 1;
	t->idx = i;
	get_impact(t, dist[i]);
	get_normal(t);
	col = seek_lights(dist, t, i);
        break;
      }
  if (i == t->params->nb_obj)
    col = sfBlack;
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
  if (!params->bmp)
    sfTexture_updateFromPixels(w->texture, w->buffer->pixels,
			       w->buffer->width, w->buffer->height, 0, 0);
  srand(getpid() * time(NULL));
  return (0);
}

int			main(int ac, char **av, char **ae)
{
  t_window		w;
  sfEvent		event;
  t_params		params;

  if (ac != 2)
    return (84);
  if (!my_strcmp(av[1], "-h") || !my_strcmp(av[1], "--help"))
    return (disp_guide());
  if (load_assets(&w, &params, av[1]) == -1)
    return (84);
  params.seed = init_seed(ac, av, ae, (void *)&main);
  init(&params, &w);
  render_frame(&w, &params);
  if (params.bmp)
    {
      save_bmp(w.buffer, "capture.bmp");
      return (free_all(&params, &w));
    }
  sfTexture_updateFromPixels(w.texture, w.buffer->pixels,
			     w.buffer->width, w.buffer->height, 0, 0);
  sfRenderWindow_drawSprite(w.window, w.sprite, NULL);
  sfRenderWindow_display(w.window);
  while (sfRenderWindow_isOpen(w.window))
    handle_events(&w, &event, &params);
  return (free_all(&params, &w));
}
