/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:20:10 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/03 00:11:24 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_basic_update_case(t_game *ga, t_but *bt, t_case *ca)
{
	t_but	*fullb = &ga->fullboard;

	if (fullb->xev_action_out)
		printf("OUT BOARD");
	if (fullb->xev_action_in)
		printf("INSIDE BOARD");

	if (bt->xev_action_out)
	{
		mx_draw_img(&bt->img_away);
	}

	if (bt->xev_action_in)
	{
		mx_draw_img(&bt->img_over);
		if (ca->piece == NULL)
			put_info(ga, "Cette case est vide.");
		else
		{
			char	*tmp;
			tmp = ft_itoabtw("La pièce est de type ", ca->piece->type, " !");
			put_info(ga, tmp);
			free(tmp);
		}
		
	}

	// if (bt->xev_action_press[MOUSE_BUT_LEFT])
	// {
	// 	mx_draw_img(&bt->img_active);
	// 	if (ca->piece == NULL)
	// 		printf("Case is empty\n");
	// }

	// if (bt->xev_action_release[MOUSE_BUT_LEFT])
	// {
	// 	mx_draw_img(&bt->img_over);
	// 	printf("Case is release\n");
	// }

	// if (bt->xev_is_press[MOUSE_BUT_LEFT])
	// {
	// 	printf("Case is press\n");
	// }
	(void)ga;
	(void)ca;
}

void	update_board(t_game *ga)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			mx_handle_button(&ga->board[y][x].bt, &ga->evstat);
			_basic_update_case(ga, &ga->board[y][x].bt, &ga->board[y][x]);
		}
	}
}
