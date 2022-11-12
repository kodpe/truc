/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_grid_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:49:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 00:55:05 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_grid_circle(t_img *img, t_ccl cl, t_2Dvec nb_tiles, t_uint hexcolor)
{
	int	i;

	i = 1;
	while (i < nb_tiles.y)
	{
		mx_draw_circle(img, cl.center, i * cl.radius / nb_tiles.y, hexcolor);
		i++;
	}

	int	trlen = cl.radius * 1.42;

	int	gap = trlen / nb_tiles.x;

	t_2Dpt	pos;

	pos = mx_pt(cl.center.x, cl.center.y - trlen);
	i = 1;
	while (pos.y <= cl.center.y)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x++;
		pos.y++;
		i++;
	}

	pos = mx_pt(cl.center.x + trlen, cl.center.y);
	i = 1;
	while (pos.y <= cl.center.y + trlen)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x--;
		pos.y++;
		i++;
	}

	pos = mx_pt(cl.center.x, cl.center.y + trlen);
	i = 1;
	while (pos.y >= cl.center.y)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x--;
		pos.y--;
		i++;
	}

	pos = mx_pt(cl.center.x - trlen, cl.center.y);
	i = 1;
	while (pos.y >= cl.center.y - trlen)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x++;
		pos.y--;
		i++;
	}
}
