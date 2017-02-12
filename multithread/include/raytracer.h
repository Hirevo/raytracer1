/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Sun Feb 12 03:52:02 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include <pthread.h>
# include "sfcaster.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_window t_window;
typedef struct s_params t_params;

typedef struct	s_ray
{
  sfVector3f	orig;
  sfVector3f	dir;
  float		rx;
  float		ry;
  float		rz;
}		t_ray;

typedef struct	s_light
{
  sfVector3f	pos;
  sfColor	col;
  float		ambient;
}		t_light;

typedef struct	s_obj
{
  char		type;
  sfVector3f	pos;
  float		rx;
  float		ry;
  float		rz;
  float		rad;
  float		aper;
  sfColor	col;
  float		height;
}		t_obj;

typedef struct s_thread
{
  int		id;
  t_ray         ray;
  sfVector2i    offs;
  float         *dist;
  sfVector2i    screen_pos;
  t_window	*w;
  t_params      *params;
}               t_thread;

typedef struct	s_params
{
  sfVector2i	screen_size;
  sfVector2i	screen_pos;
  long		proc_count;
  pthread_t	tid[8];
  t_thread	t[8];
  t_light	*light;
  int		bmp;
  int		progress;
  int		nb_lights;
  int		nb_obj;
  t_ray		ray;
  t_obj		*objs;
  float		*dist;
  int		fov;
}		t_params;

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
** calc.c
*/
void		sub_coords(t_thread *, t_obj *);
void		add_coords(t_thread *, t_obj *);
float		gather_distances(t_thread *, int);
void		render_frame(t_window *, t_params *);

/*
** angles.c
*/
float		get_cos_angle_s(float, t_thread *, sfVector2i);
float		get_cos_angle_p(float, t_thread *, sfVector2i);
float           get_cos_angle_c(float, t_thread *, sfVector2i);
float           get_cos_angle_cc(float, t_thread *, sfVector2i);
float           get_cos_angle_o(float, t_thread *, sfVector2i);
float           get_cos_angle_oo(float, t_thread *, sfVector2i);

/*
** lights.c
*/
void		sub_coords_vect(sfVector3f *, sfVector3f *, t_obj *);
void		add_coords_vect(sfVector3f *, sfVector3f *, t_obj *);
float		intersect_light(float, t_thread *, sfVector2i);
sfColor		set_luminosity(float, sfColor, float);

/*
** multi_lights.c
*/
sfColor	average_color(sfColor *, int);
sfColor	seek_lights(float *, t_thread *, int);

/*
** window.c
*/
int		create_window(sfRenderWindow **, char *, sfVector2i);
int		init(t_params *);
sfColor		evaluate_luminosity(float *, t_thread *,
				    sfColor, sfVector2i);
sfColor		color_stuff(float *, t_thread *);

/*
** thread.c
*/
void	render_rect(t_thread *);
void	*thread_handler(void *);
void	init_thread(int, t_params *, t_window *);

/*
** load.c
*/
int	load_assets(t_window *, t_params *, char *);

/*
** parse/parse.c
*/
int	parse_config_file(char *, t_params *);

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
** normals.c
*/
void	get_cone_normal(t_thread *, sfVector2i, sfVector3f *, float);
void	get_cylinder_normal(t_thread *, sfVector2i, sfVector3f *, float);

/*
** rotation.c
*/
void	rx(sfVector3f *, float);
void	ry(sfVector3f *, float);
void	rz(sfVector3f *, float);
void	rotation(sfVector3f *, sfVector3f *, t_obj *);
void	rotation_t_eye(t_thread *);

/*
** anti_rotation.c
*/
void	anti_rotation(sfVector3f *, sfVector3f *, t_obj *);
void	anti_rotation_eye(t_params *);

/*
** calc_dir_vector.c
*/
sfVector3f	calc_dir_vector(sfVector2i, sfVector2i, int);

/*
** intersect/intersect_sphere.c
*/
float		intersect_sphere(sfVector3f *, sfVector3f *, float);

/*
** intersect/intersect_cyl.c
*/
float		intersect_cyl(sfVector3f *, sfVector3f *, t_obj *);
float		intersect_closed_cyl(sfVector3f *, sfVector3f *,
				     t_obj *, float);

/*
** intersect/intersect_cone.c
*/
float		intersect_cone(sfVector3f *, sfVector3f *, t_obj *);
float           intersect_closed_cone(sfVector3f *, sfVector3f *,
				      t_obj *, float);

/*
** intersect/intersect_disk.c
*/
float	intersect_disk(sfVector3f *, sfVector3f *, float);

/*
** intersect/intersect_plane.c
*/
float		intersect_plane(sfVector3f *, sfVector3f *);

/*
** events.c
*/
void		handle_events(t_window *, sfEvent *,
			      t_params *);

#endif /* !RAYTRACER_H_ */
