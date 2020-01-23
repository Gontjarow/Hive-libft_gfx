/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:05:14 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/23 21:19:02 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int		ft_put_pixel(t_program *p, int x, int y, int color)
{
	int index;

	index = (y * p->buffer.line_bytes + x);
	if (index < 0 || index > WIN_WIDTH * WIN_HEIGHT)
	{
		printf("ignoring put_pixel %d %d (%d)\n", x, y, index);
		return (FALSE);
	}
	p->buffer.data[index] = color;
	return (TRUE);
}
