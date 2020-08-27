/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 21:55:35 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/26 22:44:28 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "data.h"
#include "libft_gfx.h"

t_image		ft_init_image(void *mlx, int width, int height)
{
	t_image img;

	img.ptr = mlx_new_image(mlx, width, height);

	if (NULL == img.ptr)
		return ((t_image){0});

	img.data = (int*)mlx_get_data_addr(img.ptr, img.bpp, img.width, img.endian);

	if (NULL == (img.data))
		return ((t_image){0});

	img.width = width;
	img.height = height;
}
