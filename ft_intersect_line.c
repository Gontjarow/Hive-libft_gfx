/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:55:27 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 20:42:07 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

/*
** if (0 < wall_pt < 1) && (0 < line_pt)
**	The lines intersect eventually. (we only care about this)
** if (0 < wall_pt < 1) && (0 < line_pt < 1)
**	The lines intersect directly.
*/

static double	test(t_program *p, t_line *wall)
{
	t_xy	plr;
	t_xy	dir;
	double	divisor;
	double	wall_pt;
	double	line_pt;

	plr = p->plr.pos;
	dir = vec2_add(p->plr.dir, p->plr.dir);
	divisor = (wall->start.x - wall->end.x) * (plr.y - dir.y) -
			(wall->start.y - wall->end.y) * (plr.x - dir.x);
	if (divisor == 0)
		return (0);
	wall_pt = ((wall->start.x - plr.x) * (plr.y - dir.y) -
		(wall->start.y - plr.y) * (plr.x - dir.x)) / divisor;
	line_pt = -((wall->start.x - wall->end.x) * (wall->start.y - plr.y) -
		(wall->start.y - wall->end.y) * (wall->start.x - plr.x)) / divisor;
	return ((0 < wall_pt && wall_pt < 1 && line_pt > 0) ? wall_pt : 0);
}

/*
** Uses the player's position and direction to test against the wall.
*/

t_xy			intersect_line(t_program *p, t_line wall)
{
	double	wall_pt;

	if ((wall_pt = test(p, &wall)))
	{
		return ((t_xy){
			wall.start.x + wall_pt * (wall.end.x - wall.start.x),
			wall.start.y + wall_pt * (wall.end.y - wall.start.y)
		});
	}
}
