/*
** load_bmp.c for wolf3d in 
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Jan  6 19:15:36 2017 Nicolas Polomack
** Last update Sun Feb  5 14:53:33 2017 Nicolas Polomack
*/

#include "raytracer.h"
#include "bmp.h"
#include "sfcaster.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void			save_bmp(t_my_framebuffer *buffer, char *name)
{
  int			fd;
  bmp_header		head;
  bmp_info_header	info;

  if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return ;
  head = set_header(head, buffer);
  write(fd, &head, 14);
  info = set_info(info, buffer);
  write(fd, &info, 40);
  write_pixel_buffer(buffer, fd);
  close(fd);
}

bmp_header	set_header(bmp_header head,
			   t_my_framebuffer *buffer)
{
  head.type = 0x4D42;
  head.size = 54 + (buffer->width * buffer->height * 3);
  head.reserved1 = 0;
  head.reserved2 = 0;
  head.off_bits = 54;
  return (head);
}

bmp_info_header	set_info(bmp_info_header info,
			 t_my_framebuffer *buffer)
{
  info.size = 40;
  info.width = buffer->width;
  info.height = buffer->height;
  info.planes = 1;
  info.bits_per_pixels = 24;
  info.compression = 0;
  info.size_image = (buffer->width * buffer->height * 3);
  info.xppm = 0;
  info.yppm = 0;
  info.clr_used = 0;
  info.clr_important = 0;
  return (info);
}

void		write_pixel_buffer(t_my_framebuffer *buffer,
                                   int fd)
{
  sfVector2i	pos;
  unsigned char	t;

  pos.y = buffer->height - 1;
  while (pos.y >= 0)
    {
      pos.x = -1;
      while (++(pos.x) < buffer->width)
        {
          t = (unsigned char)(buffer->pixels[((buffer->width * pos.y
					       + pos.x) * 4) + 2]);
          write(fd, &t, sizeof(unsigned char));
          t = (unsigned char)(buffer->pixels[((buffer->width * pos.y
					       + pos.x) * 4) + 1]);
          write(fd, &t, sizeof(unsigned char));
          t = (unsigned char)(buffer->pixels[((buffer->width * pos.y
					       + pos.x) * 4) + 0]);
          write(fd, &t, sizeof(unsigned char));
        }
      pos.y -= 1;
    }
}
