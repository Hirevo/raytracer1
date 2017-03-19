/*
** events.c for raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 00:02:17 2017 Nicolas Polomack
** Last update Sun Mar 19 21:18:31 2017 Nicolas Polomack
*/

#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include "bmp.h"
#include "raytracer.h"

void	handle_events(t_window *w, sfEvent *event)
{
  if (sfWindow_hasFocus((sfWindow *)w->window))
    while (sfRenderWindow_pollEvent(w->window, event))
      if (event->type == sfEvtClosed ||
	  (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
	{
	  sfRenderWindow_drawSprite(w->window, w->save_s, NULL);
	  sfRenderWindow_display(w->window);
	  save_bmp(w->buffer, "capture.bmp");
	  sfRenderWindow_close(w->window);
	}
}
