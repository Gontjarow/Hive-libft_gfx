/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:38:13 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/17 14:40:55 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clamp(double input, double min, double max)
{
	if (input < min)
	{
		return (min);
	}
	else if (input > max)
	{
		return (max);
	}
	else
	{
		return (input);
	}
}
