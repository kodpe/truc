/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_profil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/30 02:15:59 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_menu.active = 0;
	LOG
	mx_destroy_button(&ga->bt_quit);
	mx_destroy_button(&ga->pbt_pc_catch);
	mx_destroy_button(&ga->pbt_pc_loose);
	mx_destroy_button(&ga->pbt_pc_moves);
	mx_destroy_button(&ga->pbt_sp_tiles);
	mx_destroy_button(&ga->pbt_wi_forme);
	destroy_userdata(&ga->ud);
}

static void	_init_bt_quit(t_game *ga, t_but *bt)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(150, 50);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	origin = mx_pt_add_vec(origin, \
		mx_vec(ga->win.width / 2 -size.x, \
			ga->win.height / 2 - size.y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "<--"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
}

static void	_init(t_game *ga)
{
	ga->ud = get_userdata();
	_init_bt_quit(ga, &ga->bt_quit);
	profil_init_graph(ga, 23);
	profil_init_graph_but(ga);
	profil_init_txt_part(ga);
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

static void	_display(t_game *ga, t_but *quit)
{
	mx_handle_button(quit, &ga->evstat);
	_basic_update_button(ga, quit);

	mx_handle_button(&ga->pbt_pc_catch, &ga->evstat);
	_basic_update_button(ga, &ga->pbt_pc_catch);

	mx_handle_button(&ga->pbt_pc_loose, &ga->evstat);
	_basic_update_button(ga, &ga->pbt_pc_loose);

	mx_handle_button(&ga->pbt_pc_moves, &ga->evstat);
	_basic_update_button(ga, &ga->pbt_pc_moves);

	mx_handle_button(&ga->pbt_sp_tiles, &ga->evstat);
	_basic_update_button(ga, &ga->pbt_sp_tiles);

	mx_handle_button(&ga->pbt_wi_forme, &ga->evstat);
	_basic_update_button(ga, &ga->pbt_wi_forme);
}

void	loop_profil(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_profil, 30, 0))
		_init(ga);
	//* DISPLAY FUNCTION(S)
	_display(ga, &ga->bt_quit);

	//* HERE LOOP INCREMENT VALUE(S)
	
	//* STOP CONDITION(S) : GOTO LOOP OR MLX_LOOP_END (= EXIT )
	if (mx_get_ppkey(&ga->evstat, KEYCODE_ESCAPE) \
		|| ga->bt_quit.xev_action_release[MOUSE_BUT_LEFT])
	{
		_destroy(ga);
		goto_loop(ga, LOOP_ID_PROFIL, LOOP_ID_MENU);
		return ;
	}
	profil_graph_actions(ga);
}
