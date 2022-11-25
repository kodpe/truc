/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:33:21 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 15:13:18by sloquet          ###   ########.fr       */
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
	if (keycode == KEY_ESCAPE)
	{
		mlx_loop_end(ga->mlx_ptr);
		return (0);
	}
	fprintf(stderr, "<> key press   [%i] [%c]\n", keycode, keycode);
	return (0);
}

static void	display_waiting_room(t_game *ga)
{
	mx_draw_circle(&ga->waitbox.img, \
		mx_pt(ga->waitbox.img.width / 2 - 15 + ga->waitbox.i, \
			ga->waitbox.img.height / 2), 2, SILVER);
	mx_draw_img(&ga->waitbox.img);

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 - 65, \
		ga->win.height / 2 - 20, SILVER, STR_WAIT);
}

static void	display_starting_room(t_game *ga)
{
	char	*time_left;

	mx_draw_circle(&ga->waitbox.img, \
		mx_pt(ga->waitbox.img.width / 2 - 15 + ga->waitbox.i, \
			ga->waitbox.img.height / 2), 2, SILVER);
	mx_draw_img(&ga->waitbox.img);

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 - 60, \
		ga->win.height / 2 - 20, SILVER, STR_START);

	time_left = ft_itoa(ga->waitbox.starting_delay / 5);
	if (!time_left)
		abort();

	mlx_string_put(ga->mlx_ptr, ga->win.ptr, ga->win.width / 2 + 53, \
		ga->win.height / 2 - 20, SILVER, time_left);
	free(time_left);
}

int	loop_waiting(t_game *ga)
{
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

	// stop condition
	if (dir_size(PATH_COMDIR) == 2)
	{
		if (ga->server == true && ga->profil_opp.file == NULL)
			receive_opponent(ga);
		mx_destroy_img(&ga->waitbox.img);
		return (0);
	}
	usleep(200000);
	// destroy img
	mx_destroy_img(&ga->waitbox.img);
	return (0);
}

int	loop_starting(t_game *ga)
{
	// create img
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(600, 300);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, ga->win.height / 2 - size.y / 2);
	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();

	if (ga->waitbox.starting_delay == 0)
		ga->waitbox.starting_delay = 10 * 5;

	display_starting_room(ga);

	ga->waitbox.i += 10;
	if (ga->waitbox.i == 30)
		ga->waitbox.i = 0;
	ga->waitbox.starting_delay--;

	// stop condition
	if (ga->waitbox.starting_delay == 0)
	{
		mlx_loop_end(ga->mlx_ptr);
		return (0);
	}
	usleep(200000);
	// destroy img
	mx_destroy_img(&ga->waitbox.img);
	return (0);
}

static int	main_loop_st(t_game *ga)
{
	if (ga->profil_opp.file == NULL)
		loop_waiting(ga);
	if (ga->profil_opp.file)
		loop_starting(ga);
	return (0);
}

void	lobby_room(t_game *ga)
{
	log_com(ga);
	assert(ga->profil_you.name);
	assert(ga->profil_you.file);
	if (ga->server == true)
		assert(ga->profil_opp.name == NULL && ga->profil_opp.file == NULL);
	if (ga->client == true)
		assert(ga->profil_opp.name && ga->profil_opp.file);

	// MLX INIT
	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();
	ga->win = mx_init_win(ga->mlx_ptr, 1200, 900);
	if (mx_create_win(&ga->win, "u"))
		abort();

	// MLX LOOP
	mlx_loop_hook(ga->mlx_ptr, &main_loop_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_CROSSDESTROY, 0, &hook_crossdestroy_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press_st, ga);
	mlx_loop(ga->mlx_ptr);
	mx_destroy_img(&ga->waitbox.img); // destroy lobby mlx content

	log_com(ga);
	// END
	if (dir_size(PATH_COMDIR) != 2)
	{
		lobby_exit(ga);
		LOG
		dprintf(2, "\033[1;31mEXIT PATH_COMDIR != 2\033[0m\n");
		exit(2);
	}
	assert(ga->profil_you.name);
	assert(ga->profil_you.file);
	assert(ga->profil_opp.name);
	assert(ga->profil_opp.file);
}
