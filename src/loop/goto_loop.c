/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:45:12 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 09:49:58 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_active_loop(t_loop *loop, int src_id, int dest_id)
{
	loop->active = 1;
	loop->loop_id = dest_id;
	loop->last_loop_id = src_id;
	loop->time_origin = 0;
	loop->time_elapsed = 0;
	loop->timeout = 0;
	loop->last_frame_duration = 0;
	loop->fps = 0;
	loop->real_fps = 0.0;
	loop->usleep_duration = 0;
}

static void	_setzero_loop(t_game *ga)
{
	ga->lp_menu.active = 0;
	ga->lp_waitopp.active = 0;
	ga->lp_startgame.active = 0;
	ga->lp_game.active = 0;
}

void	goto_loop(t_game *ga, int src_id, int dest_id)
{
	_setzero_loop(ga);

	if (src_id > 0 && dest_id > 0)
		mx_clear_win(&ga->win);

	if (dest_id == LOOP_ID_MENU)
		return (_active_loop(&ga->lp_menu, src_id, dest_id));

	if (dest_id == LOOP_ID_WAITOPP)
		return (_active_loop(&ga->lp_waitopp, src_id, dest_id));

	if (dest_id == LOOP_ID_STARTGAME)
		return (_active_loop(&ga->lp_startgame, src_id, dest_id));

	if (dest_id == LOOP_ID_GAME)
		return (_active_loop(&ga->lp_game, src_id, dest_id));

	if (dest_id == LOOP_EXIT)
	{
		mlx_loop_end(ga->mlx_ptr);
		return ;
	}
	abort(); // TODO fatal error loop bad id
}

int	loop_manager(t_game *ga)
{
	if (ga->lp_menu.active)
		loop_menu(ga);
	if (ga->lp_waitopp.active)
		loop_waitopp(ga);
	if (ga->lp_startgame.active)
		loop_startgame(ga);
	if (ga->lp_game.active)
		loop_game(ga);
	return (0);
}
