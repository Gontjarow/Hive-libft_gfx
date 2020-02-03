/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:32:59 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/03 22:32:33 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

t_argb new_argb(int color)
{
	return ((t_argb){
		(color >> 24) & 0xFF,
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		(color) & 0xFF
	});
}

int blend_argb(int foreground, int background)
{
	t_argb fg;
	t_argb bg;
	t_argb blend;
	double ratio;

	fg = new_argb(foreground);
	bg = new_argb(background);

	if (bg.a == 255)
		return (foreground);
	if (fg.a == 255)
		return (background);

	// printf("FG | A %3hhu, R %3hhu, G %3hhu, B %3hhu\n", fg.a, fg.r, fg.g, fg.b);
	// printf("BG | A %3hhu, R %3hhu, G %3hhu, B %3hhu\n", bg.a, bg.r, bg.g, bg.b);

	blend.a = (bg.a == 0 ? 0 : bg.a + fg.a);

	ratio = fg.a / 255.0;
	blend.r = (fg.r * (1 - ratio)) + (bg.r * ratio);
	blend.g = (fg.g * (1 - ratio)) + (bg.g * ratio);
	blend.b = (fg.b * (1 - ratio)) + (bg.b * ratio);

	// printf("=  | A %3hhu, R %3hhu, G %3hhu, B %3hhu\n\n", blend.a, blend.r, blend.g, blend.b);

	return (blend.a << 24 | blend.r << 16 | blend.g << 8 | blend.b);
}
