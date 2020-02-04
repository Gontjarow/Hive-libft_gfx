/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_region.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:31:38 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 21:49:27 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int	ft_get_region(t_xy point, t_clip clip)
{
	int outcode;

	outcode = OUTCODE_INSIDE;
	if (point.x < clip.left)
	{
		outcode |= OUTCODE_LEFT;
	}
	else if (point.x > clip.right)
	{
		outcode |= OUTCODE_RIGHT;
	}
	if (point.y < clip.top)
	{
		outcode |= OUTCODE_TOP;
	}
	else if (point.y > clip.bottom)
	{
		outcode |= OUTCODE_BOTTOM;
	}
	return (outcode);
}
