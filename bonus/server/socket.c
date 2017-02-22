/*
** socket.c for socket in /home/nicolaspolomack
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb 16 13:52:48 2017 Nicolas Polomack
** Last update Mon Feb 20 20:32:46 2017 Nicolas Polomack
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

void	prepare_connection(t_socket *s, char *file)
{
  char	*result;

  result = get_config_file(file);
  my_memset(s->scene, 4096);
  my_strcpy(s->scene, result);
  free(result);
  s->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s->addr.sin_port = htons(4242);
  s->addr.sin_family = AF_INET;
  if (bind(s->fd,(struct sockaddr *) &s->addr, sizeof(struct sockaddr)) == -1)
    handle_error("bind");
  if (listen(s->fd, s->nb_clients) == -1)
    handle_error("listen");
}

void	broadcast_start(t_socket *s)
{
  int	i;

  i = -1;
  usleep(15000);
  while (++i < 4)
    send(s->cfd[i], "START", 6, 0);
}

char		*get_config_file(char *file)
{
  int		fd;
  char		*buffer;
  struct stat	stats;

  stat(file, &stats);
  if ((buffer = malloc(((int)stats.st_size) + 1)) == NULL)
    handle_error("malloc");
  if ((fd = open(file, O_RDONLY)) == -1)
    handle_error("open");
  if (read(fd, buffer, stats.st_size) == -1)
    handle_error("read");
  buffer[stats.st_size] = 0;
  close(fd);
  return (buffer);
}

void		listen_connections(t_socket *s)
{
  char		confirm[2];
  unsigned int	addrsize;
  int		i;

  i = -1;
  while (++i < s->nb_clients)
    {
      addrsize = sizeof(s->caddr[i]);
      s->cfd[i] = accept(s->fd, (struct sockaddr *)&(s->cfd[i]), &addrsize);
      if (s->cfd[i] == -1)
	handle_error("client connect");
      send(s->cfd[i], s->scene, 4096, 0);
      send(s->cfd[i], &(s->offs[i]), sizeof(sfVector2i), 0);
      send(s->cfd[i], &(s->end[i]), sizeof(sfVector2i), 0);
      recv(s->cfd[i], confirm, 3, 0);
      if (my_strcmp(confirm, "OK"))
	{
	  my_printf("Connection detected, but communication has failed.\n");
	  close(s->cfd[i--]);
	  continue;
	}
      my_printf("Client %d connected !\n", i);
    }
}

void		gather_results(t_params *params, t_window *w)
{
  int		i;

  i = -1;
  while (++i < params->s.nb_clients)
    {
      my_printf("Client %d: ...", i);
      send(params->s.cfd[i], "RESULT", 7, 0);
      recv(params->s.cfd[i],
	   &(w->buffer->pixels[((params->s.offs[i].y * w->buffer->width) +
				params->s.offs[i].x) * 4]),
	   (params->s.end[i].x - params->s.offs[i].x) *
	   (params->s.end[i].y - params->s.offs[i].y) * 4, MSG_WAITALL);
      my_printf(" OK !\n");
    }
}
