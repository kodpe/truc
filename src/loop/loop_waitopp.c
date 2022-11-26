/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_waitopp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 18:51:05 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	display(t_game *ga, t_img *img)
{
	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_circle(img, \
				mx_pt(img->width / 2 - 15 + ga->waitbox.i, \
					img->height / 2 + 12), 2, SILVER);

	// mx_draw_aabb(img, mx_aabb(mx_pt(img->width / 2 - 72, img->height / 2 - 24), mx_vec(144, 16)), RED);

	mx_draw_img(img);
	mx_putstr_cen_img(img, STR_WAIT, SILVER);

	if (rand() % 3 == 0) // cool
		if (mx_reset_img(&ga->waitbox.img))
			abort();
}

int	loop_waitopp(t_game *ga)
{
	display(ga, &ga->waitbox.img);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;

	///TODO FIXME why this display nothing
	// mx_log_event("waitopp", ga->lp_waitopp.evstat.mlx_keycode);
	// stop condition
	if (ga->lp_waitopp.evstat.win_exit_cross
		|| ga->lp_waitopp.evstat.key_escape)
	{
		mlx_loop_end(ga->mlx_ptr);
		lobby_exit(ga);
		LOG
		exit(0);
	}
	if (dir_size(PATH_COMDIR) == 2)
	{
		if (ga->server == true && ga->profil_opp.file == NULL)
		{
			receive_opponent(ga);
			_goto_loop(ga, LOOP_ID_WAITOPP, LOOP_ID_STARTGAME);
		}
		return (0);
	}
	// FPS
	mx_wait_fps(5);
	return (0);
}
