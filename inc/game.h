/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:26:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 18:31:16 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "mx.h"

typedef enum e_xpmid
{
	XPM_30W_LANTERN,
	XPM_80W_LANTERN,
	XPM_30W_LOTUS,
	XPM_80W_LOTUS,
	XPM_30W_MOUNTAIN,
	XPM_80W_MOUNTAIN,
	XPM_30W_CASTLE,
	XPM_80W_CASTLE,
	XPM_80W_SAMURAI,
	XPM_80W_NINJA,
	XPM_80W_DRAGON,
	XPM_80W_WITCH,
}	t_xpmid;

typedef enum e_case_type
{
	CASE_NORMAL = 0,
	CASE_LANTERN = 1,
	CASE_LOTUS = 2,
	CASE_MOUNTAIN = 3,
	CASE_CASTLE = 4,
}	t_case_type;

typedef enum e_piece_t
{
	PIECE_SAMURAI = 5,
	PIECE_NINJA = 6,
	PIECE_DRAGON = 7,
	PIECE_WITCH = 8,
}	t_piece_t;

typedef struct s_piece
{
	t_piece_t	type;
	t_img		img;
	t_img		xpm;
	bool		owned;
	bool		mouseover;
}	t_piece;

typedef struct s_case
{
	t_case_type	type;
	t_aabb		abs_box;	// x,x 160,160
	t_aabb		rel_box;	// 0,0 160,160

	t_piece		*piece;
	// NULL if the case is empty

	bool		mouseover;
	bool		visible;
	// si le joueur a une piece sur la case 
	//ou si elle est eclairée
}	t_case;

typedef struct s_game
{
	void	*mlx_ptr;
	t_win	win;

	t_img	img_board;
	t_case	board[5][5];

	t_img	xpm[12];
	t_piece	piece[8];

	t_2Dpt	mouse;
}	t_game;


int		load_xpm(t_game *ga);
void	main_loop(t_game *ga);
void	destroy_xpm(t_game *ga);

#endif /* GAME_H */
