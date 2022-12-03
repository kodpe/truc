/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:38:58 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 10:02:55y sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


/****************************************************/

static void	_destroy(t_game *ga)
{
	LOG
	destroy_profil(&ga->profil_you);
	destroy_profil(&ga->profil_opp);
	destroy_xpm(ga);

	destroy_board(ga);
	destroy_piece(ga);
	destroy_info(ga);
}

static void	_init(t_game *ga)
{
	load_xpm(ga);
	load_profils(ga);

	create_board(ga);
	create_piece(ga);
	create_info(ga);
}

static void	_display(t_game *ga)
{
	update_board(ga);
	update_piece(ga);
	update_info(ga);
}

void	loop_game(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_game, 30, 0))
		_init(ga);
	//* DISPLAY FUNCTION(S)
	_display(ga);

	//* HERE LOOP INCREMENT VALUE(S)

	//* STOP CONDITION(S) : GOTO LOOP OR MLX_LOOP_END (= EXIT )
	if (ga->evstat.win_cross \
		|| mx_get_ppkey(&ga->evstat, KEYCODE_ESCAPE) \
		|| assert_comfile(ga->profil_opp.path) \
		|| assert_comfile(ga->profil_you.path))
	{
		_destroy(ga);
		goto_loop(ga, LOOP_ID_GAME, LOOP_ID_MENU);
	}
}
