/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:38:17 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/03 00:12:41 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_piece(t_game *ga)
{
	mx_destroy_button(&ga->pc.bt);
}

void	update_piece(t_game *ga)
{
	t_but	*bt;

	bt = &ga->pc.bt;
	mx_handle_button(bt, &ga->evstat);
	if (bt->xev_action_out)
	{
		mx_draw_img(&bt->img_away);
	}

	if (bt->xev_action_in)
	{
		mx_draw_img(&bt->img_over);
	}

	if (bt->xev_action_press[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_active);
	}

	if (bt->xev_action_release[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_over);
		printf("PIECE is release\n");
	}

	if (bt->xev_is_press[MOUSE_BUT_LEFT])
	{
		printf("PIECE is press\n");
	}
}

void	create_piece(t_game *ga)
{
	t_2Dpt	case_id;
	t_2Dpt	origin;
	t_2Dvec	size;
	t_but	*bt;

	ga->pc.type = PIECE_DRAGON;
	case_id = mx_pt(1, 1);

	bt = &ga->pc.bt;
	origin = ga->board[case_id.x][case_id.y].bt.origin;
	size = mx_vec(160, 160);
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "piece"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, BLUE);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, ORCHID);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, YELLOW);

	t_img	*xpm = &ga->xpm[ga->pc.type];
	t_2Dpt	xpmpos = mx_pt(origin.x + 40, origin.y + 40);
	xpm->origin = xpmpos;

	mx_draw_img(&bt->img_away);
	mx_draw_img(xpm);

	//link
	ga->board[case_id.x][case_id.y].piece = &ga->pc;
}

