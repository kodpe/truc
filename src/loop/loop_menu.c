/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/02 15:35:41 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_menu.active = 0;
	LOG
	mx_destroy_button(&ga->bt_play);
	mx_destroy_button(&ga->bt_quit);
	mx_destroy_button(&ga->bt_profil);
}

static void	_init_bt_play(t_game *ga, t_but *bt)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(150, 50);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	origin = mx_pt_add_vec(origin, mx_vec(0, -100));

	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "PLAY"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
}

static void	_init_bt_profil(t_game *ga, t_but *bt)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(150, 50);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	origin = mx_pt_add_vec(origin, mx_vec(0, 0));

	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "PROFIL"))
		abort();

	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
}

static void	_init_bt_quit(t_game *ga, t_but *bt)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(150, 50);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	origin = mx_pt_add_vec(origin, mx_vec(0, 100));

	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "QUIT"))
		abort();

	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
}

static void	_init(t_game *ga)
{
	_init_bt_play(ga, &ga->bt_play);
	_init_bt_profil(ga, &ga->bt_profil);
	_init_bt_quit(ga, &ga->bt_quit);
}

static void	_basic_update_button(t_game *ga, t_but *bt)
{
	if (bt->xev_action_out)
	{
		mx_draw_img(&bt->img_away);
		mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
	}

	if (bt->xev_action_in)
	{
		mx_draw_img(&bt->img_over);
		mx_putstr_cen_img(&bt->img_over, bt->name, SILVER, 0);
	}

	if (bt->xev_action_press[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_active);
		mx_putstr_cen_img(&bt->img_active, bt->name, SILVER, 0);
	}

	if (bt->xev_action_release[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_over);
		mx_putstr_cen_img(&bt->img_over, bt->name, SILVER, 0);
	}
	(void)ga;
}

static void	_display(t_game *ga, t_but *play, t_but *quit, t_but *profil)
{
	mx_handle_button(play, &ga->evstat);
	mx_handle_button(profil, &ga->evstat);
	mx_handle_button(quit, &ga->evstat);
	_basic_update_button(ga, play);
	_basic_update_button(ga, profil);
	_basic_update_button(ga, quit);
}

void	loop_menu(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_menu, 30, 0))
		_init(ga);
	//* DISPLAY FUNCTION(S)
	_display(ga, &ga->bt_play, &ga->bt_quit, &ga->bt_profil);

	//* HERE LOOP INCREMENT VALUE(S)
	
	//* STOP CONDITION(S) : GOTO LOOP OR MLX_LOOP_END (= EXIT )
	if (ga->evstat.win_cross \
		|| ga->bt_quit.xev_action_release[MOUSE_BUT_LEFT])
	{
		_destroy(ga);
		goto_loop(ga, LOOP_ID_MENU, LOOP_EXIT);
		return ;
	}

	if (ga->bt_play.xev_action_release[MOUSE_BUT_LEFT])
	{
		_destroy(ga);
		if (server_exist())
			create_client(ga);
		else
			create_server(ga);
		sc_check_multiplayer(ga);
		if (ga->server)
			goto_loop(ga, LOOP_ID_MENU, LOOP_ID_WAITOPP);
		if (ga->client)
			goto_loop(ga, LOOP_ID_MENU, LOOP_ID_STARTGAME);
		return ;
	}

	if (ga->bt_profil.xev_action_release[MOUSE_BUT_LEFT])
	{
		_destroy(ga);
		goto_loop(ga, LOOP_ID_MENU, LOOP_ID_PROFIL);
		return ;
	}
}
