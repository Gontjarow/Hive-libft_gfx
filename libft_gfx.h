/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gfx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:07:46 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 21:49:56 by ngontjar         ###   ########.fr       */
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

# define DEG_TO_RAD (0.01745329251994329576923690768488612)

# define VEC2(x,y) (t_xy){x, y}
# define VEC3(x,y,z) (t_xyz){x, y, z}
# define RANGE(start,end) (t_range){start, end}
# define LINE(Ax,Ay,Bx,By) (t_line){VEC2(Ax, Ay), VEC2(Bx, By)}
# define CLIP(top,left,right,bottom) (t_clip){top,left,right,bottom}
# define CIRCLE(pos,r) (t_circle){pos, r}
# define ARGB(a,r,g,b) ((t_argb){a, r, g, b})
# define COLOR(AA,RR,GG,BB) ((AA) << 24 | (RR) << 16 | (GG) << 8 | (BB))

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

typedef struct	s_clip
{
	double top;
	double left;
	double right;
	double bottom;
}				t_clip;

typedef struct	s_line
{
	t_xy start;
	t_xy end;
}				t_line;

typedef struct	s_circle
{
	t_xy	pos;
	double	r;
}				t_circle;

typedef struct	s_image
{
	void	*ptr;
	int		*data;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
}				t_image;

/*
** player.dir = direction of the player's view
** range [0,1] normalized
*/

typedef struct	s_player
{
	t_xy pos;
	t_xy dir;
}				t_player;

typedef struct	s_mouse
{
	t_xy pos;
	t_xy d;
}				t_mouse;

typedef struct	s_program
{
	void		*mlx;
	void		*win;
	t_xy		size;
	t_image		buffer;
	t_player	plr;
	t_mouse		mouse;
	char		**map;
}				t_program;

typedef struct	t_argb
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_argb;

enum			e_key
{
	W = 13,
	A = 0,
	S = 1,
	D = 2
};

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

t_argb			new_argb(int color);
int 			blend_argb(int fore, int back);

int				ft_rgb_to_int(double r, double g, double b);
int				ft_argb_to_int(double a, double r, double g, double b);

int				ft_clear_buffer(t_image *image);

int				ft_get_region(t_xy point, t_clip clip);
int				ft_clip_line(t_line *line, t_clip clip);
t_xy			intersect_line(t_program *p, t_line wall);

int				ft_put_pixel(t_program *p, int x, int y, int color);
int				ft_draw_line(t_program *p, t_xy start, t_xy end, int color);
int				ft_draw_box(t_program *p, t_xy pos, t_xy size, int color);
int				ft_draw_wall(t_program *p, int x, double distance, int color);
int				ft_draw_circle(t_program *p, t_circle *circle, int color);
int				ft_draw_ring(t_program *p, t_circle *circle, int color);
int				ft_draw_circle_full(t_program *p, t_circle *circle, int color);

void			draw_top_view(t_program *p, t_xy pos, t_xy dir);
void			draw_view(t_program *p);

t_xy			vec2_rot(t_xy v, double angle);
t_xy			vec2_norm(t_xy v);
t_xy			vec2_mul(t_xy v, double scalar);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_dec(t_xy a, t_xy b);

int				render(t_program *p);

#endif
