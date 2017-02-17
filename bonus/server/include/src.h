/*
** wireframe.h for wireframe in /home/nicolaspolomack/graphical/wireframe
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Dec  1 20:15:25 2016 Nicolas Polomack
** Last update Thu Feb  9 19:13:05 2017 Nicolas Polomack
*/

#ifndef SRC_H_
# define SRC_H_

# include <SFML/Graphics.h>

typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_my_framebuffer;

void		my_put_pixel(t_my_framebuffer *, int, int, sfColor);
sfVector3f	raytrace(sfVector2i, sfVector2i);

#endif /* !SRC_H_ */
