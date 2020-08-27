/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:34:35 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/27 03:22:18 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "constants.h"

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

typedef struct	s_image
{
	void	*ptr;
	int		*data;
	int		bpp;
	int		width;
	int		height;
	int		endian;
}				t_image;

typedef struct	t_argb
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_argb;

typedef struct	s_clip
{
	double top;
	double left;
	double right;
	double bottom;
}				t_clip;

#endif
