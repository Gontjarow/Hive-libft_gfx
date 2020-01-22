/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:12:57 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/22 13:57:54 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int ft_clear_buffer(t_image *image)
{
	int	*data;
	int	pixel;
	int	max;

	data = image->data;
	pixel = 0;
	max = WIN_WIDTH * WIN_HEIGHT;
	while (pixel < max)
	{
		data[pixel] = 0;
		++pixel;
	}
	return (TRUE);
}
