/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_profil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 15:15:45 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_menu.active = 0;
	LOG
	mx_destroy_button(&ga->bt_quit);
}

static void	_init_graph(t_game *ga)
{
	t_img	img;
	t_2Dpt	origin;
	t_2Dvec	size;

	int	tab_size = 4;
	int	graph_size = 200;
	size = mx_vec(graph_size, graph_size);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&img, "graph"))
		abort();
	// mx_draw_box_img(&img, DARK_GRAY);

	float nb_fighter = 5;
	float nb_ninja = 10;
	float nb_witch = 2;
	float nb_dragon = 10;

	float *tab = ft_newtabf(tab_size);
	tab[0] = nb_fighter;
	tab[1] = nb_ninja;
	tab[2] = nb_witch;
	tab[3] = nb_dragon;

	ft_tabfshow(tab, tab_size, "input values");
	float	max_value = tab[ft_tabf_max(tab, tab_size)];
	float	coef = graph_size / 2 / max_value * 0.9;
	printf("max_value [%f]\n", max_value);
	printf("coef [%f]\n", coef);
	for (int i = 0; i < tab_size; i++)
		tab[i] = tab[i] * coef;
	ft_tabfshow(tab, tab_size, "scaled values");

	float ff = tab[0];
	float fn = tab[1];
	float fw = tab[2];
	float fd = tab[3];
	free(tab);
	
	t_2Dpt	center = mx_pt(size.x / 2, size.y / 2);
	t_2Dpt	fighter = mx_pt(size.x / 2, size.y / 2 - (ff));
	t_2Dpt	ninja = mx_pt(size.x / 2 + (fn), size.y / 2);
	t_2Dpt	witch = mx_pt(size.x / 2, size.y / 2 + (fw));
	t_2Dpt	dragon = mx_pt(size.x / 2 - (fd), size.y / 2);

	mx_draw_pt(&img, center, RED);
	mx_draw_pt(&img, fighter, LIME);
	mx_draw_pt(&img, ninja, LIME);
	mx_draw_pt(&img, witch, LIME);
	mx_draw_pt(&img, dragon, LIME);

	t_tri	f_n = mx_triangle(fighter, ninja, center);
	t_tri	n_w = mx_triangle(ninja, witch, center);
	t_tri	w_d = mx_triangle(witch, dragon, center);
	t_tri	d_f = mx_triangle(dragon, fighter, center);

	t_line	bgline;
	bgline = mx_line_xy(size.x / 2, 0, size.x / 2, size.y);
	mx_draw_line(&img, bgline, DARK_GRAY);
	bgline = mx_line_xy(0, size.y / 2, size.x, size.y / 2);
	mx_draw_line(&img, bgline, DARK_GRAY);

	for (int y = 0; y < size.y / 2; y++)
		for (int x = 0; x < size.x / 2; x++)
			if (mx_coll_xy_triangle(x, y, d_f))
				mx_draw_pt(&img, mx_pt(x, y), SILVER);

	for (int y = 0; y < size.y / 2; y++)
		for (int x = size.x / 2; x < size.x; x++)
			if (mx_coll_xy_triangle(x, y, f_n))
				mx_draw_pt(&img, mx_pt(x, y), SILVER);

	for (int y = size.y / 2 ; y < size.y; y++)
		for (int x = 0; x < size.x / 2; x++)
			if (mx_coll_xy_triangle(x, y, w_d))
				mx_draw_pt(&img, mx_pt(x, y), SILVER);

	for (int y = size.y / 2; y < size.y; y++)
		for (int x = size.x / 2; x < size.x; x++)
			if (mx_coll_xy_triangle(x, y, n_w))
				mx_draw_pt(&img, mx_pt(x, y), SILVER);

	mx_draw_line(&img, mx_line(fighter, ninja), SILVER);
	mx_draw_line(&img, mx_line(ninja, witch), SILVER);
	mx_draw_line(&img, mx_line(witch, dragon), SILVER);
	mx_draw_line(&img, mx_line(dragon, fighter), SILVER);

	// mx_draw_line(&img, mx_line(fighter, witch), BLACK);
	// mx_draw_line(&img, mx_line(dragon, ninja), BLACK);


	mx_draw_img(&img);
	mx_destroy_img(&img);
}

static void	_init_bt_quit(t_game *ga, t_but *bt)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(200, 100);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	origin = mx_pt_add_vec(origin, mx_vec(0, 300));
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
	_init_bt_quit(ga, &ga->bt_quit);
	_init_graph(ga);
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
}
