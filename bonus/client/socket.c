/*
** socket.c for socket in /home/nicolaspolomack
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb 16 13:52:48 2017 Nicolas Polomack
** Last update Wed Feb 22 03:08:06 2017 Nicolas Polomack
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "my.h"
#include "raytracer.h"

void	handle_error(char *msg)
{
  perror(msg);
  exit(errno);
}

void		send_results(t_window *w, t_socket *s)
{
  char		buffer[7];

  recv(s->fd, buffer, 7, 0);
  if (my_strcmp(buffer, "RESULT"))
    my_printf("KO !\n");
  send(s->fd, &(w->buffer->pixels[((s->offs.y *
				    w->buffer->width) + s->offs.x) * 4]),
       (s->end.x - s->offs.x) * (s->end.y - s->offs.y) * 4, 0);
}

void			connect_socket(t_socket *s, char *ip)
{
  char			confirm[6];
  struct hostent	*hostinfo;

  hostinfo = gethostbyname(ip);
  s->addr.sin_addr = *(struct in_addr *) hostinfo->h_addr;
  s->addr.sin_port = htons(4242);
  s->addr.sin_family = AF_INET;
  if (connect(s->fd, (struct sockaddr *)&s->addr,
	      sizeof(struct sockaddr)) == -1)
    handle_error("connect");
  recv(s->fd, s->scene, 4096, 0);
  recv(s->fd, &s->offs, sizeof(sfVector2i), 0);
  recv(s->fd, &s->end, sizeof(sfVector2i), 0);
  my_printf(" OK !\nWaiting for start signal...");
  send(s->fd, "OK", 3, 0);
  do
    recv(s->fd, confirm, 6, 0);
  while (my_strcmp(confirm, "START"));
}
