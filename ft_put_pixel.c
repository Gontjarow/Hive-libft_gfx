/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:05:14 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/27 03:27:34 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int		ft_put_pixel(t_program *p, int x, int y, int color)
{
	int index;
	int background;

	index = (y * p->buffer.width + x);
	if (index > 0 || index < WIN_WIDTH * WIN_HEIGHT)
	{
		background = p->buffer.data[index];
		p->buffer.data[index] = blend_argb(color, background);
		// printf("wrote pixel %X to index %d\n", p->buffer.data[index], index);
		return (TRUE);
	}
	else
	{
		printf("ignoring put_pixel %d %d (%d)\n", x, y, index);
		return (FALSE);
	}
}
