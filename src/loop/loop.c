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


static void	exit_tmploop(t_game *ga)
{
		mlx_loop_end(ga->mlx_ptr);
		lobby_exit(ga);
		LOG
		exit(0);
}

static int	hook_win_cross_st(t_game *ga)
{
	t_loop	*lp;

	exit_tmploop(ga); //TODO FIXME
	lp = get_active_loop_ptr(ga);
	if (!lp)
		abort();
	mx_add_keycode_to_evstat(&lp->evstat, WIN_CROSS, 42042);
	return (0);
}

static int	hook_key_press_st(int keycode, t_game *ga)
{
	t_loop	*lp;

	if (keycode == KEY_ESCAPE)
		exit_tmploop(ga); //TODO FIXME
	lp = get_active_loop_ptr(ga);
	if (!lp)
		abort();
	mx_add_keycode_to_evstat(&lp->evstat, KEY_PRESS, keycode);
	return (0);
}

static int	hook_key_release_st(int keycode, t_game *ga)
{
	t_loop	*lp;

	lp = get_active_loop_ptr(ga);
	if (!lp)
		abort();
	mx_add_keycode_to_evstat(&lp->evstat, KEY_RELEASE, keycode);
	return (0);
}

static void	lobby_room_init(t_game *ga)
{
	log_com(ga);
	assert(ga->profil_you.name);
	assert(ga->profil_you.file);
	assert(ga->profil_you.path);
	if (ga->server == true)
		assert(ga->profil_opp.name == NULL && ga->profil_opp.file == NULL);
	if (ga->client == true)
		assert(ga->profil_opp.name && ga->profil_opp.file);

	// MLX INIT
	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();
	if (ga->server)
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 0, 0);
	if (ga->client)
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 1300, 0);
	if (mx_create_win(&ga->win, "y"))
		abort();

	// CREATE MLX IMG
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(500, 250);
	origin = mx_pt(ga->win.width / 2 - size.x / 2, ga->win.height / 2 - size.y / 2);
	ga->waitbox.img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&ga->waitbox.img, "waitbox"))
		abort();
}

static void	lobby_room_end(t_game *ga)
{
	// DESTROY MLX IMG
	mx_destroy_img(&ga->waitbox.img);

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
	assert_comfile(ga->profil_opp.path);
	assert(ga->profil_opp.name);
	assert(ga->profil_opp.file);
	assert_comfile(ga->profil_you.path);
}

static int	loop_manager(t_game *ga)
{
	if (ga->lp_waitopp.active)
		loop_waitopp(ga);

	if (ga->profil_opp.file)
		loop_startgame(ga);

	if (ga->lp_wantquit.active)
		loop_wantquit(ga);

	return (0);
}

void	lobby_room(t_game *ga)
{
	// INIT
	lobby_room_init(ga);

	if (ga->server == true)
		_goto_loop(ga, 0, LOOP_ID_WAITOPP);
	else
		_goto_loop(ga, 0, LOOP_ID_STARTGAME);

	// MLX LOOP
	mlx_loop_hook(ga->mlx_ptr, &loop_manager, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_WIN_CROSS, 0, &hook_win_cross_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press_st, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYUP, 1L << 1, &hook_key_release_st, ga);
	mlx_loop(ga->mlx_ptr);

	// END
	lobby_room_end(ga);
}
