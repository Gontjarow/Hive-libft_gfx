/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:09:41 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 19:09:57 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

t_xy vec2_rot(t_xy v, double angle)
{
	return ((t_xy){
		v.x * cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle)
	});
}

t_xy	vec2_norm(t_xy v)
{
	double mag;

	mag = sqrt((v.x * v.x) + (v.y * v.y));
	return ((t_xy){
		v.x / mag,
		v.y / mag
	});
}

t_xy vec2_mul(t_xy v, double scalar)
{
	return ((t_xy){
		v.x * scalar,
		v.y * scalar
	});
}

t_xy vec2_add(t_xy a, t_xy b)
{
	return((t_xy)
	{
		a.x + b.x,
		a.y + b.y
	});
}

t_xy vec2_dec(t_xy a, t_xy b)
{
	return((t_xy)
	{
		a.x - b.x,
		a.y - b.y
	});
}
