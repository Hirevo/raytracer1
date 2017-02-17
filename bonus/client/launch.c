/*
** launch.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/bonus
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb 16 16:22:58 2017 Nicolas Polomack
** Last update Fri Feb 17 12:53:16 2017 Nicolas Polomack
*/

#include <errno.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "bmp.h"
#include "raytracer.h"

int		main(int ac, char **av)
{
  t_window	w;
  t_params	params;

  if (ac != 2)
    return (84);
  if (!my_strcmp(av[1], "-h") || !my_strcmp(av[1], "--help"))
    return (disp_guide());
  if ((params.s.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (84);
  my_printf("Socket created.\nCreating connection...");
  connect_socket(&params.s, av[1]);
  my_printf(" OK !\nLoading scene...");
  if ((load_assets(&w, &params)) == -1)
    return (84);
  init(&params, &w);
  my_printf(" OK !\n");
  render_frame(&w, &params);
  my_printf("Scene rendered.\nSending to server...");
  send_results(&w, &params.s);
  my_printf(" OK !\n");
  return (0);
}
