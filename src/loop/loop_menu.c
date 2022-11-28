/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:00:35 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 21:49:57 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_menu.active = 0;
	LOG
	// log_com(ga);
	// unlink_sc(ga->profil_you.path);
	// free(ga->profil_you.file);
	// free(ga->profil_you.name);
	// free(ga->profil_you.path);
	// free(ga->profil_opp.file);
	// free(ga->profil_opp.name);
	// free(ga->profil_opp.path);
	mx_destroy_img(&ga->waitbox.img);
	mlx_loop_end(ga->mlx_ptr);
}

static void	_init(t_game *ga)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(500, 250);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, \
					ga->win.height / 2 - size.y / 2);
	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();
	(void)ga;
}

static void	_display(t_game *ga, t_img *img)
{
	// if (rand() % 3 == 0) // cool
		if (mx_reset_img(img))
			abort();

	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_img(img);
	// mx_putstr_cen_img(img, STR_WAIT, SILVER);
	mx_putnbr_cen_img(img, ga->lp_menu.time_elapsed, SILVER);
	// (void)img;
	(void)ga;
}

void	loop_menu(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_menu, 5, 0))
		_init(ga);
	_display(ga, &ga->waitbox.img);

	// ga->waitbox.i += 10;
	// if (ga->waitbox.i == 30)
		// ga->waitbox.i = 0;
	
	if (ga->evstat.win_cross)
		return (_destroy(ga));
	// if (dir_size(PATH_COMDIR) == 2 && ga->profil_opp.path == NULL)
	// {
	// 		receive_opponent(ga);
	// 		if (assert_comfile(ga->profil_opp.path))
	// 			return (_destroy(ga));
	// 		if (assert_comfile(ga->profil_you.path))
	// 			return (_destroy(ga));
	// 		// passage a startgame avec new img init
	// 		mx_destroy_img(&ga->waitbox.img); 
	// 		goto_loop(ga, LOOP_ID_WAITOPP, LOOP_ID_STARTGAME);
	// }
}
