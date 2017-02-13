/*
** translate.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/src
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 21:07:05 2017 Nicolas Polomack
** Last update Mon Feb 13 21:41:04 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>

sfVector3f	translate(sfVector3f imp, sfVector3f t)
{
  imp.x += t.x;
  imp.y += t.y;
  imp.z += t.z;
  return (imp);
}
