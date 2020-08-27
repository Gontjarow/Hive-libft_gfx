/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:42:47 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/08 06:29:11 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define VEC2(x,y) (t_xy){x, y}
# define VEC3(x,y,z) (t_xyz){x, y, z}
# define RANGE(start,end) (t_range){start, end}
# define LINE(Ax,Ay,Bx,By) (t_line){VEC2(Ax, Ay), VEC2(Bx, By)}
# define CLIP(top,left,right,bottom) (t_clip){top,left,right,bottom}
# define CIRCLE(pos,r) (t_circle){pos, r}
# define ARGB(a,r,g,b) ((t_argb){a, r, g, b})
# define COLOR(AA,RR,GG,BB) ((AA) << 24 | (RR) << 16 | (GG) << 8 | (BB))

#endif
