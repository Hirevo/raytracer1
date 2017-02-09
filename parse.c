/*
** parse.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Feb  8 23:10:21 2017 Nicolas Polomack
** Last update Thu Feb  9 02:38:44 2017 Nicolas Polomack
*/

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "raytracer.h"
#include "get_next_line.h"
#include "my.h"

void	parse_eye(char *line, t_params *params, int *idxs)
{
  params->ray.orig.x = get_number(line + idxs[0]);
  params->ray.orig.y = get_number(line + idxs[1]);
  params->ray.orig.z = get_number(line + idxs[2]);
  params->ray.rx = get_number(line + idxs[3]);
  params->ray.ry = get_number(line + idxs[4]);
  params->ray.rz = get_number(line + idxs[5]);
}

void	parse_light(char *line, t_params *params, int *idxs)
{
  params->light.x = get_number(line + idxs[0]);
  params->light.y = get_number(line + idxs[1]);
  params->light.z = get_number(line + idxs[2]);
  params->ambient = ((float)get_number(line + idxs[3])) / 1000.0F;
}

void	parse_object(char *line, t_params *params, int obj, int *idxs)
{
  params->objs[obj].type = line[0];
  params->objs[obj].pos.x = get_number(line + idxs[0]);
  params->objs[obj].pos.y = get_number(line + idxs[1]);
  params->objs[obj].pos.z = get_number(line + idxs[2]);
  params->objs[obj].rx = get_number(line + idxs[3]);
  params->objs[obj].ry = get_number(line + idxs[4]);
  params->objs[obj].rz = get_number(line + idxs[5]);
  params->objs[obj].col.r = get_number(line + idxs[6]) % 256;
  params->objs[obj].col.g = get_number(line + idxs[7]) % 256;
  params->objs[obj].col.b = get_number(line + idxs[8]) % 256;
  params->objs[obj].col.a = 255;
  if (line[0] == 'o' || line[0] == 'x')
    params->objs[obj].aper = get_number(line + idxs[9]);
  else
    params->objs[obj].rad = get_number(line + idxs[9]);
}

void	parse_line(char *line, t_params *params, int *objs)
{
  int	idxs[10];

  gather_idxs(line, idxs);
  if (line[0] == 'e')
    parse_eye(line, params, idxs);
  else if (line[0] == 'l')
    parse_light(line, params, idxs);
  else
    {
      parse_object(line, params, *objs, idxs);
      *objs += 1;
    }
}

int	parse_config_file(char *file, t_params *params)
{
  int	fd;
  char	*line;
  int	lights;
  int	eyes;
  int	objs;

  eyes = 0;
  lights = 0;
  if ((objs = get_nbr_objs(file)) == -1 || objs < 2 ||
      (fd = open(file, O_RDONLY)) == -1)
    return (-1);
  if (objs && (params->objs = malloc(sizeof(t_obj) * (objs - 2))) == NULL)
    return (-1);
  params->nb_obj = objs - 2;
  objs = 0;
  while ((line = get_next_line(fd)))
    {
      if (is_valid_line(line, &lights, &eyes))
	parse_line(line, params, &objs);
      else
	return (-1);
      free(line);
    }
  close(fd);
  return (0);
}
