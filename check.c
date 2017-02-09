/*
** check.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 02:34:59 2017 Nicolas Polomack
** Last update Thu Feb  9 21:29:30 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include "get_next_line.h"
#include "raytracer.h"
#include "my.h"

int	check_sections(char type, int sec, int *eyes)
{
  if (type == 's' || type == 'p' || type == 'c' ||
      type == 'o' || type == 'x')
    return (sec == 11);
  else if (type == 'e' && !*eyes)
    {
      *eyes = 1;
      return (sec == 8);
    }
  else if (type == 'l')
    return (sec == 5);
  return (0);
}

int	is_valid_line(char *line, int *eyes)
{
  int	len;
  int	idx;
  int	sec;
  int	tmp;

  sec = 1;
  len = my_strlen(line);
  if (!(line[0] == 's' || line[0] == 'p' || line[0] == 'c' ||
        line[0] == 'o' || line[0] == 'x' || line[0] == 'e' ||
        line[0] == 'l'))
    return (0);
  if (len < 10 || line[1] != ':')
    return (0);
  idx = 1;
  while (++idx < len)
    {
      tmp = is_a_number(line + idx);
      if (tmp == -1)
        return (0);
      sec += 1;
      idx += tmp;
    }
  return (check_sections(line[0], sec, eyes) ? 1 : 0);
}

void	gather_idxs(char *line, int idxs[10])
{
  int	idx;
  int	sec;
  int	len;

  sec = 0;
  len = my_strlen(line);
  idx = 1;
  while (++idx < len)
    {
      idxs[sec++] = idx;
      while (line[idx] && line[idx] != ':')
        idx += 1;
    }
}

int	get_nbr_objs(char *file, int *l)
{
  int	objs;
  int	fd;
  char	*line;
  int	e;

  objs = 0;
  e = 0;
  *l = 0;
  if ((fd = open(file, O_RDONLY)) == -1)
    return (-1);
  while ((line = get_next_line(fd)))
    {
      if (line[0] == 'e')
        e += 1;
      else if (line[0] == 'l')
        *l += 1;
      objs += 1;
      free(line);
    }
  close(fd);
  if (!*l || e != 1)
    return (-1);
  return (objs);
}
