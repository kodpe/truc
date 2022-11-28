/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:52:34 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 17:15:33y sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

t_but	mx_init_button(void *mlx_ptr, t_win *win, t_2Dpt origin, t_2Dvec size)
{
	t_but	bt;

	ft_memset(&bt, 0, sizeof(t_but));
	bt.origin = origin;
	bt.box_abs = mx_aabb(origin, mx_vec(size.x - 1, size.y - 1));
	bt.box_rel = mx_aabb(mx_pt(0, 0), mx_vec(size.x - 1, size.y - 1));
	bt.img_away = mx_init_img(mlx_ptr, win, origin, size);
	bt.img_over = mx_init_img(mlx_ptr, win, origin, size);
	bt.img_active = mx_init_img(mlx_ptr, win, origin, size);
	return (bt);
}

int	mx_create_button(t_but *bt, char *name)
{
	bt->name = ft_strdup(name);
	if (!bt->name)
		return (1);
	if (mx_create_img(&bt->img_away, name))
		return (1);
	if (mx_create_img(&bt->img_over, name))
		return (1);
	if (mx_create_img(&bt->img_active, name))
		return (1);
	return (0);
}

void	mx_destroy_button(t_but *bt)
{
	free(bt->name);
	mx_destroy_img(&bt->img_away);
	mx_destroy_img(&bt->img_over);
	mx_destroy_img(&bt->img_active);
}

/**
 * > print "?? < value >" if is not boolean value
 * > startl & endl are facultative, both can be null
*/
void	mx_log_bool(char * startl, int value, char *endl)
{
	if (startl)
		fprintf(stderr, "%s", startl);
	if (value == 0)
		fprintf(stderr, "\033[0;31mOFF\033[0m");
	else if (value == 1)
		fprintf(stderr, "\033[0;32m ON\033[0m");
	else
		fprintf(stderr, "\033[0;33m? %i\033[0m", value);
	if (endl)
		fprintf(stderr, "%s", endl);
}

void	mx_log_button(const char *msg, t_but *bt)
{
	int	mb;

	if (!MX_VERBOSE_BUTTON)
		return ;
	fprintf(stderr, "%s:button:%s  ", msg, bt->name);
	fprintf(stderr, "x[%4i] y[%4i]  ", bt->origin.x, bt->origin.y);
	fprintf(stderr, "w[%4i] h[%4i]\n", bt->box_abs.lenght.x, bt->box_abs.lenght.y);
	mx_log_bool("BOX  [", bt->xev_is_in,              "] is_in     ");
	mx_log_bool("[", bt->xev_action_in,          "] action_in     ");
	mx_log_bool("[", bt->xev_action_out,         "] action_out\n");
	mb = MOUSE_BUT_LEFT;
	mx_log_bool("BT-L [", bt->xev_is_press[mb],       "] is_press  ");
	mx_log_bool("[", bt->xev_action_press[mb],   "] action_press  ");
	mx_log_bool("[", bt->xev_action_release[mb], "] action_release\n");
	mb = MOUSE_BUT_RIGHT;
	mx_log_bool("BT-R [", bt->xev_is_press[mb],       "] is_press  ");
	mx_log_bool("[", bt->xev_action_press[mb],   "] action_press  ");
	mx_log_bool("[", bt->xev_action_release[mb], "] action_release\n");
	mb = MOUSE_BUT_MIDDLE;
	mx_log_bool("BT-M [", bt->xev_is_press[mb],       "] is_press  ");
	mx_log_bool("[", bt->xev_action_press[mb],   "] action_press  ");
	mx_log_bool("[", bt->xev_action_release[mb], "] action_release\n");
	mb = MOUSE_SCROLL_UP;
	mx_log_bool("SC-U [", bt->xev_is_press[mb],       "] is_press  ");
	mx_log_bool("[", bt->xev_action_press[mb],   "] action_press  ");
	mx_log_bool("[", bt->xev_action_release[mb], "] action_release\n");
	mb = MOUSE_SCROLL_DOWN;
	mx_log_bool("SC-D [", bt->xev_is_press[mb],       "] is_press  ");
	mx_log_bool("[", bt->xev_action_press[mb],   "] action_press  ");
	mx_log_bool("[", bt->xev_action_release[mb], "] action_release\n");
}

void	mx_handle_button(t_but *bt, t_evstat *ev)
{
	bt->xev_action_in = 0;
	bt->xev_action_out = 0;

	for (int button = 0; button < 6; button++)
	{
		bt->xev_action_press[button] = 0;
		bt->xev_action_release[button] = 0;
	}
	if (false == mx_coll_pt_aabb(ev->mouse_pos, bt->box_abs))
	{
		if (bt->xev_is_in == 1)
			bt->xev_action_out = 1;
		bt->xev_is_in = 0;
		for (int button = 0; button < 6; button++)
			bt->xev_is_press[button] = 0;
		return ;
	}
	if (bt->xev_is_in == 0)
		bt->xev_action_in = 1;
	bt->xev_is_in = 1;

	// scroll up / scroll down not work
	for (int button = 0; button < 6; button++)
	{
		if (ev->mouse[button].event == MX_EVENT_MOUSEDOWM \
			&& mx_coll_pt_aabb(ev->mouse[button].pos, bt->box_abs))
		{
			if (bt->xev_is_press[button] == 0)
				bt->xev_action_press[button] = 1;
			bt->xev_is_press[button] = 1;
		}
		else if (ev->mouse[button].event == MX_EVENT_MOUSEUP)
		{
			if (bt->xev_is_press[button] == 1)
				bt->xev_action_release[button] = 1;
			bt->xev_is_press[button] = 0;
		}
	}
}
