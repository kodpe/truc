/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_startgame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:01:45 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 18:19:08 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	display_starting_room(t_game *ga, t_img *img)
{
	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_circle(img, \
			mx_pt(img->width / 2 - 15 + ga->waitbox.i, \
				img->height / 2 + 12), 2, SILVER);
	mx_draw_img(img);
	mx_putstr_cen_img(img, STR_START, SILVER);

	mx_putnbr_img(img, \
				mx_pt(img->origin.x + img->width / 2 + 50, \
				img->origin.y + img->height / 2 - 12), \
				ga->waitbox.starting_delay / 5, SILVER);

	if (mx_reset_img(img))
		abort();
}

int	loop_startgame(t_game *ga)
{
	if (ga->waitbox.starting_delay == 0)
		ga->waitbox.starting_delay = 9 * 5; // 9 seconds

	display_starting_room(ga, &ga->waitbox.img);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;
	ga->waitbox.starting_delay--;

	// stop condition
	if (ga->waitbox.starting_delay == 0)
	{
		mlx_loop_end(ga->mlx_ptr);
		return (0);
	}
	// FPS
	mx_wait_fps(5);
	return (0);
}
