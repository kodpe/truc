/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_waiting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 03:01:02 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	display_waiting_room(t_game *ga, t_img *img)
{
	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_circle(img, \
				mx_pt(img->width / 2 - 15 + ga->waitbox.i, \
					img->height / 2 + 12), 2, SILVER);
	mx_draw_img(img);
	mx_putstr_cen_img(img, STR_WAIT, SILVER);

	if (rand() % 3 == 0) // cool
		if (mx_reset_img(&ga->waitbox.img))
			abort();
}

int	loop_waiting(t_game *ga)
{
	display_waiting_room(ga, &ga->waitbox.img);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;

	// stop condition
	if (dir_size(PATH_COMDIR) == 2)
	{
		if (ga->server == true && ga->profil_opp.file == NULL)
			receive_opponent(ga);
		return (0);
	}
	// FPS
	mx_wait_fps(5);
	return (0);
}
