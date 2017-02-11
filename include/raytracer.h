/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Sat Feb 11 02:46:41 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include "sfcaster.h"

# define WIDTH 1920
# define HEIGHT 1080

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

typedef struct	s_imp
{
  float		dist;
  int		face;
}		t_imp;

typedef struct	s_params
{
  sfVector2i	screen_size;
  sfVector2i	screen_pos;
  t_light	*light;
  int		nb_lights;
  int		nb_obj;
  t_ray		ray;
  t_obj		*objs;
  float		*dist;
  int		fov;
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
float		get_cos_angle_s(float, t_params *, sfVector2i);
float		get_cos_angle_p(float, t_params *, sfVector2i);
float           get_cos_angle_c(float, t_params *, sfVector2i);
float           get_cos_angle_cc(float, t_params *, sfVector2i);
float           get_cos_angle_o(float, t_params *, sfVector2i);
float           get_cos_angle_oo(float, t_params *, sfVector2i);

/*
** lights.c
*/
void		sub_coords_vect(sfVector3f *, sfVector3f *, t_obj *);
void		add_coords_vect(sfVector3f *, sfVector3f *, t_obj *);
float		intersect_light(float, t_params *, sfVector2i);
sfColor		set_luminosity(float, sfColor, float);

/*
** multi_lights.c
*/
sfColor	average_color(sfColor *, int);
sfColor	seek_lights(float *, t_params *, int);

/*
** window.c
*/
sfColor		evaluate_luminosity(float *, t_params *,
				    sfColor, sfVector2i);
sfColor		color_stuff(float *, t_params *);

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

/*
** parse/util.c
*/
int	alloc_all(t_params *, int, int);
int	is_a_number(char *);
int	get_number(char *);

/*
** normals.c
*/
void	get_cone_normal(t_params *, sfVector2i, sfVector3f *, float);
void	get_cylinder_normal(t_params *, sfVector2i, sfVector3f *, float);

/*
** rotation.c
*/
void	rx(sfVector3f *, float);
void	ry(sfVector3f *, float);
void	rz(sfVector3f *, float);
void	rotation(sfVector3f *, sfVector3f *, t_obj *);
void	rotation_eye(t_params *, int);

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
void		handle_events(sfRenderWindow *, sfEvent *,
			      t_params *);

#endif /* !RAYTRACER_H_ */
