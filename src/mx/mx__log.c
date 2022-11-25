/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx__log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 19:02:27 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_log_msg(const char *msg)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s\n", msg);
}

void	mx_log_ptr(const char *msg, void *ptr)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:ptr:[%p]\n", msg, ptr);
}

void	mx_log_pt(const char *msg, t_2Dpt pt)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:pt:[%i],[%i]\n", msg, pt.x, pt.y);
}

void	mx_log_vec(const char *msg, t_2Dvec vec)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:vec:[%i],[%i]\n", msg, vec.x, vec.y);
}

void	mx_log_line(const char *msg, t_line ln)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:line:[%i],[%i] -> [%i],[%i]\n", \
					msg, ln.a.x, ln.a.y, ln.b.x, ln.b.y);
}

void	mx_log_circle(const char *msg, t_ccl cl)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:circle: center [%i],[%i] radius [%i]\n", \
					msg, cl.center.x, cl.center.y, cl.radius);
}

void	mx_log_triangle(const char *msg, t_tri tr)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:triangle:[%i],[%i] [%i],[%i] [%i],[%i]\n", \
		msg, tr.a.x, tr.a.y, tr.b.x, tr.b.y, tr.c.x, tr.c.y);
}

void	mx_log_aabb(const char *msg, t_aabb box)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "%s:aabb: origin x[%4i]y[%4i]   length w[%4i]h[%4i]\n", \
				msg, box.origin.x, box.origin.y, box.lenght.x, box.lenght.y);
}

void	mx_log_img(const char *msg, t_img *img)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:image:%s\n", msg, img->name);
	fprintf(stderr, "ptr     [%14p] addr    [%14p]\n", img->ptr, img->addr);
	fprintf(stderr, "mlx_ptr [%14p] win     [%14p]\n", img->mlx_ptr, img->win);
	fprintf(stderr, "origin  x[%4i]  y[%4i] ", img->origin.x, img->origin.y);
	fprintf(stderr, "size    w[%4i]  h[%4i]\n", img->width, img->height);
	// mx_log_aabb("box_rel ", img->box_rel);
	// mx_log_aabb("box_abs ", img->box_abs);
}

void	mx_log_win(const char *msg, t_win *win)
{
	if (!MX_VERBOSE)
		return ;
	fprintf(stderr, "\n");
	fprintf(stderr, "%s:window:\n", msg);
	fprintf(stderr, "ptr     :[%p]\n", win->ptr);
	fprintf(stderr, "size    :[%i]x[%i]\n", win->width, win->height);
	fprintf(stderr, "origin  :[%i],[%i]\n", win->x, win->y);
	fprintf(stderr, "title   :[%s]\n", win->name);
	fprintf(stderr, "mlx_ptr :[%p]\n", win->mlx_ptr);
	// mx_log_aabb("window", win->box);
}
