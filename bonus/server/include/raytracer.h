/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Wed Feb 22 03:11:05 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <pthread.h>
# include "sfcaster.h"

typedef struct s_window t_window;
typedef struct s_params t_params;
typedef struct s_socket t_socket;

typedef struct          s_socket
{
  int                   fd;
  struct sockaddr_in	addr;
  int			nb_clients;
  int                   cfd[10];
  struct sockaddr_in	caddr[10];
  sfVector2i            offs[10];
  sfVector2i            end[10];
  char			scene[4096];
}                       t_socket;

typedef struct		s_params
{
  sfVector2i		screen_size;
  t_socket		s;
  int			bmp;
  int			live;
  int			progress;
  int			fov;
}			t_params;

typedef struct		s_window
{
  pthread_mutex_t	mutex;
  sfRenderWindow	*window;
  sfTexture		*save_t;
  sfTexture		*texture;
  sfSprite		*save_s;
  sfSprite		*sprite;
  t_my_framebuffer	*save;
  t_my_framebuffer	*buffer;
}			t_window;

/*
** launch.c
*/
void	handle_error(char *);

/*
** socket.c
*/
void	prepare_connection(t_socket *, char *);
void	listen_connections(t_socket *);
void	broadcast_start(t_socket *);
void	gather_results(t_params *, t_window *);
char	*get_config_file(char *);

/*
** window.c
*/
int		create_window(sfRenderWindow **, char *, sfVector2i);
int		init(t_params *, t_window *);

/*
** load.c
*/
int	load_assets(t_window *, t_params *, char *);

/*
** parse/parse.c
*/
int	parse_config_file(char *, t_params *);

/*
** free.c
*/
int	free_all(t_params *, t_window *);

/*
** parse/check.c
*/
int	is_valid_line(char *, int *);
void	gather_idxs(char *, int[10]);
int	get_nbr_objs(char *, int *);
int	disp_guide();

/*
** parse/util.c
*/
int	alloc_all(t_params *, int, int);
int	is_a_number(char *);
int	get_number(char *);
int	parse_first(char *, t_params *);

/*
** parse/proc.c
*/
int	get_core_count();

/*
** events.c
*/
void		handle_events(t_window *, sfEvent *);

#endif /* !RAYTRACER_H_ */
