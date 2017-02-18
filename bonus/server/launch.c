/*
** launch.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/bonus
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb 16 16:22:58 2017 Nicolas Polomack
** Last update Sat Feb 18 20:29:25 2017 Nicolas Polomack
*/

#include <errno.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "bmp.h"
#include "raytracer.h"

void	divide_frame(t_params *params, t_window *w)
{
  int	i;

  i = -1;
  while (++i < params->s.nb_clients)
    {
      params->s.offs[i].x = 0;
      params->s.offs[i].y = (w->buffer->height / params->s.nb_clients) * i;
      params->s.end[i].x = w->buffer->width;
      params->s.end[i].y = (w->buffer->height / params->s.nb_clients) * (i + 1);
      params->s.end[i].y += (i == 3) ?
        w->buffer->height % params->s.nb_clients : 0;
    }
}

void	render_frame(t_window *w, t_params *params, char *file)
{
  divide_frame(params, w);
  if ((params->s.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return ;
  prepare_connection(&(params->s), file);
  my_printf("Waiting for connections...\n");
  listen_connections(&(params->s));
  my_printf("All clients are connected, sending start signal...");
  broadcast_start(&params->s);
  my_printf(" OK !\nGathering results:\n");
  gather_results(params, w);
  my_printf("\n--- SCENE COMPLETE ---\n\n");
}

int		main(int ac, char **av)
{
  t_window	w;
  t_params	params;
  sfEvent	event;

  if (ac != 3 || !my_str_isnum(av[2]))
    return (84);
  if (!my_strcmp(av[1], "-h") || !my_strcmp(av[1], "--help"))
    return (disp_guide());
  if (load_assets(&w, &params, av[1]) == -1)
    return (84);
  params.s.nb_clients = my_getnbr(av[2]);
  render_frame(&w, &params, av[1]);
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
    handle_events(&w, &event);
  return (free_all(&params, &w));
}
