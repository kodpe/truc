/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:12:13 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 16:28:53 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#if 0



/*
	checkboard 800x800 5x5 cases

	case 160x160
	personnage 80x80
	case special 80x80 or 30x30
*/

void	draw_piece(t_game *ga)
{
	t_case	current_case;

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			current_case = ga->checkboard[y][x];
			if (current_case.visible)
				draw_case()

		}
	}
}

void	draw_case(t_img *img, t_2Dpt pos)
{
	int	size;	// size of square case
	int	db;		// distance_to_border
	int	mx;		// extremum db
	int	mi;		// mid size
	int	c3; 	// color moving points

	size = 160;
	c3 = WHITE;

	db = 5;
	mi = size / 2;
	mx = size - db;
	mx_fill_circle(img, mx_pt(db, db), 2, c3);
	mx_fill_circle(img, mx_pt(mi, db), 2, c3);
	mx_fill_circle(img, mx_pt(mx, db), 2, c3);
	mx_fill_circle(img, mx_pt(db, mi), 2, c3);
	mx_fill_circle(img, mx_pt(mx, mi), 2, c3);
	mx_fill_circle(img, mx_pt(db, mx), 2, c3);
	mx_fill_circle(img, mx_pt(mi, mx), 2, c3);
	mx_fill_circle(img, mx_pt(mx, mx), 2, c3);
}

#endif
