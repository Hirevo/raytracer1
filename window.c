/*
** bs.c for bootstrap raytracer in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 14:08:22 2017 Nicolas Polomack
** Last update Tue Feb  7 23:15:42 2017 Nicolas Polomack
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

  mode.width = 1280;
  mode.height = 720;
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
		       (params->objs[i].type == 'o') ?
		       get_cos_angle_o(dist[i], params,
				       params->objs[i].aper, i) : 1,
		       col);
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
	    break;
	  }
      }
  if (i == params->nb_obj)
    col = sfBlack;
  return (col);
}

void	init(t_params *params)
{
  params->ray.orig.x = -200;
  params->ray.orig.y = 0;
  params->ray.orig.z = 40;
  params->ray.dir.x = 0;
  params->ray.dir.y = 0;
  params->ray.dir.z = 0;
  params->screen_size.x = 1280;
  params->screen_size.y = 720;
  params->light.x = -200;
  params->light.y = 0;
  params->light.z = 100;
  params->nb_obj = 5;
  params->objs = malloc(sizeof(t_obj) * params->nb_obj);
  params->objs[0].type = 's';
  params->objs[0].pos.x = 0;
  params->objs[0].pos.y = 0;
  params->objs[0].pos.z = 0;
  params->objs[0].rad = 50;
  params->objs[0].col = RED;
  params->objs[1].type = 'p';
  params->objs[1].pos.x = 0;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = -25;
  params->objs[1].col = sfWhite;
  params->objs[2].type = 's';
  params->objs[2].pos.x = 0;
  params->objs[2].pos.y = 10;
  params->objs[2].pos.z = 100;
  params->objs[2].rad = 25;
  params->objs[2].col = BLUE;
  params->objs[3].type = 'c';
  params->objs[3].pos.x = -50;
  params->objs[3].pos.y = -75;
  params->objs[3].pos.z = 0;
  params->objs[3].rad = 10;
  params->objs[3].col = DARK_BLUE;
  params->objs[4].type = 'o';
  params->objs[4].pos.x = -50;
  params->objs[4].pos.y = 75;
  params->objs[4].pos.z = 30;
  params->objs[4].aper = 25;
  params->objs[4].col = GREEN;
}

int			main(int ac, char **av)
{
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;
  sfEvent		event;
  t_my_framebuffer	*buffer;
  t_params		params;

  buffer = assemble_texture(&texture, &sprite, 1280, 720);
  create_window(&window, "Bootstrap Raytracer");
  init(&params);
  render_frame(buffer, &params);
  sfTexture_updateFromPixels(texture, buffer->pixels,
			     buffer->width, buffer->height, 0, 0);
  while (sfRenderWindow_isOpen(window))
    {
      render_frame(buffer, &params);
      sfTexture_updateFromPixels(texture, buffer->pixels,
				 buffer->width, buffer->height, 0, 0);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
      handle_events(window, &event, &params);
    }
  save_bmp(buffer, "capture.bmp");
  return (0);
}
