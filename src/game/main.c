/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:08:29 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 18:26:07by sloquet          ###   ########.fr       */
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

int	main(void)
{
	t_game	ga;

	game_init(&ga);
	/*
	time_t	t;
	t_game	ga;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	srand(time(&t));
	ft_memset(&ga, 0, sizeof(t_game));

#ifdef SOLO
	dprintf(2, "\033[1;31mSOLO MODE\033[0m\n");
	abort(); // TODO
#endif

#ifdef MULTIPLAYER

	if (server_exist())
		create_client(&ga);
	else
		create_server(&ga);
	lobby_room(&ga);
# if 0
	lobby_exit(&ga);
	LOG
	dprintf(2, "\033[1;31mEXIT SUCCESS\033[0m\n");
	exit(0);
# else
	mx_destroy_win(&ga.win);
	mx_destroy_mlx(ga.mlx_ptr);
# endif
#endif
	// MLX INIT
	ga.mlx_ptr = mx_init_mlx();
	if (!ga.mlx_ptr)
		abort();
	if (ga.server)
	{
		ga.win = mx_init_win(ga.mlx_ptr, 1200, 900, 0, 0);
		if (mx_create_win(&ga.win, "server"))
			abort();
	}
	if (ga.client)
	{
		ga.win = mx_init_win(ga.mlx_ptr, 1200, 900, 1300, 0);
		if (mx_create_win(&ga.win, "client"))
			abort();
	}
	*/

	ga.img_board = mx_init_img(ga.mlx_ptr, &ga.win, mx_pt(200, 0), mx_vec(800, 800));
	if (mx_create_img(&ga.img_board, "img_board"))
		abort();


	//BOARD
	mx_draw_aabb(&ga.img_board, ga.img_board.box_rel, RED);
	mx_grid_aabb(&ga.img_board, ga.img_board.box_rel, mx_vec(5, 5), DARK_GRAY);
	mx_draw_img(&ga.img_board);

	load_xpm(&ga);

	// DISPLAY

	load_profils(&ga);
	load_info(&ga);

	// mx_move_pt_img(&ga.xpm[1], mx_pt(500, 500));
	// mx_move_pt_img(&ga.xpm[3], mx_pt(540, 540));

	// mx_draw_img(&ga.xpm[1]);


	// mx_fill_img_bg(&ga.xpm[3], &ga.xpm[1]);
	// mx_draw_img(&ga.xpm[3]);

	main_loop(&ga);
	destroy_xpm(&ga);



	mx_destroy_img(&ga.info.img);

	mx_destroy_img(&ga.img_board);

	destroy_profil(&ga.profil_you);
	destroy_profil(&ga.profil_opp);
	mx_destroy_win(&ga.win);
	mx_destroy_mlx(ga.mlx_ptr);
	LOG
	return (0);
}
