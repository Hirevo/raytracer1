/*
** util.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 02:33:42 2017 Nicolas Polomack
** Last update Thu Feb  9 21:55:15 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"

int	is_a_number(char *str)
{
  int	i;

  i = 1;
  if (str[0] != '-' && (str[0] < '0' || str[0] > '9'))
    return (-1);
  while (str[i] && str[i] != ':')
    {
      if (str[i] < '0' || str[i] > '9')
        return (-1);
      i += 1;
    }
  return (i);
}

int	get_number(char *str)
{
  int	i;
  int	result;
  int	factor;

  result = 0;
  factor = 1;
  i = (str[0] == '-');
  while (str[i] && str[i] != ':')
    {
      i += 1;
      factor *= 10;
    }
  if (i == (str[0] == '-'))
    return (-1);
  factor /= 10;
  i = (str[0] == '-');
  while (str[i] && str[i] != ':')
    {
      result += (str[i] - '0') * factor;
      factor /= 10;
      i += 1;
    }
  return ((str[0] == '-') ? -result : result);
}

int	alloc_all(t_params *params, int objs, int lights)
{
  if (!objs || !lights || (params->objs = malloc(sizeof(t_obj) *
						 (objs - 1 - lights))) == NULL ||
      (params->light = malloc(sizeof(t_light) * lights)) == NULL)
    return (-1);
  params->nb_lights = lights;
  params->nb_obj = objs - 1 - lights;
  return (0);
}
