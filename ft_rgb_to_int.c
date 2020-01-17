/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:36:49 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/17 15:22:51 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int		ft_rgb_to_int(double r, double g, double b)
{
	int color;

	r = ft_clamp(r, 0, 1);
	g = ft_clamp(g, 0, 1);
	b = ft_clamp(b, 0, 1);
	color = 0;
	color |= (int)(r * 255) << 16;
	color |= (int)(g * 255) << 8;
	color |= (int)(b * 255);
	return (color);
}
