/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Thu Feb  9 08:51:46 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include "sfcaster.h"

# define WIDTH 1280//15360
# define HEIGHT 720//8640

typedef struct	s_ray
{
  sfVector3f	orig;
  sfVector3f	dir;
  float		rx;
  float		ry;
  float		rz;
}		t_ray;

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
}		t_obj;

typedef struct	s_params
{
  sfVector2i	screen_size;
  sfVector2i	screen_pos;
  sfVector3f	light;
  int		nb_obj;
  t_ray		ray;
  t_obj		*objs;
  float		ambient;
  float		*dist;
}		t_params;

typedef struct		s_window
{
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;
  t_my_framebuffer	*buffer;
}			t_window;

/*
** calc.c
*/
void		sub_coords(t_params *, t_obj *);
void		add_coords(t_params *, t_obj *);
void		render_frame(t_window *, t_params *);

/*
** angles.c
*/
float		get_cos_angle_s(float, t_params *, int);
float		get_cos_angle_p(float, t_params *, int);
float           get_cos_angle_c(float, t_params *, int);
float           get_cos_angle_o(float, t_params *, float, int);

/*
** lights.c
*/
void		sub_coords_vect(sfVector3f *, t_obj *);
void		add_coords_vect(sfVector3f *, t_obj *);
float		intersect_light(float, t_params *, int);
sfColor		set_luminosity(float, sfColor, float);

/*
** window.c
*/
sfColor		color_stuff(float *, t_params *);

/*
** parse.c
*/
int	parse_config_file(char *, t_params *);

/*
** check.c
*/
int	is_valid_line(char *, int *, int *);
void	gather_idxs(char *, int[10]);
int	get_nbr_objs(char *);

/*
** util.c
*/
int	is_a_number(char *);
int	get_number(char *);

/*
** calc_dir_vector.c
*/
sfVector3f	calc_dir_vector(sfVector2i, sfVector2i);

/*
** intersect_sphere.c
*/
float		intersect_sphere(sfVector3f *, sfVector3f *, float);

/*
** intersect_cyl.c
*/
float		intersect_cyl(sfVector3f *, sfVector3f *, t_obj *);

/*
** intersect_cone.c
*/
float		intersect_cone(sfVector3f *, sfVector3f *, t_obj *);

/*
** intersect_plane.c
*/
float		intersect_plane(sfVector3f *, sfVector3f *);

/*
** events.c
*/
void		handle_events(sfRenderWindow *, sfEvent *,
			      t_params *);

#endif /* !RAYTRACER_H_ */
