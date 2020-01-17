/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:16:24 by ngontjar          #+#    #+#             */
/*   Updated: 2020/01/17 15:19:22 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_gfx.h"

void	ft_die(const char *error_message)
{
	ft_putstr("Error: ");
	ft_putendl(error_message);
	exit(0);
}