/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:05:14 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/03 22:34:24 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int		ft_put_pixel(t_program *p, int x, int y, int color)
{
	int index;
	int background;

	index = (y * p->buffer.line_bytes + x);
	if (index > 0 || index < WIN_WIDTH * WIN_HEIGHT)
	{
		background = p->buffer.data[index];
		p->buffer.data[index] = blend_argb(color, background);
		return (TRUE);
	}
	else
	{
		printf("ignoring put_pixel %d %d (%d)\n", x, y, index);
		return (FALSE);
	}
}
