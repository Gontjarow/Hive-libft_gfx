/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:25:43 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/24 16:30:49 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

double		ft_map(double in, t_range from, t_range to)
{
	return (to.begin +
		(in - from.begin) * (to.end - to.begin) / (from.end - from.begin));
}
