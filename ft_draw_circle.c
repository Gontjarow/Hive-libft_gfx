/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:59:00 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/24 15:40:53 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

/*
** Doesn't quite draw a perfect circle.
*/

int ft_draw_circle(t_program *p, t_circle *circle, int color)
{
	double r2 = circle->r * circle->r;
	double area = r2 * 2 * 2;
	double rr = circle->r * 2;

	double i = 0;
	t_xy t;
	while (i < area)
	{
		t.x = fmod(i, rr) - circle->r;
		t.y = (i / rr) - circle->r;
		if (t.x * t.x + t.y * t.y <= r2)
		{
			t_xy pixel = VEC2(circle->pos.x + t.x, circle->pos.y + t.y);
			ft_draw_line(p, pixel, pixel, color);
		}
		++i;
	}
	return (TRUE);
}

/*
** Beautiful and extremely efficient circle:
** http://staffwww.itn.liu.se/~stegu/circle/circlealgorithm.pdf
** Misses one diagonal pixel when r isn't ^2
*/

int ft_draw_ring(t_program *prg, t_circle *circle, int color)
{
	t_xy p;
	t_xyz delta;

	p = VEC2(0, circle->r);
	delta = VEC3(5 - 4 * circle->r, 12, 20 - 8 * circle->r);
	while (p.x < p.y)
	{
		ft_put_pixel(prg, circle->pos.x + p.x, circle->pos.y + p.y, color);
		ft_put_pixel(prg, circle->pos.x + p.y, circle->pos.y + p.x, color);
		ft_put_pixel(prg, circle->pos.x + p.x, circle->pos.y - p.y, color);
		ft_put_pixel(prg, circle->pos.x + p.y, circle->pos.y - p.x, color);
		ft_put_pixel(prg, circle->pos.x - p.x, circle->pos.y + p.y, color);
		ft_put_pixel(prg, circle->pos.x - p.y, circle->pos.y + p.x, color);
		ft_put_pixel(prg, circle->pos.x - p.x, circle->pos.y - p.y, color);
		ft_put_pixel(prg, circle->pos.x - p.y, circle->pos.y - p.x, color);
		if ((delta.x < 0) && (delta.x += delta.y))
			delta.z += 8;
		else if((delta.x >= 0) && (--p.y) && (delta.x += delta.z))
			delta.z += 16;
		++p.x;
		delta.y += 8;
	}
	return (TRUE);
}

/*
** Awful idea.
*/
int ft_draw_circle_full(t_program *prg, t_circle *circle, int color)
{
	int i;
	t_circle ring;

	ring.pos = circle->pos;
	i = 0;
	while (++i <= circle->r)
	{
		ring.r = i;
		ft_draw_ring(prg, &ring, color);
	}
	return (TRUE);
}