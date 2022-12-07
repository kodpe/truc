/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:38:17 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/07 21:45:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_piece(t_game *ga)
{
	mx_destroy_button(&ga->pc.bt);
}

void	update_piece(t_game *ga, t_piece *pc)
{
	t_but	*bt;

	bt = &pc->bt;
	mx_handle_button(bt, &ga->evstat);
	if (bt->xev_action_out)
	{
		mx_draw_img(&bt->img_away);
		mx_draw_img(pc->xpm);
	}

	if (bt->xev_action_in)
	{
		mx_draw_img(&bt->img_over);
		mx_draw_img(pc->xpm);
	}

	if (bt->xev_action_press[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_active);
		mx_draw_img(pc->xpm);
		if (pc->active)
			pc->active = 0;
		else
			pc->active = 1;
	}

	if (bt->xev_action_release[MOUSE_BUT_LEFT])
	{
		mx_draw_img(&bt->img_over);
		mx_draw_img(pc->xpm);
		printf("PIECE is release\n");
	}

	if (bt->xev_is_press[MOUSE_BUT_LEFT])
	{
		printf("PIECE is press\n");
		pc->is_press = 1;
	}

	if (ga->evstat.mouse[MOUSE_BUT_LEFT].event == MX_EVENT_MOUSEUP)
	{
		pc->is_press = 0;
		return ;
	}
	if (pc->is_press)
	{
		t_aabb	mousemax_box = mx_aabb(mx_pt_add_vec(ga->fullboard.origin, mx_div_vec(pc->bt.box_abs.lenght, 2)), \
			mx_vec_sub_vec(ga->fullboard.box_abs.lenght, pc->bt.box_abs.lenght));
		if (false == mx_coll_pt_aabb(ga->evstat.mouse_pos, mousemax_box))
		{
			// pc->is_press = 0;
			return ;
		}
void move_piece(t_game * ga, int board_x, int board_y, t_piece_t type);
		if (ga->evstat.mouse_pos.x - 80 != ga->pc.bt.origin.x || ga->evstat.mouse_pos.y - 80 != ga->pc.bt.origin.y)
			move_piece(ga, 2, 2, PIECE_WITCH);
	}
}

void	move_piece(t_game *ga, int board_x, int board_y, t_piece_t type)
{
	printf("MOVE PIECE\n");
	mx_destroy_button(&ga->pc.bt);
	t_img	img = mx_init_img(ga->mlx_ptr, &ga->win, ga->pc.bt.origin, ga->pc.bt.box_abs.lenght);
	if (mx_create_img(&img, "erase case"))
		abort();
	// mx_fill_img(&img, LIME);

	mx_draw_img(&img);
	mx_destroy_img(&img);

	t_2Dpt	case_id;
	t_2Dpt	origin;
	t_2Dvec	size;
	t_but	*bt;

	ga->pc.type = type;
	case_id = mx_pt(board_x, board_y);

	bt = &ga->pc.bt;
	origin = ga->board[case_id.x][case_id.y].bt.origin;

	//!
	origin = ga->evstat.mouse_pos;
	origin.x -= 80;
	origin.y -= 80;

	size = mx_vec(160, 160);
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "piece"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, BLUE);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, ORCHID);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, YELLOW);

	ga->pc.xpm = &ga->xpm[ga->pc.type];
	t_2Dpt	xpmpos = mx_pt(origin.x + 40, origin.y + 40);
	ga->pc.xpm->origin = xpmpos;

	mx_draw_img(&bt->img_away);
	mx_draw_img(ga->pc.xpm);

	//link
	ga->board[case_id.x][case_id.y].piece = &ga->pc;

}

void	create_piece(t_game *ga, int board_x, int board_y, t_piece_t type)
{
	t_2Dpt	case_id;
	t_2Dpt	origin;
	t_2Dvec	size;
	t_but	*bt;

	ga->pc.type = type;
	case_id = mx_pt(board_x, board_y);

	bt = &ga->pc.bt;
	origin = ga->board[case_id.x][case_id.y].bt.origin;
	size = mx_vec(160, 160);
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "piece"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, BLUE);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, ORCHID);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, YELLOW);

	ga->pc.xpm = &ga->xpm[ga->pc.type];
	t_2Dpt	xpmpos = mx_pt(origin.x + 40, origin.y + 40);
	ga->pc.xpm->origin = xpmpos;

	mx_draw_img(&bt->img_away);
	mx_draw_img(ga->pc.xpm);

	//link
	ga->board[case_id.x][case_id.y].piece = &ga->pc;
}
#if 0
void	create_case(t_game *ga, int board_x, int board_y, t_case_type type)
{
	t_2Dpt	case_id;
	t_2Dpt	origin;
	t_2Dvec	size;
	t_but	*bt;

	ga->pc.type = type;
	case_id = mx_pt(board_x, board_y);

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

void	create_ai_opponent(t_game *ga)
{
	int	randx = rand() % 5;
	int	randy = rand() % 2;

	create_piece(ga, randx, 0, randy, PIECE_DRAGON);

}
#endif
