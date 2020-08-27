/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 21:48:44 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/27 03:24:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft_gfx.h"

int ft_set_buffer(t_image *image, int color)
{
	int	*data;
	int	pixel;
	int	max;

	data = image->data;
	pixel = 0;
	max = WIN_WIDTH * WIN_HEIGHT;
	while (pixel < max)
	{
		data[pixel] = color;
		++pixel;
	}
	return (TRUE);
}
