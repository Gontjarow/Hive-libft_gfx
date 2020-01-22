/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_region.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:31:38 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/22 13:45:58 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int	ft_get_region(t_xy point)
{
	int outcode;

	outcode = OUTCODE_INSIDE;
	if (point.x < 0)
	{
		outcode |= OUTCODE_LEFT;
	}
	else if (point.x > WIN_WIDTH)
	{
		outcode |= OUTCODE_RIGHT;
	}
	if (point.y < 0)
	{
		outcode |= OUTCODE_TOP;
	}
	else if (point.y > WIN_HEIGHT)
	{
		outcode |= OUTCODE_BOTTOM;
	}
	return (outcode);
}
