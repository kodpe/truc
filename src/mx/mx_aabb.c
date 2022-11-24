/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_aabb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 15:54:21 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

t_aabb	mx_aabb(t_2Dpt origin, t_2Dvec lenght)
{
	t_aabb	box;

	box.origin = origin;
	box.lenght = lenght;
	return (box);
}

void	mx_draw_aabb(t_img *img, t_aabb box, t_uint hexcolor)
{
	t_2Dpt	max;
	t_2Dpt	ori;

	if (false == mx_aabb_in_aabb(box, img->box_rel))
	{
		c_red();
		mx_log_aabb("mx_draw_aabb() err outside img", box);
		c_reset();
		return ;
	}
	max = mx_pt_add_vec(box.origin, box.lenght);
	ori = box.origin;
	mx_draw_line(img, mx_line(ori, mx_pt(max.x, ori.y)), hexcolor);
	mx_draw_line(img, mx_line(ori, mx_pt(ori.x, max.y)), hexcolor);
	mx_draw_line(img, mx_line(max, mx_pt(max.x, ori.y)), hexcolor);
	mx_draw_line(img, mx_line(max, mx_pt(ori.x, max.y)), hexcolor);
}

void	mx_fill_aabb(t_img *img, t_aabb box, t_uint hexcolor)
{
	t_2Dpt	max;
	t_2Dpt	ori;
	int		y;

	if (false == mx_aabb_in_aabb(box, img->box_rel))
	{
		c_red();
		mx_log_aabb("mx_fill_aabb() err outside img", box);
		c_reset();
		return ;
	}
	max = mx_pt_add_vec(box.origin, box.lenght);
	ori = box.origin;
	y = ori.y;
	while (y <= max.y)
	{
		mx_draw_line(img, mx_line(mx_pt(ori.x, y), mx_pt(max.x, y)), hexcolor);
		y++;
	}
}

void	mx_grid_aabb(t_img *img, t_aabb box, t_2Dvec nb_tiles, t_uint hexcolor)
{
	t_2Dpt	a;
	t_2Dpt	b;
	int		i;

	if (false == mx_aabb_in_aabb(box, img->box_rel))
	{
		c_red();
		mx_log_aabb("mx_grid_aabb() err outside img", box);
		c_reset();
		return ;
	}
	i = 1;
	while (i < nb_tiles.x)
	{
		a = mx_pt(box.origin.x + i * box.lenght.x / nb_tiles.x, box.origin.y);
		b = mx_pt(a.x, box.origin.y + box.lenght.y);
		mx_draw_line(img, mx_line(a, b), hexcolor);
		i++;
	}
	i = 1;
	while (i < nb_tiles.y)
	{
		a = mx_pt(box.origin.x, box.origin.y + i * box.lenght.y / nb_tiles.y);
		b = mx_pt(box.origin.x + box.lenght.x, a.y);
		mx_draw_line(img, mx_line(a, b), hexcolor);
		i++;
	}
}

bool	mx_coll_xy_aabb(int x, int y, t_aabb box)
{
	if (x < box.origin.x || x > box.origin.x + box.lenght.x)
		return (false);
	if (y < box.origin.y || y > box.origin.y + box.lenght.y)
		return (false);
	return (true);
}

bool	mx_coll_pt_aabb(t_2Dpt pt, t_aabb box)
{
	return (mx_coll_xy_aabb(pt.x, pt.y, box));
}

bool	mx_coll_aabb(t_aabb box1, t_aabb box2)
{
	if (box1.origin.x > box2.origin.x + box2.lenght.x)
		return (false);
	if (box1.origin.x + box1.lenght.x <= box2.origin.x)
		return (false);
	if (box1.origin.y > box2.origin.y + box2.lenght.y)
		return (false);
	if (box1.origin.y + box1.lenght.y <= box2.origin.y)
		return (false);
	return (true);
}

bool	mx_aabb_in_aabb(t_aabb box_inside, t_aabb box_around)
{
	t_2Dpt	inside_max;
	t_2Dpt	around_max;

	inside_max = mx_pt_add_vec(box_inside.origin, box_inside.lenght);
	around_max = mx_pt_add_vec(box_around.origin, box_around.lenght);
	if (box_inside.origin.x < box_around.origin.x)
		return (false);
	if (box_inside.origin.y < box_around.origin.y)
		return (false);
	if (inside_max.x > around_max.x)
		return (false);
	if (inside_max.y > around_max.y)
		return (false);
	return (true);
}

bool	mx_ccl_in_aabb(t_ccl cl, t_aabb box_around)
{
	t_aabb	box_cl;

	box_cl.origin = mx_pt(cl.center.x - cl.radius, cl.center.y - cl.radius);
	box_cl.lenght = mx_vec(cl.radius * 2, cl.radius * 2);
	if (mx_aabb_in_aabb(box_cl, box_around))
		return (true);
	return (false);
}
