/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Thu Feb  9 22:00:52 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sfcaster.h"
#include "raytracer.h"
#include "bmp.h"

int		create_window(sfRenderWindow **w, char *name)
{
  sfVideoMode	mode;

  mode.width = WIDTH;
  mode.height = HEIGHT;
  mode.bitsPerPixel = 32;
  *w = sfRenderWindow_create(mode, name, sfClose, NULL);
  if (*w == NULL)
    return (-1);
  return (0);
}

sfColor		evaluate_luminosity(float *dist, t_params *params,
				    sfColor col, sfVector2i idxs)
{
  col = set_luminosity((params->objs[idxs.x].type == 's') ?
		       get_cos_angle_s(dist[idxs.x], params, idxs) :
		       (params->objs[idxs.x].type == 'p') ?
		       get_cos_angle_p(dist[idxs.x], params, idxs) :
		       (params->objs[idxs.x].type == 'c') ?
		       get_cos_angle_c(dist[idxs.x], params, idxs) :
		       (params->objs[idxs.x].type == 'o' ||
			params->objs[idxs.x].type == 'x') ?
		       get_cos_angle_o(dist[idxs.x], params,
				       params->objs[idxs.x].aper, idxs) : 1,
		       col, params->light[idxs.y].ambient);
  return (col);
}

sfColor		color_stuff(float *dist, t_params *params)
{
  sfColor	col;
  float		record;
  int		i;

  record = FLT_MAX;
  i = -1;
  while (++i < params->nb_obj)
    if (dist[i] < record && dist[i] > 0)
      record = dist[i];
  i = -1;
  while (++i < params->nb_obj)
    if (dist[i] == record)
      {
	col = seek_lights(dist, params, i);
        break;
      }
  if ((!col.r && !col.g && !col.b))
    col = sfBlack;
  if (i == params->nb_obj)
    col = sfBlack;
  return (col);
}

int	init(t_params *params)
{
  params->ray.dir.x = 0;
  params->ray.dir.y = 0;
  params->ray.dir.z = 0;
  params->screen_size.x = WIDTH;
  params->screen_size.y = HEIGHT;
  if ((params->dist = malloc(sizeof(float) * params->nb_obj)) == NULL)
    return (-1);
  return (0);
}

int			main(int ac, char **av)
{
  t_window		w;
  sfEvent		event;
  t_params		params;

  if (ac != 2)
    return (84);
  if ((w.buffer = assemble_texture(&w.texture, &w.sprite, WIDTH, HEIGHT)) ==
      NULL || create_window(&w.window, "Raytracer1") == -1 ||
      parse_config_file(av[1], &params) == -1 || init(&params) == -1)
    return (84);
  render_frame(&w, &params);
  sfRenderWindow_drawSprite(w.window, w.sprite, NULL);
  sfRenderWindow_display(w.window);
  while (sfRenderWindow_isOpen(w.window))
    handle_events(w.window, &event, &params);
  save_bmp(w.buffer, "capture.bmp");
  return (0);
}
