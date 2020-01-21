/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clip_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:44:51 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/21 22:55:53 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

/*
** Modifies line start/end to stay within the screen.
**
** Uses Cohen–Sutherland algorithm, 9 "regions"
**
**          left  center  right
**
** top		 1001 | 1000 | 1010
**       	──────┼──────┼──────
** center	 0001 | 0000 | 0010
**       	──────┼──────┼──────
** bottom	 0101 | 0100 | 0110
**
** Start and End will be tested for region, then compared.
**
** Returns TRUE if there are pixels to draw.
*/

/*
** TODO: Bottom and Right don't work. Outcode always 0010 (2)
*/
static t_xy	new_point_vert(t_xy start, t_xy end, int outcode)
{
	t_xy out;

	out.y = (outcode & OUTCODE_TOP ? WIN_HEIGHT : 0);
	out.x = (end.x - start.x);
	out.x *= (outcode & OUTCODE_TOP ? (WIN_HEIGHT - start.y) : (0 - start.y));
	out.x /= (end.y - start.y);
	out.x += start.x;
	return (out);
}

static t_xy new_point_hori(t_xy start, t_xy end, int outcode)
{
	t_xy out;

	out.x = (outcode & OUTCODE_LEFT ? 0 : WIN_WIDTH);
	out.y = (end.y - start.y);
	out.y *= (outcode & OUTCODE_LEFT ? (0 - start.x) : (WIN_WIDTH - start.x));
	out.y /= (end.x - start.x);
	out.y += start.y;
	return (out);
}

/*
** if !(outcode_start | outcode_end)
**    Both points are in the center (0b000)
**    The line can be drawn.
**
** if (outcode_start & outcode_end)
**    Both points SHARE an outside-region
**    The line can't be drawn at all.
**
** else
**    At least one end of the line is outside
**    the screen, or both, but they don't share
**    a side so the line will intersect the view.
**    Clip one end of the line before checking again.
*/

int			ft_clip_line(t_line *line)
{
	int		outcode_start;
	int		outcode_end;
	int		outcode;
	int		accept;
	t_xy	point;

	accept = FALSE;
	outcode_start = ft_get_region(line->start);
	outcode_end = ft_get_region(line->end);
	while (TRUE)
	{
		if (!(outcode_start | outcode_end) && (accept = TRUE))
			break ;
		else if (outcode_start & outcode_end)
			break ;
		outcode = (outcode_start ? outcode_start : outcode_end);
		printf("outcode %X\n", outcode);
		if (outcode & (OUTCODE_TOP | OUTCODE_BOTTOM))
			point = new_point_vert(line->start, line->end, outcode);
		else if (outcode & (OUTCODE_LEFT | OUTCODE_RIGHT))
			point = new_point_hori(line->start, line->end, outcode);
		if (outcode == outcode_start)
			outcode_start = ft_get_region((line->start = point));
		else
			outcode_end = ft_get_region((line->end = point));
	}
	return (accept);
}
