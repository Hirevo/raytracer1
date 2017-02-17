/*
** calc_dir_vector.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:29:14 2017 Nicolas Polomack
** Last update Mon Feb 13 00:36:49 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "sfcaster.h"

sfVector3f	calc_dir_vector(sfVector2i screen_size,
				int x, int y, int fov)
{
  sfVector3f	dir;

  dir.x = (screen_size.x / 2) / tanr(fov / 2);
  dir.y = (screen_size.x / 2) - x;
  dir.z = (screen_size.y / 2) - y;
  return (dir);
}
