/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:45:12 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 18:13:39 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// return the current active loop id or -1
int	get_active_loop_id(t_game *ga)
{
	if (ga->lp_waitopp.active)
		return (LOOP_ID_WAITOPP);

	if (ga->lp_startgame.active)
		return (LOOP_ID_STARTGAME);

	if (ga->lp_game.active)
		return (LOOP_ID_GAME);

	if (ga->lp_wantquit.active)
		return (LOOP_ID_WANTQUIT);
	
	return (-1);
}

// return the current active loop ptr or NULL
t_loop	*get_active_loop_ptr(t_game *ga)
{
	if (ga->lp_waitopp.active)
		return (&ga->lp_game);

	if (ga->lp_startgame.active)
		return (&ga->lp_startgame);

	if (ga->lp_game.active)
		return (&ga->lp_game);

	if (ga->lp_wantquit.active)
		return (&ga->lp_wantquit);
	
	return (NULL);
}

static void	_setzero_loop(t_game *ga)
{
	ga->lp_waitopp.active = 0;
	ga->lp_startgame.active = 0;
	ga->lp_game.active = 0;
	ga->lp_wantquit.active = 0;
}

static void	_active_loop(t_loop *loop, int src_id)
{
	loop->active = 1;
	loop->last_loop_id = src_id;
	loop->time_origin = 0;
	loop->time_elapsed = 0;
	// loop->fps = 0;
	loop->timeout = 0;
}

// change loop
void	_goto_loop(t_game *ga, int src_id, int dest_id)
{
	_setzero_loop(ga);

	if (dest_id == LOOP_ID_WAITOPP)
		return (_active_loop(&ga->lp_waitopp, src_id));

	if (dest_id == LOOP_ID_STARTGAME)
		return (_active_loop(&ga->lp_startgame, src_id));

	if (dest_id == LOOP_ID_GAME)
		return (_active_loop(&ga->lp_game, src_id));

	if (dest_id == LOOP_ID_WANTQUIT)
		return (_active_loop(&ga->lp_wantquit, src_id));

	abort(); // TODO fatal error loop bad id
}
