/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_waitopp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 02:18:15by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_waitopp.active = 0;
	LOG
	log_com(ga);
	unlink_sc(ga->profil_you.path);
	free(ga->profil_you.file);
	free(ga->profil_you.name);
	free(ga->profil_you.path);
	free(ga->profil_opp.file);
	free(ga->profil_opp.name);
	free(ga->profil_opp.path);
	mx_destroy_img(&ga->waitbox.img);

	mx_destroy_button(&ga->bt);
	// mx_destroy_img(&ga->testborder); //NEW
	// mx_destroy_img(&ga->testborder2); //NEW
	// mx_destroy_img(&ga->testborder3); //NEW
	mlx_loop_end(ga->mlx_ptr);
}

static void	_init(t_game *ga)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(500, 250);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();

	ga->bt = mx_init_button(ga->mlx_ptr, &ga->win, mx_pt(200, 700), mx_vec(200, 50));
	if (mx_create_button(&ga->bt, "PLAY"))
		abort();

	// mx_destroy_img(&ga->bt.img_active);
	// ga->bt.img_active = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(205, 705), mx_vec(1, 1));
	// if (mx_create_xpm_img(&ga->bt.img_active, XPM_PATH_80W_SAMURAI))
	// 	abort();

	// mx_draw_line(&ga->bt.img_away, mx_line_xy(150, 50, 200, 0), SILVER);

	mx_draw_aabb(&ga->bt.img_away, ga->bt.box_rel, DARK_GRAY);
	// mx_draw_lt_border_aabb(&ga->bt.img_over, ga->bt.box_rel, 5, SILVER);
	mx_draw_pn_border_aabb(&ga->bt.img_over, ga->bt.box_rel, 3, SILVER);
	mx_draw_pn_border_aabb(&ga->bt.img_active, ga->bt.box_rel, 6, SILVER);

	// ga->testborder = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(0, 0), mx_vec(1200, 900));
	// if (mx_create_img(&ga->testborder, "test border"))
		// abort();
	// ga->testborder2 = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(500, 200), mx_vec(200, 100));
	// if (mx_create_img(&ga->testborder2, "test border"))
	// 	abort();
	// ga->testborder3 = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(800, 200), mx_vec(200, 100));
	// if (mx_create_img(&ga->testborder3, "test border"))
	// 	abort();

	// mx_draw_lt_border_aabb(&ga->testborder, ga->testborder.box_rel, 5, SILVER);

	// mx_draw_pn_border_aabb(&ga->testborder2, ga->testborder2.box_rel, 5, SILVER);

	// mx_draw_pn_border_aabb(&ga->testborder3, ga->testborder3.box_rel, 5, SILVER);

	// mx_fill_aabb(&ga->testborder3, mx_aabb(mx_pt(5, 5), mx_vec(190, 90)), DARK_GRAY);

	// mx_draw_img(&ga->testborder);
	// mx_draw_img(&ga->testborder2);
	// mx_draw_img(&ga->testborder3);

			mx_draw_img(&ga->bt.img_away);
}

static void	_display(t_game *ga, t_img *img)
{
	if (rand() % 3 == 0) // cool
		if (mx_reset_img(img))
			abort();
	mx_handle_button(&ga->bt, &ga->evstat);

		if (ga->bt.xev_action_out)
			mx_draw_img(&ga->bt.img_away);
		if (ga->bt.xev_action_in)
			mx_draw_img(&ga->bt.img_over);
		if (ga->bt.xev_action_press[MOUSE_BUT_LEFT])
			mx_draw_img(&ga->bt.img_active);
		if (ga->bt.xev_action_release[MOUSE_BUT_LEFT])
			mx_draw_img(&ga->bt.img_over);
		if (ga->bt.xev_is_press[MOUSE_BUT_LEFT])
		{
			printf("GG oui je reste appuyé\n");
			ga->bt.origin = mx_pt(ga->evstat.mouse_pos.x -100, ga->evstat.mouse_pos.y - 25);
			ga->bt.box_abs.origin = ga->bt.origin;
			ga->bt.img_away.origin = ga->bt.origin;
			ga->bt.img_over.origin = ga->bt.origin;
			ga->bt.img_active.origin = ga->bt.origin;
		}

	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_circle(img, \
				mx_pt(img->width / 2 - 15 + ga->waitbox.i, \
					img->height / 2 + 12), 2, SILVER);
	mx_draw_img(img);
	mx_putstr_cen_img(img, STR_WAIT, SILVER);
}

void	loop_waitopp(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_waitopp, 50, 0))
		_init(ga);
	_display(ga, &ga->waitbox.img);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;
	

	if (ga->evstat.win_cross)
		return (_destroy(ga));
	if (dir_size(PATH_COMDIR) == 2 && ga->profil_opp.path == NULL)
	{
			receive_opponent(ga);
			if (assert_comfile(ga->profil_opp.path))
				return (_destroy(ga));
			if (assert_comfile(ga->profil_you.path))
				return (_destroy(ga));
			// passage a startgame avec new img init
			mx_destroy_img(&ga->waitbox.img); 
			goto_loop(ga, LOOP_ID_WAITOPP, LOOP_ID_STARTGAME);
	}
}
