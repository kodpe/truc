/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:33:21 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/06 14:15:2 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	hook_crossdestroy_st(t_game *ga)
{
	mlx_loop_end(ga->mlx_ptr);
	return (0);
}

static int	hook_key_press_st(int keycode, t_game *ga)
{
	fprintf(stderr, "<> key press   [%i] [%c]\n", keycode, keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(ga->mlx_ptr);
	return (0);
}

static void	display_waiting_room(t_game *ga)
{
	mx_draw_circle(&ga->waitbox.img, \
		mx_pt(ga->waitbox.img.width / 2 - 15 + ga->waitbox.i, \
			ga->waitbox.img.height / 2), 2, SILVER);
	mx_draw_img(&ga->waitbox.img);

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 - 65, \
		ga->win.height / 2 - 20, SILVER, GAME_STR_WAIT);
}

static int	loop_chrono_st(t_game *ga)
{
	usleep(200000);

	// destroy im if exist
	if (ga->waitbox.img.ptr)
		mx_destroy_img(&ga->waitbox.img);

	// create img
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(600, 300);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, ga->win.height / 2 - size.y / 2);
	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();

	display_waiting_room(ga);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;

	if (dir_size(PATH_COMDIR) == 2)
		mlx_loop_end(ga->mlx_ptr);
	return (0);
}

void	waiting_room(t_game *ga)
{

	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();

	ga->win = mx_init_win(ga->mlx_ptr, 1200, 900);
	if (mx_create_win(&ga->win, "waiting room"))
		abort();

	mlx_loop_hook(ga->mlx_ptr, &loop_chrono_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_CROSSDESTROY, 0, &hook_crossdestroy_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press_st, ga);
	mlx_loop(ga->mlx_ptr);

	mx_destroy_img(&ga->waitbox.img);
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);

	if (dir_size(PATH_COMDIR) != 2)
	{
		char	*comfilepath = ft_strjoin(PATH_COMDIR, ga->profil_you.file);
		unlink_sc(comfilepath);
		free(comfilepath);
		free(ga->profil_you.file);
		free(ga->profil_you.name);
		exit(0);
	}
}
