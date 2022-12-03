/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:55:20 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/02 23:50:19 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_board(t_game *ga)
{
	mx_destroy_button(&ga->fullboard);
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			mx_destroy_button(&ga->board[y][x].bt);
}

static void	_init_case_but(t_game *ga, t_but *bt, t_2Dpt board_origin , \
									t_2Dvec board_size, t_2Dpt case_id)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(board_size.x / 5, board_size.y / 5);
	origin.x = board_origin.x + case_id.x * size.x;
	origin.y = board_origin.y + case_id.y * size.y;
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "CASE"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, LIME);
	mx_draw_img(&bt->img_away);
	char	*n1 = ft_itoa(case_id.x);
	char	*n2 = ft_itoa(case_id.y);
	char	*tmp = ft_strjointri(n1, ",", n2);
	free(n1);
	free(n2);
	// mx_putstr_cen_img(&bt->img_away, tmp, SILVER, 0);
	free(tmp);
}

void	create_board(t_game *ga)
{
	t_2Dpt	board_origin;
	t_2Dvec	board_size;
	int		bdsize;

	bdsize = 800;
	board_origin = mx_pt(200, 0);
	board_size = mx_vec(bdsize, bdsize);

	ga->fullboard = mx_init_button(ga->mlx_ptr, &ga->win, board_origin, board_size);
	if (mx_create_button(&ga->fullboard, "fullboard"))
		abort();
	// t_but	*bt = &ga->fullboard;

	// mx_draw_aabb(bt.im, ga->img_board.box_rel, RED);
	// mx_grid_aabb(&ga->img_board, ga->img_board.box_rel, mx_vec(5, 5), DARK_GRAY);
	// mx_draw_img(&ga->img_board);

	ft_memset(&ga->board, CASE_NORMAL, sizeof(ga->board));
	t_2Dpt	case_id;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			case_id = mx_pt(x, y);
			_init_case_but(ga, &ga->board[y][x].bt, board_origin, board_size, case_id);
			ga->board[y][x].case_id = case_id;

		}
	}
}
