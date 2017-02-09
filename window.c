/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Thu Feb  9 03:41:38 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "sfcaster.h"
#include "raytracer.h"
#include "bmp.h"

int	create_window(sfRenderWindow **w, char *name)
{
  sfVideoMode   mode;

  mode.width = WIDTH;
  mode.height = HEIGHT;
  mode.bitsPerPixel = 32;
  *w = sfRenderWindow_create(mode, name, sfClose, NULL);
  if (*w == NULL)
    return (-1);
  return (0);
}

sfColor		evaluate_luminosity(float *dist, t_params *params,
				    sfColor col, int i)
{
  col = set_luminosity((params->objs[i].type == 's') ?
		       get_cos_angle_s(dist[i], params, i) :
		       (params->objs[i].type == 'p') ?
		       get_cos_angle_p(dist[i], params, i) :
		       (params->objs[i].type == 'c') ?
		       get_cos_angle_c(dist[i], params, i) :
		       (params->objs[i].type == 'o' || params->objs[i].type == 'x') ?
		       get_cos_angle_o(dist[i], params,
				       params->objs[i].aper, i) : 1,
		       col, params->ambient);
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
	col = intersect_light(dist[i], params, i) ?
	  params->objs[i].col : sfBlack;
	if (col.r || col.g || col.b)
	  {
	    col = evaluate_luminosity(dist, params, col, i);
	  }
	break;
      }
  if ((!col.r && !col.g && !col.b))
    col = set_luminosity(0.0F, params->objs[i].col, params->ambient);
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
  //sfEvent		event;
  t_params		params;

  if (ac != 2)
    return (84);
  if ((w.buffer = my_framebuffer_create(WIDTH, HEIGHT)) ==//assemble_texture(&w.texture, &w.sprite, WIDTH, HEIGHT)) ==
      NULL || //create_window(&w.window, "Raytracer1") == -1 ||
      parse_config_file(av[1], &params) == -1 || init(&params) == -1)
    return (84);
  render_frame(&w, &params);
  //sfRenderWindow_drawSprite(w.window, w.sprite, NULL);
  //sfRenderWindow_display(w.window);
  //while (sfRenderWindow_isOpen(w.window))
  //handle_events(w.window, &event, &params);
  save_bmp(w.buffer, "capture.bmp");
  return (0);
}
