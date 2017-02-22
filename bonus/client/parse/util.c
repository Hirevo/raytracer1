/*
** util.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 02:33:42 2017 Nicolas Polomack
** Last update Wed Feb 22 02:41:59 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"
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

int	parse_first(char *line, t_params *params)
{
  int	idxs[7];

  idxs[0] = -1 + (idxs[6] = 0) * 0;
  while (line[++(idxs[0])])
    {
      if (line[idxs[0]] == ':')
	idxs[6] += 1;
      if ((line[idxs[0]] < '0' || line[idxs[0]] > '9') &&
	  line[idxs[0]] != ':')
	return (-1);
    }
  if (idxs[6] != 5 && idxs[6] != 4)
    return (-1);
  gather_idxs(line, idxs);
  params->screen_size.x = get_number(line);
  params->screen_size.y = get_number(line + idxs[1]);
  params->live = get_number(line + idxs[2]) % 2;
  params->reflect_depth = get_number(line + idxs[3]);
  params->ambient = get_number(line + idxs[4]) / 1000.0F;
  params->t_count = (idxs[6] == 5) ? get_number(line + idxs[5]) : 'x';
  if (params->t_count != 'x' &&
      (params->t_count == 0 || params->t_count > 50 || params->t_count % 2))
    return (-1);
  free(line);
  return (0);
}
