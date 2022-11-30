/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profil_graph_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:27:57 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/30 01:04:32 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	profil_graph_actions(t_game *ga)
{
	if (ga->pbt_pc_catch.xev_action_release[MOUSE_BUT_LEFT])
		profil_init_graph(ga, 7);

	if (ga->pbt_pc_loose.xev_action_release[MOUSE_BUT_LEFT])
		profil_init_graph(ga, 11);

	if (ga->pbt_pc_moves.xev_action_release[MOUSE_BUT_LEFT])
		profil_init_graph(ga, 15);

	if (ga->pbt_sp_tiles.xev_action_release[MOUSE_BUT_LEFT])
		profil_init_graph(ga, 19);

	if (ga->pbt_wi_forme.xev_action_release[MOUSE_BUT_LEFT])
		profil_init_graph(ga, 23);
}
