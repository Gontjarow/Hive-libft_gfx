/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gfx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:07:46 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/24 16:44:44 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GFX_H
# define LIBFT_GFX_H

# ifndef LIBFT_OUTCODES
#  define LIBFT_OUTCODES
#  define OUTCODE_INSIDE 0b0000
#  define OUTCODE_LEFT 0b0001
#  define OUTCODE_RIGHT 0b0010
#  define OUTCODE_BOTTOM 0b0100
#  define OUTCODE_TOP 0b1000
# endif

# include "stdio.h"
# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define EVENT_MOUSE_MOVE 6
# define EVENT_CLOSE_WIN 17

# define WIN_WIDTH 500
# define WIN_HEIGHT 500

# define VEC3(a,b,c) (t_xyz){a, b, c}
# define VEC2(a,b) (t_xy){a, b}
# define RANGE(a,b) (t_range){a, b}
# define LINE(a,b,c,d) (t_line){VEC2(a, b), VEC2(c, d)}

typedef struct	s_xyz
{
	double x;
	double y;
	double z;
}				t_xyz;

typedef struct	s_xy
{
	double x;
	double y;
}				t_xy;

typedef struct	s_range
{
	double begin;
	double end;
}				t_range;

typedef struct	s_line
{
	t_xy start;
	t_xy end;
}				t_line;

typedef struct	s_circle
{
	t_xy pos;
	double r;
}				t_circle;

typedef struct	s_image
{
	void	*ptr;
	int		*data;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
}				t_image;

typedef struct	s_program
{
	void	*mlx;
	void	*win;
	t_xy	size;
	t_image	buffer;
}				t_program;

enum			e_color
{
	black = 0x000000,
	white = 0xFFFFFF,
	half_grey = 0x808080,
	red = 0xFF0000,
	dark_red = 0x800000,
	green = 0x00FF00,
	dark_green = 0x008000,
	blue = 0x0000FF,
	dark_blue = 0x000080,
	yellow = 0xFFFF00,
	dark_yellow = 808000,
	cyan = 0x00FFFF,
	dark_cyan = 0x008080,
	pink = 0xFF00FF,
	purple = 0x800080
};

void			ft_die(const char *error_message);
double			ft_map(double in, t_range from, t_range to);
double			ft_clamp(double input, double min, double max);
int				ft_rgb_to_int(double r, double g, double b);
int				ft_put_pixel(t_program *p, int x, int y, int color);
int				ft_draw_line(t_program *p, t_xy start, t_xy end, int color);
int				ft_draw_wall(t_program *p, int x, double distance, int color);
int				ft_clear_buffer(t_image *image);
int				ft_clip_line(t_line *line);
int				ft_draw_circle(t_program *p, t_circle *circle, int color);
int				ft_draw_ring(t_program *p, t_circle *circle, int color);
int				ft_draw_circle_full(t_program *p, t_circle *circle, int color);

int				ft_get_region(t_xy point);
int				render(t_program *p);

#endif
