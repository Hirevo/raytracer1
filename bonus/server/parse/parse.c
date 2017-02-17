/*
** parse.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Feb  8 23:10:21 2017 Nicolas Polomack
** Last update Fri Feb 17 12:29:20 2017 Nicolas Polomack
*/

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "raytracer.h"
#include "get_next_line.h"
#include "my.h"

int	parse_config_file(char *file, t_params *params)
{
  char	*line;
  int	fleo[4];

  fleo[2] = 0;
  fleo[1] = 0;
  if ((fleo[3] = get_nbr_objs(file, &(fleo[1]))) == -1 || fleo[3] < 2 ||
      (fleo[0] = open(file, O_RDONLY)) == -1)
    return (-1);
  fleo[3] = -1;
  fleo[1] = 0;
  while ((line = get_next_line(fleo[0])) != NULL)
    {
      if (fleo[3] == -1)
	fleo[3] = parse_first(line, params);
      else if (!is_valid_line(line, &(fleo[2])))
	return (-1);
      if (fleo[3] == -1)
	return (-1);
    }
  close(fleo[0]);
  return (0);
}
