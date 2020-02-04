/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clip_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:44:51 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 21:50:56 by ngontjar         ###   ########.fr       */
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

static t_xy	new_point_vert(t_xy start, t_xy end, int outcode, t_clip *clip)
{
	t_xy out;

	out.y = (outcode & OUTCODE_TOP ? clip->top : clip->bottom - 1);
	out.x = (end.x - start.x);
	out.x *= (outcode & OUTCODE_TOP ?
		(clip->top - start.y) :
		(clip->bottom - start.y));
	out.x /= (end.y - start.y);
	out.x += start.x;
	return (out);
}

static t_xy	new_point_hori(t_xy start, t_xy end, int outcode, t_clip *clip)
{
	t_xy out;

	out.x = (outcode & OUTCODE_LEFT ? clip->left : clip->right);
	out.y = (end.y - start.y);
	out.y *= (outcode & OUTCODE_LEFT ?
		(clip->left - start.x) :
		(clip->right - start.x));
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

static int	assign(t_xy *dest, t_xy point, t_clip *clip)
{
	*dest = point;
	return (ft_get_region(point, *clip));
}

int			ft_clip_line(t_line *line, t_clip clip)
{
	int		outcode_start;
	int		outcode_end;
	int		outcode;
	t_xy	point;

	outcode_start = ft_get_region(line->start, clip);
	outcode_end = ft_get_region(line->end, clip);
	while (TRUE)
	{
		if (!(outcode_start | outcode_end))
			break ;
		else if (outcode_start & outcode_end)
			break ;
		outcode = (outcode_start ? outcode_start : outcode_end);
		if (outcode & (OUTCODE_TOP | OUTCODE_BOTTOM))
			point = new_point_vert(line->start, line->end, outcode, &clip);
		else if (outcode & (OUTCODE_LEFT | OUTCODE_RIGHT))
			point = new_point_hori(line->start, line->end, outcode, &clip);
		if (outcode == outcode_start)
			outcode_start = assign(&line->start, point, &clip);
		else
			outcode_end = assign(&line->end, point, &clip);
	}
	return (!(outcode_start | outcode_end));
}
