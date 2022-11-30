/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profil_init_graph.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:30:44 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 20:39:44by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

float	*_get_values(t_game *ga, int index_data_graph)
{
	t_userdata	*ud;
	
	ud = &ga->ud;
	if (index_data_graph == 7)
		return (ft_tabdup_itof(ud->pieces_catch, 4));
	if (index_data_graph == 11)
		return (ft_tabdup_itof(ud->pieces_loose, 4));
	if (index_data_graph == 15)
		return (ft_tabdup_itof(ud->pieces_moves, 4));
	if (index_data_graph == 19)
		return (ft_tabdup_itof(ud->sp_tiles_use, 4));
	if (index_data_graph == 23)
		return (ft_tabdup_itof(ud->witch_formes, 8));
	return (NULL);
}

void	profil_init_graph(t_game *ga, int index_data_graph)
{
	t_img	img;
	t_2Dpt	origin;
	t_2Dvec	size;

	int	tab_size = 4;
	if (index_data_graph == 23)
		tab_size = 8;

	int	graph_size = 200;
	size = mx_vec(graph_size, graph_size);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&img, "graph"))
		abort();
	// mx_draw_box_img(&img, DARK_GRAY);

	t_line	bgline;
	bgline = mx_line_xy(size.x / 2, 0, size.x / 2, size.y);
	mx_draw_line(&img, bgline, DARK_GRAY);
	bgline = mx_line_xy(0, size.y / 2, size.x, size.y / 2);
	mx_draw_line(&img, bgline, DARK_GRAY);

	if (tab_size == 8)
	{
		t_line l0 = mx_line_wh(size.x / 2, size.y / 2,
							   -size.x / 2 / 1.41, -size.y / 2 / 1.41);
		mx_draw_line(&img, l0, DARK_GRAY);
		t_line l1 = mx_line_wh(size.x / 2, size.y / 2,
							   +size.x / 2 / 1.41, -size.y / 2 / 1.41);
		mx_draw_line(&img, l1, DARK_GRAY);
		t_line l2 = mx_line_wh(size.x / 2, size.y / 2,
							   +size.x / 2 / 1.41, +size.y / 2 / 1.41);
		mx_draw_line(&img, l2, DARK_GRAY);
		t_line l3 = mx_line_wh(size.x / 2, size.y / 2,
							   -size.x / 2 / 1.41, +size.y / 2 / 1.41);
		mx_draw_line(&img, l3, DARK_GRAY);
	}


	float *tab = _get_values(ga, index_data_graph);
	// ft_tabfshow(tab, tab_size, "input values");

	float	max_value = tab[ft_tabf_max(tab, tab_size)];
	if (max_value == 0)
	{
		free(tab);
		mx_draw_img(&img);
		mx_destroy_img(&img);
		return ;
	}
	float	coef = graph_size / 2 / max_value * 0.9;
	for (int i = 0; i < tab_size; i++)
		tab[i] = tab[i] * coef;
#if 0
	printf("max_value [%f]\n", max_value);
	printf("coef [%f]\n", coef);
	ft_tabfshow(tab, tab_size, "scaled values");
#endif

	if (tab_size == 4)
	{
		t_2Dpt center = mx_pt(size.x / 2, size.y / 2);
		t_2Dpt top = mx_pt(size.x / 2, size.y / 2 - tab[0]);
		t_2Dpt right = mx_pt(size.x / 2 + tab[1], size.y / 2);
		t_2Dpt bot = mx_pt(size.x / 2, size.y / 2 + tab[2]);
		t_2Dpt left = mx_pt(size.x / 2 - tab[3], size.y / 2);
		t_tri f_n = mx_triangle(top, right, center);
		t_tri n_w = mx_triangle(right, bot, center);
		t_tri w_d = mx_triangle(bot, left, center);
		t_tri d_f = mx_triangle(left, top, center);

		for (int y = 0; y < size.y / 2; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, d_f))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = 0; y < size.y / 2; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, f_n))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = size.y / 2; y < size.y; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, w_d))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = size.y / 2; y < size.y; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, n_w))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		mx_draw_line(&img, mx_line(top, right), SILVER);
		mx_draw_line(&img, mx_line(right, bot), SILVER);
		mx_draw_line(&img, mx_line(bot, left), SILVER);
		mx_draw_line(&img, mx_line(left, top), SILVER);
	}

	if (tab_size == 8)
	{
		for (int i = 4; i < tab_size; i++)
			tab[i] /= 1.41;
		t_2Dpt center = mx_pt(size.x / 2, size.y / 2);
		t_2Dpt top = mx_pt(size.x / 2, size.y / 2 - tab[0]);
		t_2Dpt right = mx_pt(size.x / 2 + tab[1], size.y / 2);
		t_2Dpt bot = mx_pt(size.x / 2, size.y / 2 + tab[2]);
		t_2Dpt left = mx_pt(size.x / 2 - tab[3], size.y / 2);
		t_2Dpt top_right = mx_pt(size.x / 2 + tab[4], size.y / 2 - tab[4]);
		t_2Dpt bot_right = mx_pt(size.x / 2 + tab[5], size.y / 2 + tab[5]);
		t_2Dpt bot_left = mx_pt(size.x / 2 - tab[6], size.y / 2 + tab[6]);
		t_2Dpt top_left = mx_pt(size.x / 2 - tab[7], size.y / 2 - tab[7]);
		t_tri t0 = mx_triangle(top, top_right, center);
		t_tri t1 = mx_triangle(top_right, right, center);
		t_tri t2 = mx_triangle(right, bot_right, center);
		t_tri t3 = mx_triangle(bot_right, bot, center);
		t_tri t4 = mx_triangle(bot, bot_left, center);
		t_tri t5 = mx_triangle(bot_left, left, center);
		t_tri t6 = mx_triangle(left, top_left, center);
		t_tri t7 = mx_triangle(top_left, top, center);

		for (int y = 0; y < size.y / 2; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, t0))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);
		for (int y = 0; y < size.y / 2; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, t1))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = size.y / 2; y < size.y; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, t2))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);
		for (int y = size.y / 2; y < size.y; y++)
			for (int x = size.x / 2; x < size.x; x++)
				if (mx_coll_xy_triangle(x, y, t3))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = size.y / 2; y < size.y; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, t4))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);
		for (int y = size.y / 2; y < size.y; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, t5))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		for (int y = 0; y < size.y / 2; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, t6))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);
		for (int y = 0; y < size.y / 2; y++)
			for (int x = 0; x < size.x / 2; x++)
				if (mx_coll_xy_triangle(x, y, t7))
					mx_draw_pt(&img, mx_pt(x, y), SILVER);

		mx_draw_line(&img, mx_line(top, top_right), SILVER);
		mx_draw_line(&img, mx_line(top_right, right), SILVER);
		mx_draw_line(&img, mx_line(right, bot_right), SILVER);
		mx_draw_line(&img, mx_line(bot_right, bot), SILVER);
		mx_draw_line(&img, mx_line(bot, bot_left), SILVER);
		mx_draw_line(&img, mx_line(bot_left, left), SILVER);
		mx_draw_line(&img, mx_line(left, top_left), SILVER);
		mx_draw_line(&img, mx_line(top_left, top), SILVER);
	}
	free(tab);
	mx_draw_img(&img);
	mx_destroy_img(&img);
}
