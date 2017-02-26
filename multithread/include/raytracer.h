/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Sun Feb 26 14:24:50 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include <pthread.h>
# include "sfcaster.h"

# define GREY get_sfcolor(150, 150, 150, 255)

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
  float		reflect;
}		t_obj;

typedef struct s_thread
{
  int		id;
  int		idx;
  int		can_reflect;
  t_ray         ray;
  sfVector2i    offs;
  sfVector2i	end;
  sfVector3f	imp;
  float         *dist;
  sfVector3f	normal;
  sfVector2i    screen_pos;
  t_window	*w;
  t_params      *params;
}               t_thread;

typedef struct		s_params
{
  sfVector2i		screen_size;
  sfVector2i		screen_pos;
  long			t_count;
  pthread_cond_t	cond;
  pthread_cond_t	start;
  pthread_t		tid[50];
  t_thread		t[50];
  t_light		*light;
  int			ssaa;
  int			bmp;
  int			live;
  int			progress;
  int			reflect_depth;
  int			nb_lights;
  int			nb_obj;
  t_ray			ray;
  t_obj			*objs;
  float			ambient;
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

typedef struct		s_menu
{
  sfRenderWindow	*window;
  sfSprite		*backg_s;
  sfTexture		*backg_t;
  sfSprite		*menu_s;
  sfTexture		*menu_t;
  sfSprite		*option_s;
  sfTexture		*option_t;
  t_my_framebuffer	*backg;
  t_my_framebuffer	*menu;
  t_my_framebuffer	*option;
  int			menu_id;
}			t_menu;

/*
** calc.c
*/
void		sub_coords(t_thread *, t_obj *);
void		add_coords(t_thread *, t_obj *);
float		gather_distances(t_obj *, t_ray, int);
void		render_frame(t_window *, t_params *);

/*
** angles.c
*/
float		get_cos_angle_s(t_thread *, sfVector2i);
float		get_cos_angle_p(t_thread *, sfVector2i);
float           get_cos_angle_c(t_thread *, sfVector2i);
float           get_cos_angle_o(t_thread *, sfVector2i);

/*
** lights.c
*/
void		sub_coords_vect(sfVector3f *restrict, sfVector3f *restrict, t_obj *);
void		add_coords_vect(sfVector3f *restrict, sfVector3f *restrict, t_obj *);
float		intersect_light(float, t_thread *, sfVector2i);
sfColor		set_luminosity(float, sfColor, t_thread *, int);

/*
** multi_lights.c
*/
sfColor	average_color(sfColor *, int);
sfColor	seek_lights(float *, t_thread *, int);

/*
** window.c
*/
int		create_window(sfRenderWindow **, char *, sfVector2i);
int		init(t_params *, t_window *);
sfColor		evaluate_luminosity(t_thread *,
				    sfColor, sfVector2i);
sfColor		color_stuff(float *, t_thread *);
int		raytracer(t_params *, char *);

/*
** thread.c
*/
sfColor	gather_color(t_thread *);
void	render_rect(t_thread *);
void	*thread_handler(void *);
void	init_thread(int, t_params *, t_window *);

/*
** load.c
*/
int	load_assets(t_window *, t_params *, char *);

/*
** reflect.c
*/
sfColor set_specular_shade(sfColor, t_thread *, int);
float   get_specular_shade(t_thread *, int);
sfColor	apply_reflect(t_thread *, sfColor);
void	get_normal(t_thread *);
void	get_impact(t_thread *, float);

/*
** ssaa.c
*/
sfColor	ssaa(t_thread *, float, float, sfColor *);

/*
** parse/parse.c
*/
int	parse_config_file(char *, t_params *);

/*
** free.c
*/
int	free_all(t_params *, t_window *);

/*
** menu.c
*/
int	handle_menu(t_menu *, t_params *);
int	handle_options(t_menu *, t_params *,
		      sfVector2i, sfEvent *);
int	handle_main_menu(t_menu *, sfVector2i, sfEvent *);
int	load_menu(t_menu *);

/*
** draw_menu.c
*/
int	show_menu(t_menu *, t_params *);
void	draw_options(t_menu *, t_params *);
void	draw_main_menu(t_menu *);
int	exit_menu(t_menu *, int);
void	init_menu(t_menu *);

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
** normals.c
*/
void	get_cone_normal(t_thread *);
void	get_cylinder_normal(t_thread *);

/*
** rotation.c
*/
void	rx(sfVector3f *restrict, float);
void	ry(sfVector3f *restrict, float);
void	rz(sfVector3f *restrict, float);
void	rotation(sfVector3f *restrict,
		 sfVector3f *restrict, t_obj *);
void	rotation_t_eye(t_thread *);

/*
** anti_rotation.c
*/
void	anti_rotation(sfVector3f *restrict,
		      sfVector3f *restrict, t_obj *);
void	anti_rotation_eye(t_thread *);

/*
** calc_dir_vector.c
*/
sfVector3f	calc_dir_vector(sfVector2i, float, float, int);

/*
** intersect/intersect_sphere.c
*/
float		intersect_sphere(sfVector3f *restrict,
				 sfVector3f *restrict, float);

/*
** intersect/intersect_cyl.c
*/
float		intersect_cyl(sfVector3f *restrict,
			      sfVector3f *restrict, t_obj *);
float		intersect_closed_cyl(sfVector3f *restrict,
				     sfVector3f *restrict,
				     t_obj *, float);

/*
** intersect/intersect_cone.c
*/
float		intersect_cone(sfVector3f *restrict,
			       sfVector3f *restrict, t_obj *);
float           intersect_closed_cone(sfVector3f *restrict,
				      sfVector3f *restrict,
				      t_obj *, float);

/*
** intersect/intersect_disk.c
*/
float	intersect_disk(sfVector3f *restrict,
		       sfVector3f *restrict, float);

/*
** intersect/intersect_plane.c
*/
float		intersect_plane(sfVector3f *restrict,
				sfVector3f *restrict);

/*
** events.c
*/
void		handle_events(t_window *, sfEvent *,
			      t_params *);

#endif /* !RAYTRACER_H_ */
