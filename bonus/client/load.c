/*
** load.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Feb 11 15:15:00 2017 Nicolas Polomack
** Last update Fri Feb 17 03:54:47 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include "sfcaster.h"
#include "get_next_line.h"
#include "raytracer.h"
#include "bmp.h"
#include "my.h"

int	load_assets(t_window *w, t_params *params)
{
  int	fds[2];

  pipe(fds);
  write(fds[1], params->s.scene, my_strlen(params->s.scene));
  close(fds[1]);
  if (parse_config_file(fds[0], params) == -1)
    return (-1);
  params->bmp = 1;
  if ((w->buffer = my_framebuffer_create(params->screen_size.x,
					 params->screen_size.y)) == NULL)
    return (-1);
  return (0);
}
