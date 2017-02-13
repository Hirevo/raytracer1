/*
** menu.c for wolf3d in /home/nicolaspolomack/graphical/wolf3d
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Jan 12 04:19:57 2017 Nicolas Polomack
** Last update Mon Feb 13 01:44:52 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "my.h"
#include "bmp.h"
#include "raytracer.h"

int		handle_menu(t_menu *m, t_params *params)
{
  sfEvent	event;
  sfVector2i	pos;
  int		i;

  i = 0;
  pos = sfMouse_getPosition((sfWindow *)m->window);
  while (sfRenderWindow_pollEvent(m->window, &event))
    {
      i = ((m->menu_id) ? handle_options(m, params, pos, &event) :
	   handle_main_menu(m, pos, &event));
      return (i);
    }
  return (i);
}

int	handle_options(t_menu *m, t_params *params,
		       sfVector2i pos, sfEvent *event)
{
  if (event->type == sfEvtClosed ||
      (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
    sfRenderWindow_close(m->window);
  else if (event->type == sfEvtMouseButtonPressed &&
           event->mouseButton.button == sfMouseLeft)
    {
      if ((pos.x >= 177 && pos.y >= 184) && (pos.x <= 448 && pos.y <= 253))
        params->live = !params->live;
      else if ((pos.x >= 159 && pos.y >= 339) &&
	       (pos.x <= 480 && pos.y <= 397))
        {
          m->menu_id = !m->menu_id;
          drawSquare(m->backg, create_vector2i(177, 184),
                     create_vector2i(271, 69), sfWhite);
          drawSquare(m->backg, create_vector2i(159, 339),
                     create_vector2i(321, 58), sfWhite);
        }
    }
  return (0);
}

int	handle_main_menu(t_menu *m,
			 sfVector2i pos, sfEvent *event)
{
  if (event->type == sfEvtClosed ||
      (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
    sfRenderWindow_close(m->window);
  else if (event->type == sfEvtMouseButtonPressed &&
           event->mouseButton.button == sfMouseLeft)
    {
      if ((pos.x >= 182 && pos.y >= 84) && (pos.x <= 450 && pos.y <= 170))
        return (1);
      else if ((pos.x >= 182 && pos.y >= 215) &&
	       (pos.x <= 450 && pos.y <= 301))
        {
          m->menu_id = !m->menu_id;
          drawSquare(m->backg, create_vector2i(182, 215),
                     create_vector2i(267, 84), sfWhite);
        }
      else if ((pos.x >= 182 && pos.y >= 344) &&
	       (pos.x <= 450 && pos.y <= 428))
        return (exit_menu(m, -3));
    }
  return (0);
}

int		load_menu(t_menu *m)
{
  sfVideoMode	mode;

  mode.width = 640;
  mode.height = 520;
  mode.bitsPerPixel = 32;
  m->window = sfRenderWindow_create(mode, "Raytracer1 - Menu", sfClose, NULL);
  if ((m->backg = assemble_texture(&(m->backg_t),
                                   &(m->backg_s),
                                   640, 520)) == NULL ||
      (m->menu = load_bmp("../resources/menu.bmp",
                          &(m->menu_s), &(m->menu_t))) == NULL ||
      (m->option = load_bmp("../resources/menu2.bmp",
                            &(m->option_s), &(m->option_t))) == NULL)
    return (-1);
  return (0);
}

int		main(int ac, char **av)
{
  t_menu	m;
  t_params	params;

  if (ac != 2)
    return (84);
  if (my_strcmp(av[1], "-h") == 0)
    return (disp_guide());
  init_menu(&m);
  if (load_menu(&m) == -1)
    exit_menu(&m, 84);
  while (show_menu(&m, &params) != -3)
    {
      sfWindow_setVisible((sfWindow *)m.window, sfFalse);
      raytracer(&params, av[1]);
      sfWindow_setVisible((sfWindow *)m.window, sfTrue);
    }
  return (0);
}
