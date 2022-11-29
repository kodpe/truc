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

	mx_destroy_img(&ga->txi.img);
	free(ga->txi.buffer);
	destroy_xpm(ga);
	mx_destroy_img(&ga->img_board);
	mx_destroy_img(&ga->info.img);
	destroy_profil(&ga->profil_you);
	destroy_profil(&ga->profil_opp);
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

	ga->txi.img = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(600, 850), mx_vec(200, 20));
	if (mx_create_img(&ga->txi.img, "txt input txi"))
		abort();

	ga->txi.buffer = ft_calloc(sizeof(char *) * 21);
	ga->txi.maxlen = 21;
	if (!ga->txi.buffer)
		abort();
	printf("buffer %li:[%s]\n", ft_strlen(ga->txi.buffer), ga->txi.buffer);
}

static void	_display(t_game *ga, t_img *img)
{
	// if (rand() % 3 == 0) // cool
		// if (mx_reset_img(img))
			// abort();

	mx_draw_aabb(&ga->txi.img, ga->txi.img.box_rel, SILVER);
	mx_draw_img(&ga->txi.img);
	mx_putstr_cen_img(&ga->txi.img, ga->txi.buffer, SILVER, 0);
	(void)img;
}

void	loop_game(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_game, 30, 0))
		_init(ga);
	//* DISPLAY FUNCTION(S)
	_display(ga, NULL);

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
