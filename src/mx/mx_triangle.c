/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:00:44 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/07 20:06:36 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

t_tri	mx_triangle(t_2Dpt a, t_2Dpt b, t_2Dpt c)
{
	t_tri	tr;

	tr.a = a;
	tr.b = b;
	tr.c = c;
	return (tr);
}

void	mx_draw_triangle(t_img *img, t_tri tr, t_uint hexcolor)
{
	mx_draw_line(img, mx_line(tr.a, tr.b), hexcolor);
	mx_draw_line(img, mx_line(tr.b, tr.c), hexcolor);
	mx_draw_line(img, mx_line(tr.c, tr.a), hexcolor);
}

static int	mx_tri_area(t_2Dpt a, t_2Dpt b, t_2Dpt c)
{
	return (abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)));
}

bool	mx_coll_pt_triangle(t_2Dpt pt, t_tri tr)
{
	int	triangle_area;
	int	point_area_1;
	int	point_area_2;
	int	point_area_3;

	triangle_area = mx_tri_area(tr.a, tr.b, tr.c);
	point_area_1 = mx_tri_area(pt, tr.a, tr.b);
	point_area_2 = mx_tri_area(pt, tr.b, tr.c);
	point_area_3 = mx_tri_area(pt, tr.c, tr.a);
	if (point_area_1 + point_area_2 + point_area_3 == triangle_area)
		return (true);
	// int	sum = point_area_1 + point_area_2 + point_area_3;
	// if (sum > triangle_area - 30 && sum < triangle_area + 30)
		// return (true);
	return (false);
}

bool	mx_coll_xy_triangle(int x, int y, t_tri tr)
{
	return (mx_coll_pt_triangle(mx_pt(x, y), tr));
}
