/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:52:34 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 03:33:39 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

t_but	mx_init_button(void *mlx_ptr, t_win *win, t_2Dpt origin, t_2Dvec size)
{
	t_but	bt;

	ft_memset(&bt, 0, sizeof(t_but));
	bt.active = 0;
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
	bt->active = 0;
	free(bt->name);
	mx_destroy_img(&bt->img_away);
	mx_destroy_img(&bt->img_over);
	mx_destroy_img(&bt->img_active);
}

#if 1 // OK GOOD
// bouton ou on peut rester appuyé (cf active)
// img active s'affiche tant que mouse down
void	mx_draw_button(t_but *bt, t_evstat *ev)
{
	if (mx_coll_xy_aabb(ev->mouse_x, ev->mouse_y, bt->box_abs))
	{
		if (ev->mouse[MOUSE_BUT_LEFT])
		{
			if (bt->lock == 0)
			{
				mx_draw_img(&bt->img_active);
				bt->active = 1;
				bt->lock = 10;
				return ;
			}
			else
				bt->lock--;
		}
		if (ev->mouse[MOUSE_BUT_LEFT] == 0)
		{
			bt->active = 0;
			bt->lock = 0;
		}
		mx_draw_img(&bt->img_over);
	}
	else
	{
		mx_draw_img(&bt->img_away);
		bt->active = 0;
		bt->lock = 0;
	}
}
#endif

#if 0
// bouton ou on peut rester appuyé (cf active)
// img active s'affiche tant que mouse down
void	mx_draw_button(t_but *bt, t_evstat *ev)
{
	if (bt->active)
	{
		mx_draw_img(&bt->img_active);
		if (mx_coll_xy_aabb(ev->mouse_x, ev->mouse_y, bt->box_abs))
			if (ev->mouse[MOUSE_BUT_LEFT])
				bt->active = 0;
		return ;
	}
	if (mx_coll_xy_aabb(ev->mouse_x, ev->mouse_y, bt->box_abs))
	{
		if (ev->mouse[MOUSE_BUT_LEFT])
			bt->active = 1;
		else
			mx_draw_img(&bt->img_over);
	}
	else
		mx_draw_img(&bt->img_away);
}
#endif
