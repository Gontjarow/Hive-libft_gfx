/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:40:50 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/08 06:59:14 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define DEG_TO_RAD		0.01745329251994329576923690768488612

# define OUTCODE_INSIDE	0b0000
# define OUTCODE_LEFT	0b0001
# define OUTCODE_RIGHT	0b0010
# define OUTCODE_BOTTOM	0b0100
# define OUTCODE_TOP	0b1000

# define EVENT_MOUSE_MOVE 6
# define EVENT_CLOSE_WIN 17

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

# ifdef __linux__
enum			e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100
};
# else
enum			e_key
{
	W = 13,
	A = 0,
	S = 1,
	D = 2
};
# endif

#endif
