/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_wantquit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 04:42:47 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	display_room(t_game *ga, t_img *img)
{
	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_img(img);
	mx_putstr_cen_img(img, STR_WANTQUIT, SILVER);

	if (mx_reset_img(&ga->waitbox.img))
		abort();
}

void	loop_wantquit(t_game *ga)
{
	display_room(ga, &ga->waitbox.img);

	// stop condition
	// if button yes
	// if button no
	// if (ga->room_wantquit == 0)
	// FPS
	mx_wait_fps(5);
}
