/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx__log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 19:31:55 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_log_msg(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
}

void	mx_log_ptr(const char *msg, void *ptr)
{
	fprintf(stderr, "%s:ptr:[%p]\n", msg, ptr);
}

void	mx_log_pt(const char *msg, t_2Dpt pt)
{
	fprintf(stderr, "%s:pt:[%i],[%i]\n", msg, pt.x, pt.y);
}

void	mx_log_vec(const char *msg, t_2Dvec vec)
{
	fprintf(stderr, "%s:vec:[%i],[%i]\n", msg, vec.x, vec.y);
}

void	mx_log_line(const char *msg, t_line ln)
{
	fprintf(stderr, "%s:line:[%i],[%i] -> [%i],[%i]\n", \
					msg, ln.a.x, ln.a.y, ln.b.x, ln.b.y);
}

void	mx_log_circle(const char *msg, t_ccl cl)
{
	fprintf(stderr, "%s:circle: center [%i],[%i] radius [%i]\n", \
					msg, cl.center.x, cl.center.y, cl.radius);
}

void	mx_log_aabb(const char *msg, t_aabb box)
{
	fprintf(stderr, "%s:aabb: origin [%i],[%i] lenght [%i],[%i]\n", \
				msg, box.origin.x, box.origin.y, box.lenght.x, box.lenght.y);
}

void	mx_log_img(const char *msg, t_img *img)
{
	fprintf(stderr, "%s:image:\n", msg);
	fprintf(stderr, "ptr     :[%p]", img->ptr);
	fprintf(stderr, "height  :[%i]", img->height);
	fprintf(stderr, "width   :[%i]", img->width);
	fprintf(stderr, "addr    :[%p]", img->addr);
	fprintf(stderr, "mlx_ptr :[%p]", img->mlx_ptr);
	mx_log_aabb("image", img->box);
}

void	mx_log_win(const char *msg, t_win *win)
{
	fprintf(stderr, "%s:window:\n", msg);
	fprintf(stderr, "ptr     :[%p]", win->ptr);
	fprintf(stderr, "height  :[%i]", win->height);
	fprintf(stderr, "width   :[%i]", win->width);
	fprintf(stderr, "title   :[%s]", win->title);
	fprintf(stderr, "mlx_ptr :[%p]", win->mlx_ptr);
	mx_log_aabb("window", win->box);
}
