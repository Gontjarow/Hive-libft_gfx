/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:25:34 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/22 18:22:01 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

/*
** Requires mlx images
*/

int					ft_draw_line(t_program *p, t_xy start, t_xy end, int color)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	int		index;
	t_xy	pos;

	length = VEC2(fabs(end.x - start.x), fabs(end.y - start.y));
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos.x = start.x;
	pos.y = start.y;
	while (pixels--)
	{
		index = (int)((int)pos.y * p->buffer.line_bytes + pos.x);
		if (index < 0 || index > WIN_WIDTH * WIN_HEIGHT)
		{
			printf("ignoring pixel %.0f %.0f (%d)\n", pos.x, pos.y, index);
			continue;
		}
		p->buffer.data[index] = color;
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}
