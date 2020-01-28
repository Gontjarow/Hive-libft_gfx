/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_box.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:21:03 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/28 18:58:35 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

static int clip_box(t_xy *pos, t_xy *size)
{
	if ((pos->x < 0) || (pos->y < 0)
	|| (pos->x > WIN_WIDTH) || (pos->y > WIN_HEIGHT))
	{
		if ((pos->x + size->x < 0) || (pos->y + size->y < 0))
			return (FALSE);
		if (pos->x < 0)
		{
			size->x -= fabs(pos->x);
			pos->x = 0;
		}
		else if (pos->x + size->x > WIN_WIDTH)
			size->x -= (size->x - WIN_WIDTH);
		if (pos->y < 0)
		{
			size->y -= fabs(pos->y);
			pos->y = 0;
		}
		else if (pos->y + size->y > WIN_HEIGHT)
			size->y -= (size->y - WIN_HEIGHT);
	}
	return (TRUE);
}

int		ft_draw_box(t_program *p, t_xy pos, t_xy size, int color)
{
	int x;
	int y;

	if (!clip_box(&pos, &size))
	{
		printf("oh no\n");
		return (FALSE);
	}
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			ft_put_pixel(p, pos.x + x, pos.y + y, color);
			++x;
		}
		++y;
	}
	return (TRUE);
}