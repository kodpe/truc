/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:38:58 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 09:42:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// int	init_piece(t_game *ga, t_piece *piece)
// {
// 	piece->img = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(0, 0), mx_vec(160, 160));
// 	piece->type = PIECE_DRAGON;
// 	piece->xpm = ga->xpm[XPM_80W_DRAGON];
// 	if (mx_create_img(&piece->img, "piece"))
// 		return (1);
// 	return (0);
// }

void	load_info(t_game *ga)
{
	t_2Dpt pos;

	pos = mx_pt(200, 800);
	ga->info.img = mx_init_img(ga->mlx_ptr, &ga->win, pos, mx_vec(800, 100));
	if (mx_create_img(&ga->info.img, "game info"))
		abort();
	mx_draw_aabb(&ga->info.img, ga->info.img.box_rel, RED);
	mx_draw_img(&ga->info.img);
}

/****************************************************/

static void	_destroy(t_game *ga)
{
	LOG
	destroy_xpm(ga);
	mx_destroy_img(&ga->img_board);
	mx_destroy_img(&ga->info.img);
	destroy_profil(&ga->profil_you);
	destroy_profil(&ga->profil_opp);
	mlx_loop_end(ga->mlx_ptr); // MLX LOOP END ON SORT
}

static void	_init(t_game *ga)
{
	load_xpm(ga);
	//BOARD
	ga->img_board = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(200, 0), mx_vec(800, 800));
	if (mx_create_img(&ga->img_board, "img_board"))
		abort();
	mx_draw_aabb(&ga->img_board, ga->img_board.box_rel, RED);
	mx_grid_aabb(&ga->img_board, ga->img_board.box_rel, mx_vec(5, 5), DARK_GRAY);
	mx_draw_img(&ga->img_board);

	load_profils(ga);
	load_info(ga);
}

static void	_display(t_game *ga, t_img *img)
{
	// if (rand() % 3 == 0) // cool
		// if (mx_reset_img(img))
			// abort();

	// mx_draw_aabb(img, img->box_rel, SILVER);
	// mx_draw_img(img);
	// mx_putstr_cen_img(img, STR_WAIT, SILVER);
	(void)ga;
	(void)img;
}

void	loop_game(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_game, 30, 0))
		_init(ga);
	_display(ga, NULL);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;

	if (ga->evstat.win_cross)
		return (_destroy(ga));
	if (assert_comfile(ga->profil_opp.path))
		return (_destroy(ga));
	if (assert_comfile(ga->profil_you.path))
		return (_destroy(ga));
}
