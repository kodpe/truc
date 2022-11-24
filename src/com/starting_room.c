/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:33:21 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 23:14:10 by sloquet          ###   ########.fr       */
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

static void	display_starting_room(t_game *ga)
{
	char	*time_left;

	mx_draw_circle(&ga->waitbox.img, \
		mx_pt(ga->waitbox.img.width / 2 - 15 + ga->waitbox.i, \
			ga->waitbox.img.height / 2), 3, SILVER);
	mx_draw_img(&ga->waitbox.img);

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 - 60, \
		ga->win.height / 2 - 20, SILVER, GAME_STR_START);

	time_left = ft_itoa(ga->waitbox.starting_delay / 5);
	if (!time_left)
		abort();

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 + 53, \
		ga->win.height / 2 - 20, SILVER, time_left);
	free(time_left);
}

static int	loop_chrono_st(t_game *ga)
{
	usleep(200000);
	if (mx_reset_img(&ga->waitbox.img))
		abort();

	if (ga->waitbox.starting_delay == 0)
		ga->waitbox.starting_delay = 10 * 5;

	display_starting_room(ga);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;
	ga->waitbox.starting_delay--;

	if (ga->waitbox.starting_delay == 0)
		mlx_loop_end(ga->mlx_ptr);
	return (0);
}

void	starting_room(t_game *ga)
{
	t_2Dpt	origin;
	t_2Dvec	size;

	assert(ga->profil_you.name);
	assert(ga->profil_you.file);
	assert(ga->profil_opp.name);
	assert(ga->profil_opp.file);

	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();

	ga->win = mx_init_win(ga->mlx_ptr, 1200, 900);
	if (mx_create_win(&ga->win, "starting room"))
		abort();

	size = mx_vec(300, 300);
	origin.x = ga->win.width / 2 - size.x / 2;
	origin.y = ga->win.height / 2 - size.y / 2;

	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();

	mlx_loop_hook(ga->mlx_ptr, &loop_chrono_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_CROSSDESTROY, 0, &hook_crossdestroy_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press_st, ga);
	mlx_loop(ga->mlx_ptr);

	mx_destroy_img(&ga->waitbox.img);
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);
	exit(0);
}
