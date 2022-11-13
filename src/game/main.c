/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:08:29 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 18:36:44 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_piece(t_game *ga, t_piece *piece)
{
	piece->img = mx_init_img(ga->mlx_ptr, &ga->win, mx_pt(0, 0), mx_vec(160, 160));
	piece->type = PIECE_DRAGON;
	piece->xpm = ga->xpm[XPM_80W_DRAGON];
	if (mx_create_img(&piece->img, "piece"))
		return (1);
	return (0);
}

void	display_board(t_game *ga)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			t_case current = ga->board[y][x];
			if (current.mouseover)
				mx_draw_aabb(&ga->img_board, current.abs_box, WHITE);
		}
	}
	mx_draw_img(&ga->img_board);
}

// int	init_board(t_game *ga)

int	main(void)
{
	t_game	ga;

	ga.mlx_ptr = mx_init_mlx();
	ga.win = mx_init_win(ga.mlx_ptr, 1200, 900);
	if (mx_create_win(&ga.win, "Yamayuba"))
		abort();

	load_xpm(&ga);

	// t_2Dpt	pos = mx_pt(200,0);
	// t_2Dvec	size = mx_vec(800, 800);
	// ga.global_checkboard = mx_init_img(ga.mlx_ptr, &ga.win, pos, size);
	// if (mx_create_img(&ga.global_checkboard, "global checkboard"))
	// 	abort();
	
	// mx_grid_aabb(&ga.global_checkboard, ga.global_checkboard.box_rel, mx_vec(5, 5), DARK_GRAY);



	// DISPLAY

	// display_board(&ga);

	main_loop(&ga);
	destroy_xpm(&ga);
	// mx_destroy_img(&ga.global_checkboard);
	return (0);
}
