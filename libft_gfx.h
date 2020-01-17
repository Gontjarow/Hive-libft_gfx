/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gfx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:07:46 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/17 15:26:45 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GFX_H
# define LIBFT_GFX_H

# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define SCRN_W 640
# define SCRN_H 360

# define VEC2(a,b) (t_xy){a, b}

typedef struct	s_xy
{
	double x;
	double y;
}				t_xy;

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
double			ft_clamp(double input, double min, double max);
int				ft_rgb_to_int(double r, double g, double b);
int				ft_draw_line(t_program *p, t_xy start, t_xy end, int color);

#endif
