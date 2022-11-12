/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_line_in_ccl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 00:30:38 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

typedef struct s_bham_line_ccl
{
	t_2Dpt	a;
	t_2Dpt	b;
	int		x_slope;
	int		y_slope;
	int		x_delta;
	int		y_delta;
	int		len;
	t_ccl	circle;
}		t_bham_line_ccl;

static void	bresenham_line(t_img *img, t_bham_line_ccl *ham, t_uint hexcolor)
{
	int	error;

	error = ham->x_delta + ham->y_delta;
	while (1)
	{
		if (mx_coll_pt_ccl(ham->a, ham->circle))
			mx_draw_pt(img, ham->a, hexcolor);
		if (mx_same_pt(ham->a, ham->b))
			break ;
		if (2 * error >= ham->y_delta)
		{
			if (ham->a.x == ham->b.x)
				break ;
			error += ham->y_delta;
			ham->a.x += ham->x_slope;
		}
		if (2 * error <= ham->x_delta)
		{
			if (ham->a.y == ham->b.y)
				break ;
			error += ham->x_delta;
			ham->a.y += ham->y_slope;
		}
	}
}

void	mx_draw_line_in_ccl(t_img *img, t_line ln, t_ccl cl, t_uint hexcolor)
{
	t_bham_line_ccl	ham;

	if (mx_sc_pixel_outside_img(img, ln.a.x, ln.a.y) \
		|| mx_sc_pixel_outside_img(img, ln.b.x, ln.b.y))
	{
		c_red();
		mx_log_line("err outside img", ln);
		c_reset();
		return ;
	}
	ham.a = ln.a;
	ham.b = ln.b;
	if (ln.a.x < ln.b.x)
		ham.x_slope = 1;
	else
		ham.x_slope = -1;
	if (ln.a.y < ln.b.y)
		ham.y_slope = 1;
	else
		ham.y_slope = -1;
	ham.x_delta = abs(ln.b.x - ln.a.x);
	ham.y_delta = -abs(ln.b.y - ln.a.y);
	ham.circle = cl;
	bresenham_line(img, &ham, hexcolor);
}
