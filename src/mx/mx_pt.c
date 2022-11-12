/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_pt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 08:09:02 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"


t_2Dpt	mx_pt(int x, int y)
{
	t_2Dpt	pt;

	pt.x = x;
	pt.y = y;
	return (pt);
}

void	mx_draw_pt(t_img *img, t_2Dpt pt, t_uint hexcolor)
{
	mx_draw_pixel(img, pt.x, pt.y, hexcolor);
}

bool	mx_same_pt(t_2Dpt pt_a, t_2Dpt pt_b)
{
	return (pt_a.x == pt_b.x && pt_a.y == pt_b.y);
}
