/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gfx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:07:46 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/27 03:24:55 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GFX_H
# define LIBFT_GFX_H

# include "macros.h"
# include "constants.h"
# include "data.h"
# include <stdio.h>
# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define WIN_WIDTH 500
# define WIN_HEIGHT 500

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

void			ft_die(const char *error_message);
double			ft_map(double in, t_range from, t_range to);
double			ft_clamp(double input, double min, double max);

t_argb			new_argb(int color);
int 			blend_argb(int fore, int back);

int				ft_rgb_to_int(double r, double g, double b);
int				ft_argb_to_int(double a, double r, double g, double b);

int				ft_clear_buffer(t_image *image);
int				ft_set_buffer(t_image *image, int color);

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

int				mouse_key(int key, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
int				keyboard(int keycode,void *param);

int				render(t_program *p);

#endif
