/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:16:09 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/04 21:23:38 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

int				render(t_program *p)
{
	ft_clear_buffer(&p->buffer);
	draw_view(p);
	// printf("minimap\n\n");
	draw_top_view(p, p->plr.pos, p->plr.dir);
	mlx_put_image_to_window(p->mlx, p->win, p->buffer.ptr, 0, 0);
	return (1);
}
