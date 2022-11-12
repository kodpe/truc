/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_circle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 20:08:07by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

static void	mx_cl_pixel(t_img *img, t_2Dpt center, t_2Dvec	gap, t_uint hexcolor)
{
	mx_draw_pixel(img, center.x + gap.x, center.y + gap.y, hexcolor);
	mx_draw_pixel(img, center.x + gap.y, center.y + gap.x, hexcolor);
	mx_draw_pixel(img, center.x - gap.x, center.y + gap.y, hexcolor);
	mx_draw_pixel(img, center.x - gap.y, center.y + gap.x, hexcolor);
	mx_draw_pixel(img, center.x + gap.x, center.y - gap.y, hexcolor);
	mx_draw_pixel(img, center.x + gap.y, center.y - gap.x, hexcolor);
	mx_draw_pixel(img, center.x - gap.x, center.y - gap.y, hexcolor);
	mx_draw_pixel(img, center.x - gap.y, center.y - gap.x, hexcolor);
}

void	mx_draw_circle(t_img *img, t_2Dpt center, int radius, t_uint hexcolor)
{
	t_2Dvec	gap;
	int		d;

	gap = mx_vec(0, radius);
	d = radius - 1;
	while (gap.y >= gap.x)
	{
		mx_cl_pixel(img, center, gap, hexcolor);
		if (d >= 2 * gap.x)
		{
			d = d - 2 * gap.x - 1;
			gap.x++;
		}
		else if (d < 2 * (radius - gap.y))
		{
			d = d + 2 * gap.y - 1;
			gap.y--;
		}
		else
		{
			d = d + 2 * (gap.y - gap.x - 1);
			gap.y--;
			gap.x++;
		}
	}
}

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

	i = 1;
	pos = mx_pt(cl.center.x, cl.center.y - trlen);
	while (pos.y <= cl.center.y)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x++;
		pos.y++;
		i++;
	}

	i = 1;
	pos = mx_pt(cl.center.x + trlen, cl.center.y);
	while (pos.y <= cl.center.y + trlen)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x--;
		pos.y++;
		i++;
	}

	i = 1;
	pos = mx_pt(cl.center.x, cl.center.y + trlen);
	while (pos.y >= cl.center.y)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x--;
		pos.y--;
		i++;
	}

	i = 1;
	pos = mx_pt(cl.center.x - trlen, cl.center.y);
	while (pos.y >= cl.center.y - trlen)
	{
		if (i % gap == 0)
			mx_draw_line_in_ccl(img, mx_line(cl.center, pos), cl, hexcolor);
		pos.x++;
		pos.y--;
		i++;
	}
}

t_ccl	mx_circle(t_2Dpt center, int radius)
{
	t_ccl	new_cl;

	new_cl.center = center;
	new_cl.radius = radius;
	return (new_cl);
}

void	mx_draw_cl(t_img *img, t_ccl cl, t_uint hexcolor)
{
	if (false == mx_ccl_in_aabb(cl, img->box_rel))
	{
		c_red();
		mx_log_circle("mx_draw_circle_topleft() err outside img", cl);
		c_reset();
		return ;
	}
	mx_draw_circle(img, cl.center, cl.radius, hexcolor);
}

void	mx_draw_circle_topleft(t_img *img, t_2Dpt pt, int radius, t_uint hexcolor)
{
	t_2Dpt	center;

	center.x = pt.x + radius;
	center.y = pt.y + radius;
	if (false == mx_ccl_in_aabb(mx_circle(center, radius), img->box_rel))
	{
		c_red();
		mx_log_circle("mx_draw_circle_topleft() err outside img", \
			mx_circle(pt, radius));
		c_reset();
		return ;
	}
	mx_draw_circle(img, center, radius, hexcolor);
}

void	mx_fill_circle_topleft(t_img *img, t_2Dpt pt, int radius, t_uint hexcolor)
{
	t_2Dpt	center;
	int		i;

	center.x = pt.x + radius;
	center.y = pt.y + radius;
	if (false == mx_ccl_in_aabb(mx_circle(center, radius), img->box_rel))
	{
		c_red();
		mx_log_circle("mx_draw_circle_topleft() err outside img", \
			mx_circle(pt, radius));
		c_reset();
		return ;
	}
	i = 0;
	while (i <= radius)
	{
		mx_draw_circle(img, center, i, hexcolor);
		i++;
	}
}

bool	mx_coll_xy_ccl(int x, int y, t_ccl cl)
{
	t_2Dpt	c;
	int		d2;

	c = cl.center;
	d2 = (x - c.x) * (x - c.x) + (y - c.y) * (y - c.y);
	if (d2 > cl.radius * cl.radius)
		return (false);
	return (true);
}

bool	mx_coll_pt_ccl(t_2Dpt pt, t_ccl cl)
{
	return (mx_coll_xy_ccl(pt.x, pt.y, cl));
}

bool	mx_coll_ccl(t_ccl cc1, t_ccl cc2)
{
	t_2Dpt	c1;
	t_2Dpt	c2;
	int		d2;

	c1 = cc1.center;
	c2 = cc2.center;
	d2 = (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
	if (d2 > (cc1.radius + cc2.radius) * (cc1.radius + cc2.radius))
		return (false);
	return (true);
}

bool	mx_ccl_in_ccl(t_ccl cc_inside, t_ccl cc_around)
{
	t_2Dpt	c1;
	t_2Dpt	c2;
	int		d2;

	c1 = cc_inside.center;
	c2 = cc_around.center;
	d2 = (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
	if (d2 + cc_inside.radius * cc_inside.radius \
		> cc_around.radius * cc_around.radius)
		return (false);
	return (true);
}
