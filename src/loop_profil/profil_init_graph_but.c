/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profil_init_graph_but.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:40:44 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 21:11:34 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	profil_init_graph_but(t_game *ga)
{
	t_2Dpt ori;
	t_2Dpt origin;
	t_2Dvec	size;

	size = mx_vec(150, 50);
	ori = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);

	int	align_y = 250;
	t_but	*bt;

	bt = &ga->pbt_pc_catch;
	origin = mx_pt_add_vec(ori, mx_vec(-400, align_y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "PIECES CATCH"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);

	bt = &ga->pbt_pc_loose;
	origin = mx_pt_add_vec(ori, mx_vec(-200, align_y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "PIECES LOOSE"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);

	bt = &ga->pbt_pc_moves;
	origin = mx_pt_add_vec(ori, mx_vec(400, align_y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "PIECES MOVES"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);

	bt = &ga->pbt_sp_tiles;
	origin = mx_pt_add_vec(ori, mx_vec(200, align_y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "SPECIAL TILES USE"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);

	bt = &ga->pbt_wi_forme;
	origin = mx_pt_add_vec(ori, mx_vec(0, align_y));
	*bt = mx_init_button(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_button(bt, "WITCH TRANSFORMATIONS"))
		abort();
	mx_draw_lt_border_aabb(&bt->img_away, bt->box_rel, 1, DARK_GRAY);
	mx_draw_lt_border_aabb(&bt->img_over, bt->box_rel, 2, SILVER);
	mx_draw_pn_border_aabb(&bt->img_active, bt->box_rel, 5, SILVER);
	mx_draw_img(&bt->img_away);
	mx_putstr_cen_img(&bt->img_away, bt->name, SILVER, 0);
}
