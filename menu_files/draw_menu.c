/*
** draw_menu.c for wolf3d in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Jan 12 04:16:03 2017 Nicolas Polomack
** Last update Mon Feb 13 02:30:25 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "raytracer.h"

int	show_menu(t_menu *m, t_params *params)
{
  int	i;

  while (sfRenderWindow_isOpen(m->window))
    {
      sfRenderWindow_clear(m->window, sfWhite);
      if (m->menu_id)
	draw_options(m, params);
      else
	draw_main_menu(m);
      sfTexture_updateFromPixels(m->backg_t, m->backg->pixels,
				 m->backg->width, m->backg->height, 0, 0);
      sfRenderWindow_drawSprite(m->window, m->backg_s, NULL);
      if (m->menu_id)
	sfRenderWindow_drawSprite(m->window, m->option_s, NULL);
      else
	sfRenderWindow_drawSprite(m->window, m->menu_s, NULL);
      sfRenderWindow_display(m->window);
      if ((i = handle_menu(m, params)) != 0)
        return (i);
    }
  return (-3);
}

void		draw_options(t_menu *m, t_params *params)
{
  sfVector2i	pos;

  pos = sfMouse_getPosition((sfWindow *)m->window);
  drawSquare(m->backg, create_vector2i(177, 184), create_vector2i(271, 69),
	     ((pos.x >= 177 && pos.y >= 184) &&
	      (pos.x <= 448 && pos.y <= 253)) ?
	     GREY : ((params->live) ? sfGreen : sfRed));
  drawSquare(m->backg, create_vector2i(159, 339), create_vector2i(321, 58),
	     ((pos.x >= 159 && pos.y >= 339) &&
	      (pos.x <= 480 && pos.y <= 397)) ? GREY : sfWhite);
}

void		draw_main_menu(t_menu *m)
{
  sfVector2i	pos;

  pos = sfMouse_getPosition((sfWindow *)m->window);
  drawSquare(m->backg, create_vector2i(182, 84), create_vector2i(267, 84),
	     ((pos.x >= 182 && pos.y >= 84) &&
	      (pos.x <= 450 && pos.y <= 170)) ? GREY : sfWhite);
  drawSquare(m->backg, create_vector2i(182, 215), create_vector2i(267, 84),
	     ((pos.x >= 182 && pos.y >= 215) &&
	      (pos.x <= 450 && pos.y <= 301)) ? GREY : sfWhite);
  drawSquare(m->backg, create_vector2i(182, 344), create_vector2i(267, 84),
	     ((pos.x >= 182 && pos.y >= 344) &&
	      (pos.x <= 450 && pos.y <= 428)) ? GREY : sfWhite);
}

int	exit_menu(t_menu *m, int exit)
{
  free(m->menu->pixels);
  free(m->menu);
  free(m->option->pixels);
  free(m->option);
  free(m->backg->pixels);
  free(m->backg);
  sfRenderWindow_destroy(m->window);
  sfSprite_destroy(m->menu_s);
  sfTexture_destroy(m->menu_t);
  sfSprite_destroy(m->option_s);
  sfTexture_destroy(m->option_t);
  sfSprite_destroy(m->backg_s);
  sfTexture_destroy(m->backg_t);
  return (exit);
}

void	init_menu(t_menu *m)
{
  m->window = NULL;
  m->menu = NULL;
  m->menu_s = NULL;
  m->menu_t = NULL;
  m->backg = NULL;
  m->backg_s = NULL;
  m->backg_t = NULL;
  m->menu_id = 0;
}
