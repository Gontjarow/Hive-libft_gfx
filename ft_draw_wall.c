/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:51:28 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/28 16:25:57 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

/*
** Draws a vertical line on the X column, based on the distance from the wall.
** TODO: Refactor so max distance can be assigned for range mapping.
** NOTE: If if distance is greater than input-range,
**       the result will be relatively greater than target-range.
*/

int		ft_draw_wall(t_program *p, int x, double distance, int color)
{
	static double	half = WIN_WIDTH / 2;
	static t_clip	clip = CLIP(0, 0, WIN_WIDTH, WIN_HEIGHT);
	t_line			line;

	if (x < 0 || x >= WIN_WIDTH)
		return (FALSE);
	// distance = ft_map(distance, RANGE(0, 100), RANGE(0, 1));
	line = LINE(x, half + half * distance, x, half + half * -distance);
	if (ft_clip_line(&line, &clip))
	{
		// printf("clip works | start %.0f %.0f | end %.0f %.0f\n",
		// 	line.start.x, line.start.y, line.end.x, line.end.y);
		ft_draw_line(p, line.start, line.end, color);
		return (TRUE);
	}
	else
		return (FALSE);
}
