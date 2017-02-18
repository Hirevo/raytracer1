/*
** parse.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Feb  8 23:10:21 2017 Nicolas Polomack
** Last update Sat Feb 18 14:45:05 2017 Nicolas Polomack
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
  params->fov = get_number(line + idxs[6]);
}

void	parse_light(char *line, t_params *params, int l, int *idxs)
{
  params->light[l].pos.x = get_number(line + idxs[0]);
  params->light[l].pos.y = get_number(line + idxs[1]);
  params->light[l].pos.z = get_number(line + idxs[2]);
  params->light[l].ambient = ((float)get_number(line + idxs[3])) / 1000.0F;
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
  if (line[0] == 'o' || line[0] == 'x' || line[0] == 'u')
    params->objs[obj].aper = get_number(line + idxs[9]);
  else
    params->objs[obj].rad = get_number(line + idxs[9]);
  if (line[0] == 'h' || line[0] == 'u')
    params->objs[obj].height = get_number(line + idxs[10]);
}

void	parse_line(char *line, t_params *params, int *lights, int *objs)
{
  int	idxs[11];

  gather_idxs(line, idxs);
  if (line[0] == 'e')
    parse_eye(line, params, idxs);
  else if (line[0] == 'l')
    {
      parse_light(line, params, *lights, idxs);
      *lights += 1;
    }
  else
    {
      parse_object(line, params, *objs, idxs);
      *objs += 1;
    }
  free(line);
}

int	parse_config_file(int fd, t_params *params)
{
  char	*line;
  int	fleo[4];

  fleo[2] = 0;
  fleo[1] = 0;
  fleo[0] = fd;
  if ((fleo[3] = get_nbr_objs(fd, &(fleo[1]))) == -1 || fleo[3] < 2 ||
      alloc_all(params, fleo[3], fleo[1]) == -1)
    return (-1);
  close(fd);
  pipe(fleo);
  write(fleo[1], params->s.scene, my_strlen(params->s.scene));
  close(fleo[1]);
  fleo[3] = -1;
  fleo[1] = 0;
  while ((line = get_next_line(fleo[0])) != NULL)
    {
      if (fleo[3] == -1)
	fleo[3] = parse_first(line, params);
      else if (!is_valid_line(line, &(fleo[2])))
	return (-1);
      else
	parse_line(line, params, &(fleo[1]), &(fleo[3]));
      if (fleo[3] == -1)
	return (-1);
    }
  close(fleo[0]);
  return (0);
}
