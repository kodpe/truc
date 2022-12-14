/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 19:48:24 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

typedef struct s_bham_line
{
	t_2Dpt	a;
	t_2Dpt	b;
	int		x_slope;
	int		y_slope;
	int		x_delta;
	int		y_delta;
	int		len;
}		t_bham_line;

static void	bresenham_line(t_img *img, t_bham_line *ham, t_uint hexcolor)
{
	int	error;

	error = ham->x_delta + ham->y_delta;
	while (1)
	{
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

t_line	mx_line_wh(int x, int y, int w, int h)
{
	t_line	ln;

	ln.a = mx_pt(x, y);
	ln.b = mx_pt(x + w, y + h);
	return (ln);
}

t_line	mx_line_xy(int x1, int y1, int x2, int y2)
{
	t_line	ln;

	ln.a = mx_pt(x1, y1);
	ln.b = mx_pt(x2, y2);
	return (ln);
}

t_line	mx_line(t_2Dpt pt_a, t_2Dpt pt_b)
{
	t_line	ln;

	ln.a = pt_a;
	ln.b = pt_b;
	return (ln);
}

bool	mx_same_line(t_line ln_k, t_line ln_q)
{
	return (mx_same_pt(ln_k.a, ln_q.a) && mx_same_pt(ln_k.b, ln_q.b));
}

void	mx_draw_line(t_img *img, t_line ln, t_uint hexcolor)
{
	t_bham_line	ham;

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
	bresenham_line(img, &ham, hexcolor);
}
