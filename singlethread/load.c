/*
** load.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Feb 11 15:15:00 2017 Nicolas Polomack
** Last update Sun Feb 12 16:31:16 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "raytracer.h"
#include "bmp.h"
#include "my.h"

int	load_window(t_window *w, t_params *params)
{
  if (create_window(&(w->window), "Raytracer1",
		    params->screen_size) == -1 ||
      (w->save = load_bmp("../resources/loading.bmp",
			  &(w->save_s), &(w->save_t))) == NULL)
    return (-1);
  sfRenderWindow_drawSprite(w->window, w->save_s, NULL);
  sfRenderWindow_display(w->window);
  sfSprite_destroy(w->save_s);
  sfTexture_destroy(w->save_t);
  free(w->save->pixels);
  free(w->save);
  if ((w->save = load_bmp("../resources/saving.bmp",
                          &(w->save_s), &(w->save_t))) == NULL ||
      (w->buffer = assemble_texture(&w->texture, &w->sprite,
				    params->screen_size.x,
				    params->screen_size.y)) == NULL ||
      init(params) == -1)
    return (-1);
  return (0);
}

int	load_assets(t_window *w, t_params *params, char *file)
{
  if (parse_config_file(file, params) == -1)
    return (-1);
  if (params->screen_size.x > 8192 ||
      params->screen_size.y > 8192)
    {
      params->bmp = 1;
      my_printf("Resolution too high for a window to be created\n%s\n",
                "Directly saving the rendered frame in capture.bmp");
      if ((w->buffer = my_framebuffer_create(params->screen_size.x,
                                             params->screen_size.y)) == NULL ||
          init(params) == -1)
        return (-1);
      return (0);
    }
  params->bmp = 0;
  if (load_window(w, params) == -1)
    return (-1);
  return (0);
}
