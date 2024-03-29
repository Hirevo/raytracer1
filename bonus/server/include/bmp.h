/*
** bmp.h for wolf3d in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Dec 21 19:22:36 2016 Nicolas Polomack
** Last update Fri Mar 17 11:53:10 2017 Nicolas Polomack
*/

#ifndef BMP_H_
# define BMP_H_

# include <SFML/Graphics.h>
# include "sfcaster.h"

# pragma pack(push, 1)

typedef struct		s_bmp_header {
  unsigned short	type;
  unsigned int		size;
  unsigned short	reserved1;
  unsigned short	reserved2;
  unsigned int		off_bits;
}			bmp_header;

# pragma pack(pop)

# pragma pack(push, 1)

typedef struct		s_bmp_info_header {
  unsigned int		size;
  int			width;
  int			height;
  unsigned short	planes;
  unsigned short	bits_per_pixels;
  unsigned int		compression;
  unsigned int		size_image;
  int			xppm;
  int			yppm;
  unsigned int		clr_used;
  unsigned int		clr_important;
}			bmp_info_header;

# pragma pack(pop)

/*
** load_bmp.c
*/
t_my_framebuffer	*load_bmp(char *, sfSprite **, sfTexture **);
void			read_pixel_buffer(t_my_framebuffer *, int,
					  unsigned short, int);
sfColor			get_bmp_color(int, unsigned short);
int			get_pad(int);
void			set_bounds(t_my_framebuffer *, sfVector2i *, int *);

/*
** save_bmp.c
*/
void		save_bmp(t_my_framebuffer *, char *);
int		calculate_pad(t_my_framebuffer *);
void		write_pixel_buffer(t_my_framebuffer *, int, unsigned char *, int);
bmp_header	set_header(bmp_header, t_my_framebuffer *, int);
bmp_info_header	set_info(bmp_info_header, t_my_framebuffer *, int);

#endif /* !BMP_H_ */
