/*
** events.c for raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Feb  7 00:02:17 2017 Nicolas Polomack
** Last update Tue Feb  7 09:46:20 2017 Nicolas Polomack
*/

#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include "raytracer.h"

void	handle_events(sfRenderWindow *window, sfEvent *event,
		      t_params *params)
{
  if (sfRenderWindow_hasFocus(window))
    {
      while (sfRenderWindow_pollEvent(window, event))
	if (event->type == sfEvtClosed ||
	    (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
	  sfRenderWindow_close(window);
      if (sfKeyboard_isKeyPressed(sfKeyUp))
	params->ray.orig.x += 10;
      if (sfKeyboard_isKeyPressed(sfKeyDown))
	params->ray.orig.x -= 10;
      if (sfKeyboard_isKeyPressed(sfKeyLeft))
	params->ray.orig.y += 10;
      if (sfKeyboard_isKeyPressed(sfKeyRight))
	params->ray.orig.y -= 10;
      if (sfKeyboard_isKeyPressed(sfKeyLShift))
	params->ray.orig.z -= 10;
      if (sfKeyboard_isKeyPressed(sfKeySpace))
	params->ray.orig.z += 10;
    }
}
