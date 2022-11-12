/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx__log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 05:07:15 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_log_msg(const char *msg)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s\n", msg);
}

void	mx_log_ptr(const char *msg, void *ptr)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:ptr:[%p]\n", msg, ptr);
}

void	mx_log_pt(const char *msg, t_2Dpt pt)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:pt:[%i],[%i]\n", msg, pt.x, pt.y);
}

void	mx_log_vec(const char *msg, t_2Dvec vec)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:vec:[%i],[%i]\n", msg, vec.x, vec.y);
}

void	mx_log_line(const char *msg, t_line ln)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:line:[%i],[%i] -> [%i],[%i]\n", \
					msg, ln.a.x, ln.a.y, ln.b.x, ln.b.y);
}

void	mx_log_circle(const char *msg, t_ccl cl)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:circle: center [%i],[%i] radius [%i]\n", \
					msg, cl.center.x, cl.center.y, cl.radius);
}

void	mx_log_aabb(const char *msg, t_aabb box)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:aabb: origin [%i],[%i] lenght [%i],[%i]\n", \
				msg, box.origin.x, box.origin.y, box.lenght.x, box.lenght.y);
}

void	mx_log_img(const char *msg, t_img *img)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:image:\n", msg);
	fprintf(stderr, "ptr     :[%p]\n", img->ptr);
	fprintf(stderr, "height  :[%i]\n", img->height);
	fprintf(stderr, "width   :[%i]\n", img->width);
	fprintf(stderr, "addr    :[%p]\n", img->addr);
	fprintf(stderr, "mlx_ptr :[%p]\n", img->mlx_ptr);
	fprintf(stderr, "win_ptr :[%p]", img->win->ptr);
	fprintf(stderr, "origin  :[%i],[%i]\n", img->origin.x, img->origin.y);
	mx_log_aabb("img box_rel", img->box_rel);
	mx_log_aabb("img box_abs", img->box_abs);
}

void	mx_log_win(const char *msg, t_win *win)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:window:\n", msg);
	fprintf(stderr, "ptr     :[%p]\n", win->ptr);
	fprintf(stderr, "height  :[%i]\n", win->height);
	fprintf(stderr, "width   :[%i]\n", win->width);
	fprintf(stderr, "title   :[%s]\n", win->name);
	fprintf(stderr, "mlx_ptr :[%p]", win->mlx_ptr);
	mx_log_aabb("window", win->box);
}
