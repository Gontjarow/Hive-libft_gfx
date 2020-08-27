/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:06:42 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/08 07:27:17 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int mouse_key(int key, int x, int y, void *param)
{
	t_program *p;
	(void)key;
	(void)x;
	(void)y;

	p = param;
	printf("mouse_key draw\n");
	render(p);
	return (TRUE);
}

int mouse_move(int x, int y, void *param)
{
	t_program *p;

	printf("mouse move");

	p = param;
	p->mouse.d = VEC2(x - p->mouse.pos.x, y - p->mouse.pos.y);
	p->mouse.pos = VEC2(x, y);

	p->plr.dir = vec2_rot(p->plr.dir, p->mouse.d.x * DEG_TO_RAD);

	render(p);
	// printf("mouse move | pos %.0f %.0f | d %f %f\n", p->mouse.pos.x, p->mouse.pos.y, p->mouse.d.x, p->mouse.d.y);
	// t_line debug;
	// debug.start = VEC2(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5);
	// debug.end = VEC2(x, y);
	// t_clip clip = get_boundary(VEC2(0, 0), VEC2(WIN_WIDTH, WIN_HEIGHT));
	// if (ft_clip_line(&debug, &clip))
	// {
	// 	printf("line %.0f %.0f -> %.0f %.0f\n", debug.start.x, debug.start.y, debug.end.x, debug.end.y);
	// 	ft_draw_line(p, debug.start, debug.end, 0xABCDEF);
	// }
}

int keyboard(int keycode,void *param)
{
	t_program *p;
	t_xy direction;

	p = param;
	printf("keycode = %d\n", keycode);
	if (keycode == W)
		p->plr.pos = vec2_add(p->plr.pos, p->plr.dir);
	else if (keycode == S)
		p->plr.pos = vec2_dec(p->plr.pos, p->plr.dir);
	else if (keycode == A)
	{
		direction = vec2_rot(p->plr.dir, 90.0 * DEG_TO_RAD);
		p->plr.pos = vec2_dec(p->plr.pos, direction);
	}
	else if (keycode == D)
	{
		direction = vec2_rot(p->plr.dir, 90.0 * DEG_TO_RAD);
		p->plr.pos = vec2_add(p->plr.pos, direction);
	}
	render(p);
}
