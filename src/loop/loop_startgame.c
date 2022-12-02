/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_startgame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:01:45 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/02 15:44:56 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy(t_game *ga)
{
	ga->lp_startgame.active = 0;
	LOG
	unlink_sc(ga->profil_you.path);
	free(ga->profil_you.file);
	free(ga->profil_you.name);
	free(ga->profil_you.path);
	free(ga->profil_opp.file);
	free(ga->profil_opp.name);
	free(ga->profil_opp.path);
	mx_destroy_img(&ga->waitbox.img);
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
	ga->waitbox.starting_delay = 3 * 5; // 3 seconds
}

static void	_display(t_game *ga, t_img *img)
{
	if (mx_reset_img(img))
		abort();

	mx_draw_aabb(img, img->box_rel, SILVER);
	mx_draw_circle(img, \
			mx_pt(img->width / 2 - 15 + ga->waitbox.i, \
				img->height / 2 + 12), 2, SILVER);
	mx_draw_img(img);

	char *tmp = ft_itoa(ga->waitbox.starting_delay / 5);
	char *str = ft_strjointri(STR_START, tmp, " s");
	free(tmp);
	mx_putstr_cen_img(img, str, SILVER, -12);
	free(str);
}

void	loop_startgame(t_game *ga)
{
	if (0 == mx_time_loop(&ga->lp_startgame, 5, 0))
		_init(ga);
	//* DISPLAY FUNCTION(S)
	_display(ga, &ga->waitbox.img);

	//* HERE LOOP INCREMENT VALUE(S)
	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;
	ga->waitbox.starting_delay--;

	//* STOP CONDITION(S) : GOTO LOOP OR MLX_LOOP_END (= EXIT )
	if (ga->waitbox.starting_delay == 0)
	{
		if (assert_comfile(ga->profil_opp.path) \
			|| assert_comfile(ga->profil_you.path))
		{
			_destroy(ga);
			goto_loop(ga, LOOP_ID_STARTGAME, LOOP_EXIT);
			return ;
		}
		mx_destroy_img(&ga->waitbox.img); // we dont destroy com profilvar
		goto_loop(ga, LOOP_ID_STARTGAME, LOOP_ID_GAME);
	}
}
