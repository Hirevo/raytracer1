/*
** calc_dir_vector.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:29:14 2017 Nicolas Polomack
** Last update Thu Feb  9 08:52:35 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>

sfVector3f	calc_dir_vector(sfVector2i screen_size, sfVector2i screen_pos)
{
  sfVector3f	dir;

  dir.x = 500;
  dir.y = (screen_size.x / 2) - screen_pos.x;
  dir.z = (screen_size.y / 2) - screen_pos.y;
  return (dir);
}
