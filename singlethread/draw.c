/*
** draw.c for wolf3d in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Dec 23 23:47:09 2016 Nicolas Polomack
** Last update Sun Feb  5 14:28:46 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "inter.h"
#include "wolf3d.h"

void		render_view(t_my_framebuffer *buffer,
			    t_params *params, t_window *w)
{
  sfVector2i	view;
  sfVector2f	angle;
  t_raycast	ray;
  int		last[3];

  draw_ground(buffer, params);
  draw_sky(buffer, params);
  angle.x = params->fov / ((params->zoom) ? 5 : 1) / buffer->width;
  view.x = -1;
  last[0] = 0;
  last[1] = 0;
  angle.y = params->direction + (params->fov / ((params->zoom) ? 5 : 1)  / 2);
  while (++(view.x) < buffer->width)
    {
      params->d[view.x] = my_raycast(params, angle.y, &ray) *
        ((params->f_eye) ? 1 : cosr(angle.y - params->direction));
      view.y = ((params->d[view.x] <= 0.1F) ? (buffer->height / 0.1F) *
		((params->zoom) ? 5 : 1) : (buffer->height / params->d[view.x]) *
		((params->zoom) ? 5 : 1));
      w->current = get_current_wall(w, &ray);
      view.y = ((!params->textured) ? draw_walls(w, view, params, last) :
		draw_textured_walls(w, view, params, &ray));
      last[0] = view.y;
      angle.y -= angle.x;
    }
}
